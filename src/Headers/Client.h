#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Object.h"

//#define CLIENT_DEBUG_SEND
//#define CLIENT_DEBUG_RECEIVE

using namespace object;

struct MessageType {
    static const uint8_t ID = 1;
    static const uint8_t TICK = 2;
    static const uint8_t OBJECTS = 3;
    static const uint8_t OBJECT = 4;
    static const uint8_t DISCONNECT = 5;
    static const uint8_t EMPTY = 6;
};

const size_t max_players = 24;

struct Client {

    uint64_t id = 0;
    sf::UdpSocket socket;
    sf::IpAddress client_ip;
    sf::IpAddress host_ip;
    uint16_t host_port = 53000;
    std::vector<Object> objects;

    Object object;
    bool active = false;
    bool host = false;

    Client(){}
    ~Client(){}

    Client(uint64_t id, sf::IpAddress host_ip, sf::IpAddress client_ip, uint16_t port){
        this->id = id;
        this->host_ip = host_ip;
        this->client_ip = client_ip;
        this->host_port = port;
    }

    bool connect(sf::IpAddress address, uint16_t port);

    void disconnect();

    void receive_data();

    void send_data();



    //static bool send_all_bytes(const void* data, std::size_t size, sf::UdpSocket &sock);

    //bool receive_all_bytes(void* data, std::size_t size);

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