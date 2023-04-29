//
// Created by alexey on 4/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>

struct Entity {
    sf::Sprite sprite;
    float movement_speed;
    float rotation_degree;

    bool move(sf::Vector2f &mouse_position);

};

