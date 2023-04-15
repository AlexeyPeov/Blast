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
    int new_client_id = 0;
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

    int assign_id (){
        new_client_id += 1;
        return new_client_id;
    }

    bool receive_data() {
        for (auto client = clients.begin(); client != clients.end();) {
            //std::cout << "SERVER RECEIVING DATA FROM CLIENT\n";
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;
            auto status = (*client)->socket.receive(buffer, sizeof(buffer), data_len);
            //std::cout << "WRITING TO BUFFER INSIDE SERVER::RECEIVE_DATA, clients.size(): " << clients.size() << " \n";
            if (status == sf::Socket::Done) {
                // Data was received
                //std::cout << "Received " << data_len << " bytes from client: ";
                std::vector<char> data(buffer, buffer + data_len);
                object::deserialize_object(data, (*client)->object);
              //  std::cout << "Id :" << (*client)->object.id << " posx: " << (*client)->object.pos_x << " posy: " << (*client)->object.pos_y << " action : " << (*client)->object.action << "\n";
                client++;
              //  std::cout << "IDK..\n";
                continue;
            } else if (status == sf::Socket::Disconnected) {
             //   std::cout << "ERASING OBJECT AND CLIENT DATA FROM SERVER\n";
                objects.erase((*client)->id);
                client = clients.erase(client);
                std::cout << "SOCKET DISCONNECTED\n";
            } else {
                client++;
             //   puts("DIDNT RECIEVE DATA FROM CLIENT");
                return false;
            }
        }
        return true;
    }

    bool send_data() {
        auto new_client = std::make_unique<Client>();
        new_client->socket.setBlocking(false);
        MessageType message_type;
        if (listener.accept(new_client->socket) == sf::Socket::Done) {
            // A new connection was accepted, add it to the container
            message_type = MessageType::ID;
            new_client->id = assign_id();
            new_client->object.id = new_client->id;

            if (new_client->socket.send(&message_type, sizeof(message_type)) != sf::Socket::Done ||
                new_client->socket.send(&new_client->id, sizeof(new_client->id)) != sf::Socket::Done) {
                //std::cerr << "Error sending id to client\n";
            } else {
                //std::cout << "sent id to client, id = " << new_client_id << "\n";
                clients.push_back(std::move(new_client));
                std::cout << "NEW CLIENT CONNECTED!\n";
            }
            //return true;
        }
        message_type = MessageType::OBJECTS;


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
                objects[client->id] = client->object;
                //std::cout << "\n\nADDED/MODIFIED OBJECT TO SERVER'S OBJECTS: \n";
                //std::cout << "ID: " << client->id << " POSx: " << client->object.pos_x << "\n" << "SERVER'S OBJECT'S SIZE: " << objects.size() << "\n\n";
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

            //std::cout << "\nWHAT TO SEND TO CLIENT " << (*client)->id << "\n\n";

            for (auto& object: objects) {
                if (object.first != (*client)->id) {
                    (*client)->objects.push_back(object.second);
                  //  std::cout <<"id: " <<  object.second.id << " posx: " << object.second.pos_x << " posy: " << object.second.pos_y << "\n";
                }
            }

            auto data = object::serialize_objects((*client)->objects);
            if (!data.empty()) {
                if ((*client)->socket.send(&message_type, sizeof(message_type)) == sf::Socket::Done &&
                    (*client)->socket.send(data.data(), data.size()) == sf::Socket::Done) {
                   // puts("SENT DATA TO CLIENT!\n");
                } else {
                   // std::cerr << "Error sending data to client\n";
                }
            }
            client++;
        }
        return true;
    }
};

