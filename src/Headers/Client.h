#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Object.h"

enum class MessageType {
    ID,
    OBJECTS,
    EMPTY,
};

const size_t max_players = 24;

struct Client {

    int id = 0;
    sf::TcpSocket socket;
    std::vector<Object> objects;
    Object object;
    bool active = false;
    bool host = false;

    bool connect(std::string address, int port);

    void disconnect();

    static bool send_all_bytes(const void* data, std::size_t size, sf::TcpSocket &sock);

    static bool receive_all_bytes(void* data, std::size_t size, sf::TcpSocket &socket);

    void receive_data();

    bool send_data();

    void print_vector();

   /* void receive_data() {
        if (active) {
            MessageType message_type;
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;

            if (this->socket.receive(&message_type, sizeof(message_type), data_len) == sf::Socket::Done) {
                data_len = 0;
                if (message_type == MessageType::ID) {
                    if (socket.receive(&id, sizeof(id), data_len) == sf::Socket::Done) {
                        this->object.id = id;
                    } else {
                        std::cerr << "Error receiving id from server\n";
                    }

                } else if (message_type == MessageType::OBJECTS) {
                    auto status = this->socket.receive(buffer, sizeof(buffer), data_len);
                    if (status == sf::Socket::Done && data_len > 0) {
                        if(data_len % sizeof(Object) != 0){
                            std::cout << "Data length, received by client, bad : " << data_len << " datalen % Objsize: " << data_len % sizeof(Object) << "\n";
                        }
                        std::vector<char> data(buffer, buffer + data_len);
                        object::deserialize_objects(data, this->objects);
                    } else if (status == sf::Socket::NotReady || status == sf::Socket::Partial) {
                        //objects.clear();
                        std::cerr << "No data received..\n";
                    } else if(status == sf::Socket::Disconnected){
                        std::cerr << "Server disconnected...\n";
                        disconnect();
                        this->objects.clear();
                    }
                    else {
                        std::cerr << "Error receiving data from Server\n";
                    }
                    //print_vector();
                } else if(message_type == MessageType::EMPTY){
                    if(!objects.empty()){
                        objects.clear();
                    }
                }
            }
        }
    }*/
   /*    void receive_data() {
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
                         if(data_len % sizeof(Object) != 0){
                             std::cout << "Data length, received by client, bad : " << data_len << " datalen % Objsize: " << data_len % sizeof(Object) << "\n";
                         }
                         std::vector<char> data(buffer, buffer + data_len);
                         object::deserialize_objects(data, this->objects);
                     } else if (status == sf::Socket::NotReady || status == sf::Socket::Partial) {
                         //objects.clear();
                         std::cerr << "No data received..\n";
                     } else if(status == sf::Socket::Disconnected){
                         std::cerr << "Server disconnected...\n";
                         disconnect();
                         this->objects.clear();
                     }
                     else {
                         std::cerr << "Error receiving data from Server\n";
                     }
                     //print_vector();
                 } else if(message_type == MessageType::EMPTY){
                     if(!objects.empty()){
                         objects.clear();
                     }
                 }
             }
         }
     }*/

};