//
// Created by alexey on 4/12/23.
//

#ifndef BLAST_SPRITEMETHODS_H
#define BLAST_SPRITEMETHODS_H

#include <SFML/Graphics.hpp>

void center_sprite_origin(sf::Sprite &sprite);

void center_rect_origin(sf::RectangleShape &shape);

void center_circle_origin(sf::CircleShape &shape);

bool sprite_collision(sf::Sprite& a, sf::Sprite& b, bool a_can_move = true, bool b_can_move = true);

bool rectangle_collision(sf::RectangleShape& a, sf::RectangleShape& b, bool a_can_move = true, bool b_can_move = true);

#endif
