//
// Created by alexey on 4/12/23.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <valarray>

#include <SFML/Graphics.hpp>

struct Entity {
    sf::Sprite sprite;
    float movement_speed;
    float rotation_degree;


    bool move(bool W, bool S, bool A, bool D);
};

#endif

