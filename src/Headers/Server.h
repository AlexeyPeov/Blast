#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Client.h"
//#define SERVER_DEBUG_SEND // if on,  prints server debug info into console
//#define SERVER_DEBUG_RECEIVE

using namespace object;

struct Server {
    sf::UdpSocket server_socket;
    std::vector<std::unique_ptr<Client>> clients;
    std::unordered_map<uint64_t, Object> objects;
    std::unordered_map<uint64_t, std::pair<std::unordered_map<uint64_t, Object>, uint8_t>> packets;
    bool active = false;
    uint64_t tick = 0;

    // receive data
    // run game loop
    // send data


    bool set_listener();

    void receive_data();

    bool send_data();



    // int assign_id();

    // static bool send_all_bytes(const void* data, std::size_t size, sf::UdpSocket &socket);
    void printObjects();

    void disconnect();
};

