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

    static bool send_all_bytes(const void* data, std::size_t size, sf::TcpSocket &sock) {
        std::size_t total_sent = 0;
        int retries = 0;
        while (total_sent < size) {
            std::size_t sent;
            if (sock.send(static_cast<const char*>(data) + total_sent, size - total_sent, sent) != sf::Socket::Done) {
                if (++retries > 3) {
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

    void receive_data() {
        if (active) {
            MessageType message_type;
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;

            if (this->socket.receive(&message_type, sizeof(message_type), data_len) == sf::Socket::Done) {

                if (message_type == MessageType::ID) {
                    if (socket.receive(&id, sizeof(id), data_len) == sf::Socket::Done) {
                        this->object.id = id;
                    } else {
                        std::cerr << "Error receiving id from server\n";
                    }

                } else if (message_type == MessageType::OBJECTS) {
                    auto status = this->socket.receive(buffer, sizeof(buffer), data_len);

                    if (status == sf::Socket::Done && data_len > 0) {
                        std::vector<char> data(buffer, buffer + data_len);
                        object::deserialize_objects(data, this->objects);
                    } else if (status == sf::Socket::NotReady || status == sf::Socket::Partial) {
                        std::cerr << "No data received..\n";
                    } else if(status == sf::Socket::Disconnected){
                        std::cerr << "Server disconnected...\n";
                        disconnect();
                    }
                    else {
                        std::cerr << "Error receiving data from Server\n";
                    }
                }
            }
        }
    }

    bool send_data() {
        if (active) {
            auto data = object::serialize_object(this->object);
            if (send_all_bytes(data.data(), data.size(), this->socket)){
                return true;
            }
            std::cerr << "Error sending data to Server\n";
            disconnect();
            return false;
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