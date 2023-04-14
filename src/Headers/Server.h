#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Client.h"



struct Server {
    sf::TcpListener listener;
    std::vector<std::unique_ptr<Client>> clients;
    std::unordered_map<int, Object> objects;
    bool active = false;

    bool set_listener() {
        listener.setBlocking(false);
        if (listener.listen(53000) != sf::Socket::Done) {
            std::cerr << "Error setting up listener\n";
            return false;
        }
        this->active = true;
        std::cout << "Server running..\n";
        return active;
    }

    bool receive_data() {
        for (auto client = clients.begin(); client != clients.end();) {
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;
            auto status = (*client)->socket.receive(buffer, sizeof(buffer), data_len);
            if (status == sf::Socket::Done) {
                // Data was received
                std::cout << "Received " << data_len << " bytes from client: ";
                std::vector<char> data(buffer, buffer + buffer_length);
                object::deserialize_object(data, (*client)->object);
                client++;
            } else if (status == sf::Socket::Disconnected) {
                objects.erase((*client)->object.id);
                client = clients.erase(client);
                std::cout << "SOCKET DISCONNECTED\n";
            } else {
                client++;
                puts("DIDNT RECIEVE DATA FROM CLIENT");
                return false;
            }
        }
        return true;
    }

    bool send_data() {
        auto new_client = std::make_unique<Client>();
        new_client->socket.setBlocking(false);
        if (listener.accept(new_client->socket) == sf::Socket::Done) {
            // A new connection was accepted, add it to the container
            clients.push_back(std::move(new_client));
            std::cout << "NEW CLIENT CONNECTED!\n";
        }


        /*
             * Update server's objects HashMap.
             *
             *  HashMap<Object> objects;
             *
             *  foreach client in clients
             *      objects[id] = client.object
             *  end
             *
             * */



        for (auto& client : clients){
            if (client->object.id != 0){
                objects[client->object.id] = client->object;
                std::cout << "\n\nADDED/MODIFIED OBJECT TO SERVER'S OBJECTS: \n";
                std::cout << "ID: " << client->object.id << " POSx: " << client->object.pos_x << "\n" << "SERVER'S OBJECT'S SIZE: " << objects.size() << "\n\n";
            }
        }


        for (auto client = clients.begin(); client != clients.end();) {
            /*
             * update each client's objects.
             *  client.objects.delete
             *  for object in objects
             *      client.objects = object
             *
             * */

            (*client)->objects.clear();

            std::cout << "\nWHAT TO SEND TO CLIENT " << (*client)->object.id << "\n\n";

            for (auto& object: objects) {
                if (object.second.id != (*client)->object.id) {
//                    std::cout << "ID: " << object.second.id << " POSX: " << object.second.pos_x << " POSY: " << object.second.pos_y << " ACTION: "
//                              << object.second.action << "\n";

                    //std::cout << "OBJECT ID: " << object.second.id << " CLIENT'S OBJECT'S ID: "<< (*client)->object.id << "\n";
                    (*client)->objects.push_back(object.second);
                }
            }

            auto data = object::serialize_objects((*client)->objects);
            if (data.empty()) {
                puts("DATA IS EMPTY, NOTHING TO SEND\n");
            } else if ((*client)->socket.send(data.data(), data.size()) == sf::Socket::Done) {
                puts("SENT DATA TO CLIENT!\n");
            } else {
                std::cerr << "Error sending data to client\n";
            }
            client++;
        }
        return true;
    }
};

