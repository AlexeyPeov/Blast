#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Map.h"

const float PI = 3.14159265f;

// ray marching
//float distanceToScene(sf::Vector2f point, const std::vector<Wall>& walls) {
//    float minDistance = std::numeric_limits<float>::max();
//    float threshold = 100.f;
//    for (const auto& wall : walls) {
//        if (std::hypot(wall.sprite.getPosition().x - point.x, wall.sprite.getPosition().y - point.y) < threshold) {
//            sf::FloatRect wallBounds = wall.sprite.getGlobalBounds();
//            float distance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
//                                      std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
//            minDistance = std::min(minDistance, distance);
//        }
//    }
//    return minDistance;
//}
//
//float distanceToScene(sf::Vector2f point, const std::vector<Wall> &walls) {
//    float minDistance = std::numeric_limits<float>::max();
//    for (const auto &wall: walls) {
//        sf::FloatRect wallBounds = wall.sprite.getGlobalBounds();
//        float distance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
//                                  std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
//        minDistance = std::min(minDistance, distance);
//    }
//    return minDistance;
//}
//
//
//
//
//void castRays(sf::RenderWindow &window, const sf::Vector2f &playerPos, const std::vector<Wall> &walls) {
//
//    // Number of rays to cast
//    const int numRays = 90;
//
//    // Maximum distance a ray can travel
//    const float maxDistance = 550.f;
//
//    // Maximum number of steps for each ray
//    const int maxSteps = 15;
//
//    for (int i = 0; i < numRays; i++) {
//        // Calculate the direction of the ray
//        float angle = static_cast<float>(i) / numRays * 360.f;
//        float dx = cos(angle * PI / 180.f);
//        float dy = sin(angle * PI / 180.f);
//
//        // March the ray
//        sf::Vector2f rayPos = playerPos;
//        for (int j = 0; j < maxSteps; j++) {
//            float distance = distanceToScene(rayPos, walls);
//            if (distance < 1.f) {
//                break;
//            }
//            rayPos.x += dx * distance;
//            rayPos.y += dy * distance;
//            if (std::hypot(rayPos.x - playerPos.x, rayPos.y - playerPos.y) > maxDistance) {
//                break;
//            }
//        }
//
//        // Draw the ray
//        sf::Vertex line[] = {
//                sf::Vertex(playerPos),
//                sf::Vertex(rayPos)
//        };
//        window.draw(line, 2, sf::Lines);
//    }
//}


//float distanceToScene(sf::RenderWindow &window, sf::Vector2f point, const std::vector<Wall> &walls) {
//    float minDistance = std::numeric_limits<float>::max();
//    for (const auto &wall: walls) {
//        sf::FloatRect wallBounds = wall.sprite.getGlobalBounds();
//        float distance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
//                                  std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
//        minDistance = std::min(minDistance, distance);
//        if (minDistance < 1.f) {
//            window.draw(wall.sprite);
//            break;
//        }
//    }
//    return minDistance;
//}
//
//sf::Vector2f cast_ray(sf::RenderWindow &window, const sf::Vector2f &playerPos, float angle, const std::vector<Wall> &walls) {
//    // Maximum distance a ray can travel
//    const float maxDistance = 640.f;
//
//    // Maximum number of steps for each ray
//    const int maxSteps = 22;
//
//    // Calculate the direction of the ray
//    float dx = cos(angle * PI / 180.f);
//    float dy = sin(angle * PI / 180.f);
//
//    // March the ray
//    sf::Vector2f rayPos = playerPos;
//    for (int j = 0; j < maxSteps; j++) {
//        float distance = distanceToScene(window,rayPos, walls);
//        if (distance < 1.f) {
//            break;
//        }
//        rayPos.x += dx * distance;
//        rayPos.y += dy * distance;
//        if (std::hypot(rayPos.x - playerPos.x, rayPos.y - playerPos.y) > maxDistance) {
//            break;
//        }
//    }
//
//    return rayPos;
//}
//
//void castRays(sf::RenderWindow &window, const sf::Vector2f &playerPos, const std::vector<Wall> &walls) {
//
//    // Number of rays to cast
//    const int numRays = 90;
//
//    for (int i = 0; i < numRays; i++) {
//        // Calculate the direction of the ray
//        float angle = static_cast<float>(i) / numRays * 360.f;
//
//        // Cast the ray
//        sf::Vector2f rayPos = cast_ray(window,playerPos, angle, walls);
//
//        // Draw the ray
//        sf::Vertex line[] = {
//                sf::Vertex(playerPos),
//                sf::Vertex(rayPos)
//        };
//        window.draw(line, 2, sf::Lines);
//    }
//}

//void castRays(sf::RenderWindow& window, const sf::Vector2f& playerPos, const std::vector<Wall>& walls) {
//    // Create a render texture
//    sf::RenderTexture renderTexture;
//    renderTexture.create(window.getSize().x, window.getSize().y);
//
//    // Clear the render texture with a dark color
//    renderTexture.clear(sf::Color(50, 50, 50, 120));
//
//    // Number of rays to cast
//    const int numRays = 50;
//
//    // Maximum distance a ray can travel
//    const float maxDistance = 500.f;
//
//    // Maximum number of steps for each ray
//    const int maxSteps = 20;
//
//    for (int i = 0; i < numRays; i++) {
//        // Calculate the direction of the ray
//        float angle = static_cast<float>(i) / numRays * 360.f;
//        float dx = cos(angle * PI / 180.f);
//        float dy = sin(angle * PI / 180.f);
//
//        // March the ray
//        sf::Vector2f rayPos = playerPos;
//        for (int j = 0; j < maxSteps; j++) {
//            float distance = distanceToScene(rayPos, walls);
//            if (distance < 1.f) {
//                break;
//            }
//            rayPos.x += dx * distance;
//            rayPos.y += dy * distance;
//            if (std::hypot(rayPos.x - playerPos.x, rayPos.y - playerPos.y) > maxDistance) {
//                break;
//            }
//        }
//
//        // Draw the ray onto the render texture
//        sf::Vertex line[] = {
//                sf::Vertex(playerPos),
//                sf::Vertex(rayPos)
//        };
//        line[0].color = sf::Color::White;
//        line[1].color = sf::Color(200, 200, 200);
//        //window.draw(line, 2, sf::Lines);
//        renderTexture.draw(line, 2, sf::Lines);
//    }
//
//    // Draw a semi-transparent black rectangle over the entire screen
//    //sf::RectangleShape darkness(sf::Vector2f(window.getSize().x, window.getSize().y));
//    //darkness.setFillColor(sf::Color(0, 0, 0, 150));
//    //renderTexture.draw(darkness);
//    renderTexture.setSmooth(true);
//    // Draw the render texture onto the screen
//    sf::Sprite sprite(renderTexture.getTexture());
//    //sprite.setPosition(playerPos);
//    window.draw(sprite);
//}

