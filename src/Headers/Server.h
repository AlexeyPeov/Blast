#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <csignal>

#include <SFML/Network.hpp>
#include "Client.h"
#include "Map.h"
#include "Takeover.h"




//#define SERVER_DEBUG_SEND // if on,  prints server debug info into console
//#define SERVER_DEBUG_RECEIVE

using namespace obj;

struct Server {
    sf::UdpSocket server_socket;

    std::unordered_map<uint64, std::unique_ptr<Client>> clients;

    uint64 host_client_id = 0;

    std::unordered_map<uint64, PlayerObject> player_objects;
    std::unordered_map<uint64, MissileObject> missile_objects;
    BombObject bomb_object;

    //std::unordered_map<uint64_t, std::pair<std::unordered_map<uint64_t, Object>, uint8_t>> packets;
    bool active = false;
    uint64 tick = 0;

    // receive data
    // run game loop
    // send data
    Map map;
    Takeover takeover;


    Server() = default;

    ~Server() = default;

    bool set_listener();

    void receive_data();

    bool send_data();


    void disconnect();

    void play_tick();

    void death_match();

    void takeover_game_mode();

};

#endif