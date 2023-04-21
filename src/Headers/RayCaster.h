#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"

const float PI = 3.14159265f;
const float BIG_FLOAT_NUMBER = 400000000.0;


namespace RayCaster {

    float distanceToScene(sf::Vector2f point, std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls);

    void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f &playerPos,
                  std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls);





}