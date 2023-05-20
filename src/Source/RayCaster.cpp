#include "../Headers/RayCaster.h"

namespace RayCaster {


    float distanceToScene(sf::Vector2f point, std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls) {

        sf::Vector2f theoretical_pos = sf::Vector2f(((int) point.x / 40) * 40 + 20, ((int) point.y / 40) * 40 + 20);
        float distance = BIG_FLOAT_NUMBER;
        if (walls.count(theoretical_pos) > 0) {
            sf::FloatRect wallBounds = walls[theoretical_pos].sprite.getGlobalBounds();
            distance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
                                std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
        }
        return distance;
    }

    void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f &playerPos,
                  std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls, float player_angle) {

        sf::RenderStates render;
        render.blendMode = sf::BlendNone;

        const int step_distance = 3;


        for (int i = 0; i < num_rays; i++) {
            float angle = player_angle + static_cast<float>(i) / num_rays * 135.f;
            float dx = cos(angle * PI / 180.f);
            float dy = sin(angle * PI / 180.f);

            // March the ray
            sf::Vector2f rayPos = playerPos;
            for (int j = 0; j < maxSteps; j++) {
                float distance = distanceToScene(rayPos, walls);
                if (distance < 1.f) {
                    break;
                }
                if (distance == BIG_FLOAT_NUMBER) {
                    rayPos.x += dx * step_distance;
                    rayPos.y += dy * step_distance;

                    continue;
                }
            }


//            sf::Vertex line[] = {
//                    sf::Vertex(playerPos),
//                    sf::Vertex(rayPos)
//            };
//            line[0].color = sf::Color(255, 255, 255, 100);
//            line[1].color = sf::Color(255, 255, 255, 100);
//            renderTexture.draw(line, 2, sf::Lines);
            sf::Vector2f lineVector = sf::Vector2f(rayPos.x + dx * 5, rayPos.y + dy * 5) - playerPos;
            float lineLength = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);

            sf::RectangleShape line(sf::Vector2f(lineLength, 5));

            line.setPosition(playerPos);
            line.setRotation(angle);
            line.setFillColor(sf::Color(255, 255, 255, 15));
            renderTexture.draw(line, render);
        }
    }

}