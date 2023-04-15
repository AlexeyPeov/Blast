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
        this->listener.setBlocking(false);
        if (this->listener.listen(53000) != sf::Socket::Done) {
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

    static bool send_all_bytes(const void* data, std::size_t size, sf::TcpSocket &socket) {
        std::size_t total_sent = 0;
        int retries = 0;
        while (total_sent < size) {
            std::size_t sent;
            if (socket.send(static_cast<const char*>(data) + total_sent, size - total_sent, sent) != sf::Socket::Done) {
                if (++retries > 3) {
                    std::cerr << "Error sending data: too many retries\n";
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
        for (auto client = clients.begin(); client != clients.end();) {
            int buffer_length = max_players * sizeof(Object);
            char buffer[buffer_length];
            std::size_t data_len = 0;
            auto status = (*client)->socket.receive(buffer, sizeof(buffer), data_len);
            if (status == sf::Socket::Done) {
                std::vector<char> data(buffer, buffer + data_len);
                object::deserialize_object(data, (*client)->object);
                client++;
            } else if (status == sf::Socket::Disconnected) {
                std::cout << "ERASING OBJECT AND CLIENT DATA FROM SERVER\n";
                objects.erase((*client)->id);
                client = clients.erase(client);
                std::cout << "SOCKET DISCONNECTED\n";
            } else {
                client++;
                puts("DIDNT RECEIVE DATA FROM CLIENT");
            }
        }
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

            if(!send_all_bytes(&message_type, sizeof(message_type), new_client->socket) ||
            !send_all_bytes(&new_client->id, sizeof(new_client->id), new_client->socket)) {
                std::cerr << "Error sending id to client\n";
            } else {
                clients.push_back(std::move(new_client));
                std::cout << "NEW CLIENT CONNECTED!\n";
            }
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

            for (auto& [object_id, object]: objects) {
                if (object_id != (*client)->id) {
                    (*client)->objects.push_back(object);
                }
            }
            auto data = object::serialize_objects((*client)->objects);
            if (!data.empty()) {
                if(!send_all_bytes(&message_type, sizeof(message_type), (*client)->socket) ||
                   !send_all_bytes(data.data(), data.size(), (*client)->socket)) {
                    std::cerr << "Sent data to client, with id: " << (*client)->id << "\n";
                } else {
                    std::cerr << "Error sending data to client, with id: " << (*client)->id << "\n";
                }
            }
            client++;
        }
        return true;
    }
};

