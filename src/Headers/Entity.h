//
// Created by alexey on 4/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>

struct Entity {
    sf::Sprite sprite;
    int movement_speed;
    int rotation_degree;

    void move(sf::Vector2f &mouse_position);

};

