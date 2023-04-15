#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Object.h"

enum class MessageType {
    ID,
    OBJECTS,
};

const size_t max_players = 24;

struct Client {
    int id = 0;
    sf::TcpSocket socket;
    std::vector<Object> objects;
    Object object;
    bool active = false;

    bool connect(std::string address, int port) {
        this->socket.setBlocking(false);
        if (socket.connect(address, port) != sf::Socket::Done) {
            std::cerr << "Error connecting to Server\n";
            this->active = false;
        }
        this->active = true;
        std::cout << "Client running..\n";
        return active;
    }

    void disconnect(){
        this->active = false;
        this->socket.disconnect();
        std::cout << "Client stopped.\n";
    }

    bool receive_data() {
        if (active) {
            MessageType message_type;
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;

            if (this->socket.receive(&message_type, sizeof(message_type), data_len) == sf::Socket::Done) {

                if (message_type == MessageType::ID) {
                    if (socket.receive(&id, sizeof(id), data_len) == sf::Socket::Done) {
                        std::cout << "Received id from server: " << id << "\n";
                        this->object.id = id;
                        return true;
                    } else {
                        std::cerr << "Error receiving id from server\n";
                        return false;
                    }

                } else if (message_type == MessageType::OBJECTS) {
                    std::cout << "Received objects from server\n";
                    auto status = this->socket.receive(buffer, sizeof(buffer), data_len);

                    if (status == sf::Socket::Done && data_len > 0) {
                        std::cout<< "RECEIVED DATA FROM SERVER, len: " << data_len << "\n";
                        std::vector<char> data(buffer, buffer + data_len);
                        object::deserialize_objects(data, this->objects);
                        print_vector();
                        return true;
                    } else if (status == sf::Socket::NotReady || status == sf::Socket::Partial) {
                        // No data received
                        return true;
                    } else {
                        std::cerr << "Error receiving data from Server\n";
                        return false;
                    }
                }
            } else {
                return false;
            }
        }
        return false;
    }

    bool send_data() {
        if (active) {
            auto data = object::serialize_object(this->object);

            std::cout << "\n\n";
            for (auto &obj: this->objects) {
                std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                          << obj.action << "\n";
            }
            std::cout << "\n\nSENDING DATA: ";

            std::cout << "id: " << this->object.id << " posx: " << this->object.pos_x << " posy : "
                      << this->object.pos_y << " Action: " << this->object.action << "\n";
            std::cout << "\n\n";

            if (socket.send(data.data(), data.size()) != sf::Socket::Done) {
                std::cerr << "Error sending data to Server\n";
                return false;
            }

            std::cout << "END CLIENT SEND DATA, SUCCESS\n";
            return true;
        }
        return false;
    }

    void print_vector() {
        std::cout << "\n\nRECEIVING DATA: \n";
        for (auto &obj: this->objects) {
            std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                      << obj.action << "\n";
        }
        std::cout << "\n\n";
    }
};