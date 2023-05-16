//
// Created by alexey on 4/12/23.
//
#include "../Headers/Entity.h"

bool Entity::move(bool W, bool S, bool A, bool D) {
    bool moving = false;

    // Move sprite based on keyboard input
    sf::Vector2f movement = {0,0};
    if (W) {
        movement.y -= 1;
        moving = true;
    }
    if (S) {
        movement.y += 1;
        moving = true;
    }
    if (A) {
        movement.x -= 1;
        moving = true;
    }
    if (D) {
        movement.x += 1;
        moving = true;
    }

    // Normalize movement vector
    float length = sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length > 0) {
        movement /= length;
        this->sprite.move(movement.x * this->movement_speed,movement.y * this->movement_speed );
    }

    return moving;
}


