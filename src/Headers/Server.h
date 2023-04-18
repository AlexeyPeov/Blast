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

    bool set_listener();

    int assign_id ();

    static bool send_all_bytes(const void* data, std::size_t size, sf::TcpSocket &socket);

    void receive_data();

    bool send_data();

    void printObjects();
};

