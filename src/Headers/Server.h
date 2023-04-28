#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <csignal>
#include "Client.h"


struct Server {
    sf::TcpListener listener;

    std::vector<std::unique_ptr<Client>> clients;

    std::unordered_map<uint64_t, Object> objects;

   /* std::vector<sf::Vector2f> available_dm_spawn_positions;
    std::vector<std::pair<int, sf::Sprite>> dropped_ammo;
    std::unordered_map<int, Player> players;
    std::vector<Animation> explosions;
    std::vector<Missile> missiles;
    std::unordered_map<sf::Vector2f, Wall, Vector2fHash> walls_for_collision_map;
    std::unordered_map<sf::Vector2f, Wall, Vector2fHash> walls_map;*/

    bool active = false;

    uint64_t tick = 0;



    bool set_listener();

    int assign_id();

    static bool send_all_bytes(const void* data, std::size_t size, sf::TcpSocket &socket);

    void receive_data();

    bool send_data();

    void printObjects();
};

