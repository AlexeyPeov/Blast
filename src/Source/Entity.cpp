//
// Created by alexey on 4/12/23.
//

#include <valarray>
#include "../Headers/Entity.h"

void Entity::move(sf::Vector2f &mouse_position) {

    float angle =
            (atan2(mouse_position.y - this->sprite.getPosition().y,
                  mouse_position.x - this->sprite.getPosition().x
                  ) * 180 / M_PI) + 90;
    this->sprite.setRotation(angle);

    // Move sprite based on keyboard input
    sf::Vector2f movement = {0,0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += 1;
    }

    // Normalize movement vector
    float length = sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length > 0) {
        movement /= length;
        this->sprite.move(movement.x * this->movement_speed,movement.y * this->movement_speed );
    }
}


