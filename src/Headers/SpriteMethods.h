//
// Created by alexey on 4/12/23.
//

#ifndef BLAST_SPRITEMETHODS_H
#define BLAST_SPRITEMETHODS_H

#include <SFML/Graphics.hpp>

void config_sprite(sf::Sprite &sprite);

void center_rect_shape(sf::RectangleShape &shape);

void center_circle_shape(sf::CircleShape &shape);

bool collision(sf::Sprite& a, sf::Sprite& b, bool a_can_move = true, bool b_can_move = true);

#endif
