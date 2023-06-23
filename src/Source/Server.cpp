#include "../Headers/Server.h"


bool Server::set_listener() {
    std::unique_lock<std::mutex> lock(server_mutex);

    this->server_socket.setBlocking(false);
    if (this->server_socket.bind(53000) != sf::Socket::Done) {
        std::cerr << "Error setting up listener\n";
        return false;
    }
    map.init_map_textures();
    this->active = true;
    std::cout << "Server running..\n";

    lock.unlock();
    return active;
}


void Server::receive_data() {
    if (active) {
        sf::Packet packet;
        sf::IpAddress sender;
        uint16_t port;
        while (server_socket.receive(packet, sender, port) == sf::Socket::Done) {
            uint8 type; // these are always present
            uint64 object_id; // these are always present

            PlayerObject player_object; // only if MessageType CONNECT

            PlayerEvent player_event = {0}; // if MessageType PLAYER_EVENT / PLAYER_EVENT_HOST

            sf::Uint8 main_menu_event; // ONLY PLAYER_EVENT_HOST

            packet >> type >> object_id;

            // receive packet
            if (type == MessageType::CONNECT) {
                packet >> player_object;
            } else {
                packet >> player_event;
                //std::cout << "PLAYER EVENT: " << std::bitset<32>(*(uint32*)&player_event) << std::endl;
            }

            if (type == MessageType::PLAYER_EVENT_HOST) {
                packet >> main_menu_event;
                //std::cout << "MAIN MENU EVENT: " << std::bitset<8>(main_menu_event) << std::endl;
            }


            // do stuff
            if (type == MessageType::CONNECT) {
                player_objects[object_id] = player_object;
                clients[object_id] = std::make_unique<Client>(object_id, "", sender, port);

                std::cout << "PLAYER OBJECT ON CONNECT: HOST: "
                          << static_cast<bool>(player_object.main_menu_event.host) << "\n";

                if (player_object.main_menu_event.host) {
                    std::cout << "SENT THAT HOST: TRUE\n";
                    clients[object_id]->host = true;
                    host_client_id = object_id;
                    std::cout << "HOST CLIENT ID SET TO: " << host_client_id << "\n";
                }
#ifdef SERVER_DEBUG_RECEIVE
                std::cout << "CLIENT CONNECTED, ID: " << player_object.id << " \n";
#endif
                continue;
            }

            if (type == MessageType::DISCONNECT) {
                player_objects.erase(object_id);
                clients.erase(object_id);
                continue;
            }

            if (type == MessageType::PLAYER_EVENT || type == MessageType::PLAYER_EVENT_HOST) {
                clients[object_id]->player_event = player_event;
            }

            if (type == MessageType::PLAYER_EVENT_HOST) {
                //player_objects[object_id].main_menu_event = *(MainMenuEvent*)&main_menu_event; // sync what gamemode/map host has chosen
            }

        }
    }
}

bool Server::send_data() {
    if (active) {
        tick++;
        //packets[tick] = {objects, objects.size()};
        for (auto &[client_id, client]: clients) {
            sf::Packet packet;
            packet << tick;
            packet << bomb_object;
            packet << (uint64)player_objects.size();
            packet << (uint64)missile_objects.size();
            for (auto &[id, object]: player_objects) {
#ifdef SERVER_DEBUG_SEND
                std::cout << "packing object:" << object.id << "-\n";
#endif
                object.tick = tick;
                packet << object;
                //std::cout << "SERVER SEND PLANT TIMER: " << object.plant_or_defuse_timer << "\n";
            }

            for (auto &[id, missile]: missile_objects) {
                packet << missile;
            }
            if (client->socket.send(packet, client->client_ip, client->host_port) != sf::Socket::Done) {
#ifdef SERVER_DEBUG_SEND
                std::cerr << "cl:" << client->id << "-";
#endif
                //return false;
            } else {
#ifdef SERVER_DEBUG_SEND
                std::cerr << "sent data to client:" << client->id << "-";
#endif
            }
        }
/*        if(packets[tick].second == 0){
#ifdef SERVER_DEBUG_SEND
            std::cout << "packet[" << tick << "] sent to all\n";
            std::cout << "pcts-size: " << packets.size() << "\n";
#endif
            packets.erase(tick);
        } else {



        }*/
        return true;
    }
    return false;
}


void Server::disconnect(std::thread &server_thread) {
    std::unique_lock<std::mutex> lock(server_mutex);

    tick = UINT64_MAX;
    for (auto &[client_id, client]: clients) {
        sf::Packet packet;
        packet << tick;
        packet << (uint64)player_objects.size();
        for (auto &[id, object]: player_objects) {
            packet << object;
        }

        for(int i = 0; i < 30; i++){
            client->socket.send(packet, client->client_ip, client->host_port);
        }

//        if (client->socket.send(packet, client->client_ip, client->host_port) != sf::Socket::Done) {
//#ifdef SERVER_DEBUG_SEND
//            std::cerr << "cl:" << client->id << "-";
//#endif
//        }
    }
    server_socket.unbind();

    clients.clear();
    player_objects.clear();
    missile_objects.clear();


    map.players.clear();
    map.missiles.clear();
    map.explosions.clear();
    map.walls_map.clear();
    map.walls_for_collision_map.clear();


    takeover.reset();
    //packets.clear();
    active = false;
    tick = 0;

    lock.unlock();
    server_thread.join();
    std::cout << "SERVER DISCONNECTED\n";
}

void Server::death_match() {

}

void Server::takeover_game_mode() {
    if (!takeover.game_started) {
        short level = 0;
        if (player_objects[host_client_id].main_menu_event.map1) level = 1;
        else if (player_objects[host_client_id].main_menu_event.map2) level = 2;
        else if (player_objects[host_client_id].main_menu_event.map3) level = 3;

        std::cout << "SERVER LEVEL " << level << "\n";
        map.init_walls(level);
        takeover = Takeover(map);
        takeover.game_started = true;
        std::cout << "takeover game started\n";
    }
    if (!takeover.game_over) {
        takeover.update();
    }
}


void Server::play_tick() {
    MainMenuEvent host_main_menu_event = player_objects[host_client_id].main_menu_event;
    std::vector<std::pair<uint64, PlayerEvent>> player_events;

    for (auto &[client_id, client]: clients) {
        PlayerEvent player_event = client->player_event;
        PlayerObject &object = player_objects[client->id];

        // main menu mainly
        if (player_event.change_team_to_t_button_pressed) {
            object.team = TEAM_T;
        }
        if (player_event.change_team_to_ct_button_pressed) {
            object.team = TEAM_CT;
        }

        if (player_event.chose_map_1_button_pressed) {
            object.main_menu_event.map1 = true;
            object.main_menu_event.map2 = false;
            object.main_menu_event.map3 = false;
        } else if (player_event.chose_map_2_button_pressed) {
            object.main_menu_event.map1 = false;
            object.main_menu_event.map2 = true;
            object.main_menu_event.map3 = false;
        } else if (player_event.chose_map_3_button_pressed) {
            object.main_menu_event.map1 = false;
            object.main_menu_event.map2 = false;
            object.main_menu_event.map3 = true;
        }
        if (player_event.chose_deathmatch_button_pressed) {
            object.main_menu_event.death_match_game_mode = true;
            object.main_menu_event.takeover_game_mode = false;
        } else if (player_event.chose_takeover_button_pressed) {
            object.main_menu_event.death_match_game_mode = false;
            object.main_menu_event.takeover_game_mode = true;
        }
        if (player_event.ready_button_pressed) {
            object.main_menu_event.ready_to_play = true;
        }

        if(!object.main_menu_event.ready_to_play){
            object.main_menu_event.in_game = false;
        }


//        else {
//            object.main_menu_event.ready_to_play = false;
//        }


        if (!object.main_menu_event.host) {
            object.main_menu_event.map1 = host_main_menu_event.map1;
            object.main_menu_event.map2 = host_main_menu_event.map2;
            object.main_menu_event.map3 = host_main_menu_event.map3;

            object.main_menu_event.death_match_game_mode = host_main_menu_event.death_match_game_mode;
            object.main_menu_event.takeover_game_mode = host_main_menu_event.takeover_game_mode;
        }

        player_events.emplace_back(client->id, player_event);
    }


    if (!host_main_menu_event.in_game) {
        bool everyone_ready = true;

        for (auto &[id, player]: player_objects) {
            if (!player.main_menu_event.ready_to_play) {
                everyone_ready = false;
            }
        }

        if (everyone_ready) {
            takeover.reset();
            for (auto &[id, player]: player_objects) {
                map.players[id] = map.init_new_player(id, player.pos_x, player.pos_y, player.team);
                player.main_menu_event.in_game = true; // todo : THE ERROR IS CAUSED BY PLAYER TEAM NOT UPDATING ON SERVER.MAP .. WHY?
                std::cout << "GAME SHOULD START,  updated host: " << (player.id == host_client_id) << '\n';
            }
        }
    }

//    for(auto&[id, player] : player_objects){
//        std::cout << "PLAYER " << id <<   " IN GAME: "   << (bool)player.main_menu_event.in_game << '\n';
//    }

    // game loop
    if (host_main_menu_event.in_game) {

        if (host_main_menu_event.death_match_game_mode) {
            death_match();
        } else if (host_main_menu_event.takeover_game_mode) {
            takeover_game_mode();
//            for (auto &[id, player]: takeover.map->players) {
//                std::cout << "PLAYER ON TAKEOVER SERVER " << id << " TEAM: " << (uint32) player.team << "\n";
//            }
//            for (auto &[id, player]: map.players) {
//                std::cout << "PLAYER ON SERVER " << id << " TEAM: " << (uint32) player.team << "\n";
//            }
        }

        for (auto &missile: map.missiles) {
            if (!missile.life) {
                missile_objects.erase(missile.id);
            }
        }

        map.play_tick(player_events);

        for (auto &[id, player]: map.players) {
            player.transfer_data_to(player_objects[id]);
//            std::cout << "SERVER PLAYER DROPS BOMB:  " << player.player_state.dropping_bomb << " HAS_BOMB? "
//                      << player.player_state.has_bomb << "\n";

            player_objects[id].sync = takeover.sync_object();
//                std::cout << "player_object synced with server takeover: current_round: " << object.sync.current_round << " rsec_left: " << object.sync.round_seconds_left
//                          << " before/in/retake/after_round: " << object.sync.is_before_round << " " << object.sync.is_in_round << " " << object.sync.is_retake
//                          << " " << object.sync.is_after_round << "\n";
//
        }
        for (auto &missile: map.missiles) {
            missile.transfer_data_to(missile_objects[missile.id]);
        }
        map.transfer_bomb_data_to(bomb_object);
    }
}

void Server::run(){
    auto frame_duration = std::chrono::milliseconds(1000 / 60);

    while(active){
        auto frame_start = std::chrono::steady_clock::now();

        std::unique_lock<std::mutex> lock(server_mutex);

        receive_data();
        play_tick();
        send_data();

        lock.unlock();

        auto frame_end = std::chrono::steady_clock::now();
        auto elapsed_time = frame_end - frame_start;
        if (elapsed_time < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed_time);
        }
    }
    std::cout << "server run stopped\n";
}
/*
void Server::printObjects() {
    std::cout << "\n\nOBJECTS: \n";
    for (auto &[id, obj]: this->objects) {
        std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                  << obj.main_menu_action << "\n";
    }
    std::cout << "\n\n";
}*/
