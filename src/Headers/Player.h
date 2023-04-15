#pragma once
#include <utility>

#include "Entity.h"

struct Player : Entity {
    int id = 0;
    int hp = 0;
    int shootDelay = 60;
    int timeSinceLastShot = 0;

    Player(){}
    Player(sf::Sprite sprite, float movement_speed, int rotation_degree, int hp, int id)
        : Entity{ std::move(sprite), movement_speed, rotation_degree}, hp{hp}, id{id}{}

};
