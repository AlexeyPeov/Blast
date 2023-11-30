#include "../Headers/Client.h"



Client::Client(){
    this->id = generate_random_id();
}
//bool Client::connect(std::string address, uint16_t port) {
//    this->socket.setBlocking(false);
//    this->host_ip = address;
//    this->host_port = port;
//    if (socket.bind(port, address) != sf::Socket::Done) {
//        std::cerr << "Error connecting to Server\n";
//        this->active = false;
//    }
//    this->active = true;
//    std::cout << "Client running..\n";
//    return active;
//}

std::string Client::getServerIp(){
    std::string ip;
    std::ifstream file(working_dir() + "/server_config.txt");
    if (file.is_open()) {
        std::getline(file, ip);
        file.close();
    }
    return ip;
}

uint16_t Client::getServerPort(){
    std::string port_str;
    uint16_t port = 0;
    std::ifstream file(working_dir() + "/server_config.txt");
    if (file.is_open()) {
        std::getline(file, port_str); // skip first line
        std::getline(file, port_str);
        port = std::stoi(port_str);
        file.close();
    }
    return port;
}


bool Client::connect(sf::IpAddress address, uint16_t port) {
    this->socket.setBlocking(false);
    this->host_ip = address;
    this->host_port = port;

    this->player_object.id = id;
    this->player_object.main_menu_event.host = host;
#ifdef CLIENT_DEBUG_SEND
    std::cout << "CL_ID: " << id << " OBJ_ID: " << player_object.id << "\n";

    if(player_object.main_menu_event.host){
        std::cout << "HOST: TRUE\n";
    }
#endif
    sf::Packet packet;


    packet << MessageType::CONNECT << id << player_object;

    if (socket.send(packet, host_ip, host_port) != sf::Socket::Done) {
#ifdef CLIENT_DEBUG_SEND
        std::cerr << "Error connecting to server\n";
#endif
        return false;
    }
    active = true;

    std::cout << "Client running..\n";
    return true;
}

void Client::disconnect() {
    sf::Packet packet;
    packet << MessageType::DISCONNECT << id << player_event;

    if (socket.send(packet, host_ip, host_port) != sf::Socket::Done) {
        // Error handling
#ifdef CLIENT_DEBUG_SEND
        std::cerr << "ERROR DISCONNECTING" << host_ip << " hp:" << host_port << '\n';
#endif
    } else {

#ifdef CLIENT_DEBUG_SEND
        std::cout << "DISCONNECTED: " << id << " OBJ_ID: " << player_object.id << "\n";
#endif

    }
    this->active = false;
    this->socket.unbind();
    this->player_objects.clear();
    this->missile_objects.clear();
    this->bomb_object = {0};
    this->player_object = PlayerObject();
    this->player_event = {0};
    std::cout << "Client stopped.\n";
}



void Client::send_data() {
    sf::Packet packet;
    if(host){
        packet << MessageType::PLAYER_EVENT_HOST << id << player_event << *(sf::Uint8*)&player_object.main_menu_event;
    } else {
        packet << MessageType::PLAYER_EVENT << id << player_event;
    }
    if (socket.send(packet, host_ip, host_port) != sf::Socket::Done) {
        // Error handling
#ifdef CLIENT_DEBUG_SEND
        std::cerr << "cl-side_err: h_ip" << host_ip << " hp:" << host_port << '\n';
#endif
    } else {

//#ifdef CLIENT_DEBUG_SEND
//        std::cout << "Client SEND DATA. TICK:" << player_object.tick << "\n";
//#endif

    }

}



void Client::receive_data() {
    // Receive data from server
    sf::Packet packet;
    sf::IpAddress sender;
    uint16_t port;

    while (socket.receive(packet, sender, port) == sf::Socket::Done) {
        // Process received data
        uint64 curr_tick;
        uint64 player_objects_count;
        uint64 missile_objects_count;
        uint32 bomb_obj;

        packet >> curr_tick;
        packet >> bomb_obj;
        packet >> player_objects_count;
        packet >> missile_objects_count;


#ifdef CLIENT_DEBUG_RECEIVE
        if(curr_tick == player_object.tick + 1){
            std::cout << "Received next tick\n";
        } else {
            std::cout << "Received bad tick: " <<  curr_tick << " and obj.tick: " <<  player_object.tick << "\n";
        }
#endif

        if(curr_tick == UINT64_MAX){
            std::cout << "server is off, disconnecting client..\n";
            disconnect();
            return;
        }


        if(curr_tick != tick){
            player_objects.clear();
            missile_objects.clear();

            this->bomb_object = *(BombObject*)&bomb_obj;

#ifdef CLIENT_DEBUG_RECEIVE
            std::cout << "COUNT:" << player_objects_count << "\n";
            std::cout << "RECEIVED as CL: " << curr_tick << " players count" << player_objects_count << "\n";
#endif
            for (size_t i = 0; i < player_objects_count; i++) {
                PlayerObject obj;
                packet >> obj;
                player_objects.push_back(obj);

               // std::cout << "CLIENT RECEIVE PLANT TIMER: " << obj.plant_or_defuse_timer << "\n";

                if(obj.id == player_object.id){
                    player_object = obj;
                }

#ifdef CLIENT_DEBUG_RECEIVE
                std::cout << "RECEIVED PLAYER OBJ: " << obj.id << " main_menu_event: " << main_menu_event_to_string(obj) <<   "\n";
#endif
            }

            for (size_t i = 0; i < missile_objects_count; i++) {
                MissileObject obj;
                packet >> obj;
                missile_objects.push_back(obj);
#ifdef CLIENT_DEBUG_RECEIVE
                std::cout << "RECEIVED missile OBJ: " << obj.id <<  "\n";
#endif
            }
        } else {
#ifdef CLIENT_DEBUG_RECEIVE
            std::cout << "RECEIVED WRONG TICK: " << curr_tick << " cl.obj.tick:" << player_object.tick << "\n";
#endif
        }
    }

    player_event = {0};

}

std::string Client::main_menu_event_to_string(PlayerObject &object){
    std::string menu_event = "\nmap1 : " + std::to_string(static_cast<uint32>(object.main_menu_event.map1))
            + "\n map2 : " + std::to_string(static_cast<uint32>(object.main_menu_event.map2))
            + "\n map3 : " + std::to_string(static_cast<uint32>(object.main_menu_event.map3))
            + "\n death_match_game_mode : " + std::to_string(static_cast<uint32>(object.main_menu_event.death_match_game_mode))
            + "\n takeover_game_mode : " + std::to_string(static_cast<uint32>(object.main_menu_event.takeover_game_mode))
            + "\n host : " + std::to_string(static_cast<uint32>(object.main_menu_event.host))
            + "\n ready to play : " + std::to_string(static_cast<uint32>(object.main_menu_event.ready_to_play))
            + "\n in game : " + std::to_string(static_cast<uint32>(object.main_menu_event.in_game));
    return menu_event;
}