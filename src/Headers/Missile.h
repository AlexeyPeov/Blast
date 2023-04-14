#pragma once

#include <utility>

#include "Entity.h"

struct Missile : Entity {

    bool life = true;
    sf::Vector2f previousPosition = {0,0};

    Missile(sf::Sprite sprite, int movement_speed, int rotation_degree)
    : Entity{ std::move(sprite), movement_speed, rotation_degree} {}
};