#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Object.h"

const size_t max_players = 24;

struct Client{
    sf::TcpSocket socket;
    std::vector<Object> objects;
    Object object;
    bool active = false;
    bool connected = false;

    bool connect(std::string address, int port){
        if (socket.connect(address, port) != sf::Socket::Done) {
            std::cerr << "Error connecting to Server\n";
            this->connected = false;
            return false;
        }
        this->active = true;
        this->connected = true;
        return active;
    }

    bool receive_data() {
        if(connected){
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;
            auto status = this->socket.receive(buffer, sizeof(buffer), data_len);
            if (status == sf::Socket::Done) {
                puts ("RECEIVED DATA FROM SERVER\n");
            } else {
                std::cerr << "Error receiving data from Server\n";
                return false;
            }
            std::vector<char> data(buffer, buffer + data_len);
            object::deserialize_objects(data, this->objects);

            print_vector();
            std::cout <<"OBJECTS SIZE: " << objects.size() << "\n";
            return true;
        }
        return false;
    }

    bool send_data(){
        if(connected){
            auto data = object::serialize_object(this->object);

            std::cout << "\n\n";
            for(auto& obj : this->objects){
                std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: " << obj.action << "\n";
            }
            std::cout << "\n\nSENDING DATA: ";

            std::cout << "id: " << this->object.id << " posx: " << this->object.pos_x << " posy : " << this->object.pos_y << " Action: " << this->object.action << "\n";
            std::cout << "\n\n";

            if (socket.send(data.data(), data.size()) != sf::Socket::Done) {
                std::cerr << "Error sending data to Server\n";
                return false;
            }
            return true;
        }
        return false;
    }

    void print_vector(){
        std::cout << "\n\nRECEIVING DATA: \n";
        for(auto& obj : this->objects){
            std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: " << obj.action << "\n";
        }
        std::cout << "\n\n";
    }
};