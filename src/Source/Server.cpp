#include "../Headers/Server.h"


bool Server::set_listener() {
    this->server_socket.setBlocking(false);
    if (this->server_socket.bind(53000) != sf::Socket::Done) {
        std::cerr << "Error setting up listener\n";
        return false;
    }
    this->active = true;
    std::cout << "Server running..\n";
    return active;
}


void Server::receive_data(){
    if(active){
        sf::Packet packet;
        sf::IpAddress sender;
        uint16_t port;
        while (server_socket.receive(packet, sender, port) == sf::Socket::Done) {
            uint8_t type;
            uint64_t object_id;
            Object object;
            packet >> type >> object_id >> object;

            if(type == MessageType::DISCONNECT){
                objects.erase(object_id);
                clients.erase(std::remove_if(clients.begin(), clients.end(),
                                             [object_id](const auto& client)
                                             { return client->id == object_id; }), clients.end());
                continue;
            } else {

                if(objects.find(object_id) == objects.end()){

                    objects[object_id] = object;
                    clients.push_back(std::make_unique<Client>(object_id, "", sender, port));
#ifdef SERVER_DEBUG_RECEIVE
                    std::cout << "CLIENT CONNECTED: ID: " << object_id << " \n";
                    std::cout << "ITS OBJ ID: " << object.id << "\n";
#endif

                } else {

                    if(objects[object_id].tick != object.tick){
#ifdef SERVER_DEBUG_RECEIVE
                        std::cout << "object updated on server id: " << object.id << " tick:" << object.tick << "\n";
#endif
                        objects[object_id] = object;
                    }



                }

            }
        }
    }
}

bool Server::send_data(){
    if(active){
        tick++;
        packets[tick] = {objects, objects.size()};
        for (auto& client : clients) {
            sf::Packet packet;
            packet << tick;
            packet << objects.size();
            for (auto &[id, object] : objects) {
                object.tick = tick;
                packet << object;
            }
            if (client->socket.send(packet, client->client_ip, client->host_port) != sf::Socket::Done) {
#ifdef SERVER_DEBUG_SEND
                std::cerr << "cl:" << client->id << "-";
#endif
                return false;
            } else {
                packets[tick].second -= 1;
            }
        }
        if(packets[tick].second == 0){
#ifdef SERVER_DEBUG_SEND
            std::cout << "packet[" << tick << "] sent to all\n";
            std::cout << "pcts-size: " << packets.size() << "\n";
#endif
            packets.erase(tick);
        } else {



        }
        return true;
    }
    return false;
}


void Server::disconnect(){
    tick = UINT64_MAX;
    for (auto &client: clients) {
        sf::Packet packet;
        packet << tick;
        packet << objects.size();
        for (auto &[id, object]: objects) {
            packet << object;
        }
        if (client->socket.send(packet, client->client_ip, client->host_port) != sf::Socket::Done) {
#ifdef SERVER_DEBUG_SEND
            std::cerr << "cl:" << client->id << "-";
#endif
        }
    }
    server_socket.unbind();
    clients.clear();
    objects.clear();
    packets.clear();
    active = false;
    tick = 0;
}

void Server::printObjects() {
    std::cout << "\n\nOBJECTS: \n";
    for (auto &[id, obj]: this->objects) {
        std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                  << obj.main_menu_action << "\n";
    }
    std::cout << "\n\n";
}