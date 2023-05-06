#include "../Headers/Client.h"
#include "../Headers/Map.h"


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

    uint64_t identifier = generate_random_id();

    this->id = identifier;
    this->object.id = identifier;
#ifdef CLIENT_DEBUG_SEND
    std::cout << "CL_ID: " << id << " OBJ_ID: " << object.id << "TICK:" << object.tick << "\n";
#endif
    sf::Packet packet;

    packet << MessageType::OBJECT << object.id << object;
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
    packet << MessageType::DISCONNECT << id << object;
    if (socket.send(packet, host_ip, host_port) != sf::Socket::Done) {
        // Error handling
#ifdef CLIENT_DEBUG_SEND
        std::cerr << "ERROR DISCONNECTING" << host_ip << " hp:" << host_port << '\n';
#endif
    } else {

#ifdef CLIENT_DEBUG_SEND
        std::cout << "DISCONNECTED: " << id << " OBJ_ID: " << object.id << "TICK:" << object.tick << "\n";
#endif

    }
    this->active = false;
    this->socket.unbind();
    this->objects.clear();
    reset(this->object);
    std::cout << "Client stopped.\n";
}



void Client::send_data() {
    sf::Packet packet;
    packet << MessageType::OBJECT << id << object;
    if (socket.send(packet, host_ip, host_port) != sf::Socket::Done) {
        // Error handling
#ifdef CLIENT_DEBUG_SEND
        std::cerr << "cl-side_err: h_ip" << host_ip << " hp:" << host_port << '\n';
#endif
    } else {

#ifdef CLIENT_DEBUG_SEND
        std::cout << "Client SEND DATA. TICK:" << object.tick << "\n";
#endif

    }

}



void Client::receive_data() {
    // Receive data from server
    sf::Packet packet;
    sf::IpAddress sender;
    uint16_t port;

    while (socket.receive(packet, sender, port) == sf::Socket::Done) {
        // Process received data
        uint64_t curr_tick;
        packet >> curr_tick;
        size_t count;
        packet >> count;

#ifdef CLIENT_DEBUG_RECEIVE
        if(curr_tick == object.tick + 1){
            std::cout << "Received next tick\n";
        } else {
            std::cout << "Received bad tick: " <<  curr_tick << " and obj.tick: " <<  object.tick << "\n";
        }
#endif

        if(curr_tick == -1){
            std::cout << "server off\n";
            disconnect();
            return;
        }


        if(curr_tick != object.tick){
            objects.clear();
#ifdef CLIENT_DEBUG_RECEIVE
            std::cout << "COUNT:" << count << "\n";
            std::cout << "RECEIVED as CL:" << curr_tick << " " << count << "h_ip:" << sender << "port:" << port << "\n";
#endif

            for (size_t i = 0; i < count; ++i) {
                Object obj;
                packet >> obj;

                if(obj.id != object.id){
#ifdef CLIENT_DEBUG_RECEIVE
                    std::cout << "RECEIVED OBJ: " << obj.id <<  "\n";
#endif
                    objects.push_back(obj);
                } else {
                    object.hp = obj.hp;
                    object.tick = obj.tick;
                }
            }

        } else {
#ifdef CLIENT_DEBUG_RECEIVE
            std::cout << "RECEIVED WRONG TICK: " << curr_tick << " cl.obj.tick:" << object.tick << "\n";
#endif
        }
    }

}


void Client::print_vector() {
    std::cout << "\n\nRECEIVING DATA: \n";
    for (auto &obj: this->objects) {
        std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                  << obj.main_menu_action << "\n";
    }
    std::cout << "\n\n";
}