#pragma once

#include <utility>

#include "Entity.h"

struct Missile : Entity {
    bool life = true;
    Player * player_who_shot = nullptr;
    sf::Vector2f previousPosition = {0,0};
    int damage = 25;

    Missile(sf::Sprite sprite, int movement_speed, float rotation_degree)
            : Entity{ std::move(sprite), static_cast<float>(movement_speed), rotation_degree} {
    }
};
