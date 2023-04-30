#include "../Headers/Client.h"


bool Client::connect(std::string address, int port) {
    this->socket.setBlocking(false);
    if (socket.connect(address, port) != sf::Socket::Done) {
        std::cerr << "Error connecting to Server\n";
        this->active = false;
    }
    this->active = true;
    std::cout << "Client running..\n";
    return active;
}

void Client::disconnect() {
    this->active = false;
    this->socket.disconnect();
    this->objects.clear();
    std::cout << "Client stopped.\n";
}

bool Client::send_all_bytes(const void *data, std::size_t size, sf::TcpSocket &sock) {
    std::size_t total_sent = 0;
    int retries = 0;
    while (total_sent < size) {
        std::size_t sent;
        if (sock.send(static_cast<const char *>(data) + total_sent, size - total_sent, sent) != sf::Socket::Done) {
            if (++retries > 50000) {
                std::cerr << " : too many retries\n";
                return false;
            }
            continue;
        }
        total_sent += sent;
        retries = 0;
    }
    return true;
}

bool Client::receive_all_bytes(void *data, std::size_t size) {
    std::size_t total_received = 0;
    int retries = 0;
    while (total_received < size) {
        std::size_t received = 0;
        auto status = socket.receive(static_cast<char*>(data) + total_received, size - total_received, received);
        if (status != sf::Socket::Done) {
            if (status == sf::Socket::Disconnected) {
                disconnect();
                return true;
            }
            if (++retries > 50000) {
                std::cerr << "Error receiving data: too many retries\n";
                return false;
            }
            #ifdef SERVER_DEBUG
            std::cout << "-" << retries;
            #endif
            continue;
        }
        total_received += received;
        retries = 0;
    }
    #ifdef SERVER_DEBUG
    std::cout << "+";
    #endif
    return true;
}


void Client::receive_data() {
    if (active) {
        MessageType message_type;
        std::uint32_t data_size;

        if (receive_all_bytes(&message_type, sizeof(message_type))) {
            if (message_type == MessageType::ID) {
                if (receive_all_bytes(&id, sizeof(id))) {
                    this->object.id = id;
                    this->object.tick = id;
                } else {
                    std::cerr << "Error receiving id from server\n";
                }
            } else if (message_type == MessageType::OBJECTS) {

                if (receive_all_bytes(&data_size, sizeof(data_size))) {
                    std::vector<char> buff(data_size);
                    if (receive_all_bytes(buff.data(), buff.size())) {
                        object::deserialize_objects(buff, this->objects);
                        for(auto obj = objects.begin(); obj != objects.end();){
                            if(obj->id == object.id){
                                obj = objects.erase(obj);
                            } else {
                                obj++;
                            }
                        }
                    } else {
                        std::cerr << "Error receiving data from Server\n";
                    }
                } else {
                    std::cerr << "Error receiving data size from server\n";
                }
            } else if (message_type == MessageType::EMPTY) {
                if (!objects.empty()) {
                    objects.clear();
                }
            }
        } else {
            std::cerr << "Error receiving message type from server\n";
        }
    }
}

bool Client::send_data() {
    if (active) {
        if (object.id != 0) {
            auto data = object::serialize_object(this->object);
            if (send_all_bytes(data.data(), data.size(), this->socket)) {
                this->object.tick++;
                return true;
            } else {
                std::cerr << "Error sending data to Server\n";
            }
            //disconnect();
        }
        return false;
    }
    return false;
}

void Client::print_vector() {
    std::cout << "\n\nRECEIVING DATA: \n";
    for (auto &obj: this->objects) {
        std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                  << obj.main_menu_action << "\n";
    }
    std::cout << "\n\n";
}