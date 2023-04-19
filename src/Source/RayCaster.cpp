#include "../Headers/RayCaster.h"

namespace RayCaster{
    float distanceToScene(sf::Vector2f point, const std::vector<Wall> &walls) {
        float minDistance = std::numeric_limits<float>::max();
        for (const auto &wall: walls) {
            sf::FloatRect wallBounds = wall.sprite.getGlobalBounds();
            float distance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
                                      std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
            minDistance = std::min(minDistance, distance);
        }
        return minDistance;
    }


  /*  void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f &playerPos, const std::vector<Wall> &walls) {

        // Number of rays to cast
        const int numRays = 90;

        // Maximum distance a ray can travel
        const float maxDistance = 550.f;

        // Maximum number of steps for each ray
        const int maxSteps = 15;

        for (int i = 0; i < numRays; i++) {
            // Calculate the direction of the ray
            float angle = static_cast<float>(i) / numRays * 360.f;
            float dx = cos(angle * PI / 180.f);
            float dy = sin(angle * PI / 180.f);

            // March the ray
            sf::Vector2f rayPos = playerPos;
            for (int j = 0; j < maxSteps; j++) {
                float distance = distanceToScene(rayPos, walls);
                if (distance < 1.f) {
                    break;
                }
                rayPos.x += dx * distance;
                rayPos.y += dy * distance;
                if (std::hypot(rayPos.x - playerPos.x, rayPos.y - playerPos.y) > maxDistance) {
                    break;
                }
            }

            // Draw the ray onto the render texture
            sf::Vertex line[] = {
                    sf::Vertex(playerPos),
                    sf::Vertex(rayPos)
            };
            renderTexture.draw(line, 2, sf::Lines);
        }
    }*/

    void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f& playerPos, const std::vector<Wall>& walls) {
        // Create a render texture
        // Number of rays to cast
        const int numRays = 50;

        // Maximum distance a ray can travel
        const float maxDistance = 500.f;

        // Maximum number of steps for each ray
        const int maxSteps = 20;

        for (int i = 0; i < numRays; i++) {
            // Calculate the direction of the ray
            float angle = static_cast<float>(i) / numRays * 360.f;
            float dx = cos(angle * PI / 180.f);
            float dy = sin(angle * PI / 180.f);

            // March the ray
            sf::Vector2f rayPos = playerPos;
            for (int j = 0; j < maxSteps; j++) {
                float distance = distanceToScene(rayPos, walls);
                if (distance < 1.f) {
                    break;
                }
                rayPos.x += dx * distance;
                rayPos.y += dy * distance;


                if (std::hypot(rayPos.x - playerPos.x, rayPos.y - playerPos.y) > maxDistance) {
                    break;
                }
            }
            //rayPos = sf::Vector2f (playerPos.x + 150, playerPos.y + 150);
            // Draw the ray onto the render texture
            sf::Vertex line[] = {
                    sf::Vertex(playerPos),
                    sf::Vertex(rayPos)
            };
            line[0].color = sf::Color::White;
            line[1].color = sf::Color(200, 200, 200);
            //window.draw(line, 2, sf::Lines);
            renderTexture.draw(line, 2, sf::Lines);
        }
    }
}