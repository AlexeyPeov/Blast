#include "../Headers/SpriteMethods.h"

void center_sprite_origin(sf::Sprite &sprite){
    sprite.setOrigin((float)sprite.getTexture()->getSize().x / 2.f, (float)sprite.getTexture()->getSize().y / 2.f);
}

void center_rect_origin(sf::RectangleShape &shape){
    if (shape.getTexture()) {
        shape.setOrigin((float)shape.getTexture()->getSize().x / 2.f, (float)shape.getTexture()->getSize().y / 2.f);
    } else {
        shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
    }
}

void center_circle_origin(sf::CircleShape &shape){
    shape.setOrigin(shape.getRadius(), shape.getRadius());
}

bool sprite_collision(sf::Sprite& a, sf::Sprite& b, bool a_can_move, bool b_can_move) {
    if (a.getGlobalBounds().intersects(b.getGlobalBounds())) {

        sf::FloatRect overlap;
        a.getGlobalBounds().intersects(b.getGlobalBounds(), overlap);

        sf::Vector2f push;
        if (overlap.width < overlap.height) {
            push.x = overlap.width * (a.getPosition().x < b.getPosition().x ? -1 : 1);
        } else {
            push.y = overlap.height * (a.getPosition().y < b.getPosition().y ? -1 : 1);
        }

        // Push back the sprites
        if (a_can_move && b_can_move) {
            a.move(push / 2.0f);
            b.move(-push / 2.0f);
        } else if (a_can_move) {
            a.move(push);
        } else if (b_can_move) {
            b.move(-push);
        }

        return true;
    }
    return false;
}

bool rectangle_collision(sf::RectangleShape& a, sf::RectangleShape& b, bool a_can_move, bool b_can_move) {
    if (a.getGlobalBounds().intersects(b.getGlobalBounds())) {

        sf::FloatRect overlap;
        a.getGlobalBounds().intersects(b.getGlobalBounds(), overlap);

        sf::Vector2f push;
        if (overlap.width < overlap.height) {
            push.x = overlap.width * (a.getPosition().x < b.getPosition().x ? -1 : 1);
        } else {
            push.y = overlap.height * (a.getPosition().y < b.getPosition().y ? -1 : 1);
        }

        // Push back the sprites
        if (a_can_move && b_can_move) {
            a.move(push / 2.0f);
            b.move(-push / 2.0f);
        } else if (a_can_move) {
            a.move(push);
        } else if (b_can_move) {
            b.move(-push);
        }

        return true;
    }
    return false;
}

sf::RectangleShape get_rectangle_from_sprite(sf::Sprite &sprite){
    center_sprite_origin(sprite); // just in case.. you may never know..
    sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
    sf::RectangleShape rectangle(sf::Vector2f(sprite_bounds.width, sprite_bounds.height));
    rectangle.setPosition(sprite.getPosition());
    rectangle.setOrigin(sprite.getOrigin());
    rectangle.setRotation(sprite.getRotation());
    rectangle.setScale(sprite.getScale());
    return rectangle;
}