#include "../Headers/RayCaster.h"

namespace RayCaster {
/*

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

    void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f &playerPos, const std::vector<Wall> &walls) {

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
    }
*/


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
                  std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls) {

        const int numRays = 360;
        const int maxSteps = 60;
        const int step_distance = 10;

        for (int i = 0; i < numRays; i++) {
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
                if (distance == BIG_FLOAT_NUMBER) {
                    rayPos.x += dx * step_distance;
                    rayPos.y += dy * step_distance;

                    continue;
                }
            }
            sf::Vertex line[] = {
                    sf::Vertex(playerPos),
                    sf::Vertex(rayPos)
            };
            line[0].color = sf::Color::White;
            line[1].color = sf::Color(200, 200, 200);
            renderTexture.draw(line, 2, sf::Lines);
        }
    }

}
/*
    sf::Vector2f closestWall(sf::Vector2f point, float angle,
                                std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls) {
        float minDistance = std::numeric_limits<float>::max();
        sf::Vector2i rayPos = sf::Vector2i((int) point.x, (int) point.y);
        const float maxDistance = 40.f;
        float dx = cos(angle * PI / 180.f);
        float dy = sin(angle * PI / 180.f);
        //dy = -dy;
        // if found
        float currentDistance = 0.f;

        //starting pos
        float x = point.x, y = point.y;


        while (currentDistance <= maxDistance) {
            // нужен х и у
            // считать х *= dx; y *= dy;
            // if x /40 * 40 + 20 .. touches wall, distance = formula()

            x = x + (x * dx);
            y = y + (y * dy);
            int int_x = (int) x;
            int int_y = (int) y;

            sf::Vector2f theoretical_pos = sf::Vector2f((int_x / 40) * 40 + 20, (int_y / 40) * 40 + 20);

            if (walls.count(theoretical_pos) > 0) {
                sf::FloatRect wallBounds = walls[theoretical_pos].sprite.getGlobalBounds();
                float distance = std::max(
                        std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
                        std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));

                x = point.x
                break;
            }

//
//
//
//            sf::Vector2i wallPosition(((rayPos.x / 40) * 40) + 20, ((rayPos.y / 40) * 40) + 20);
//            if (walls.count(sf::Vector2f(wallPosition.x, wallPosition.y)) > 0) {
//                sf::FloatRect wallBounds = walls[sf::Vector2f(wallPosition)].sprite.getGlobalBounds();
//                float distance = std::max(
//                        std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
//                        std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
//                minDistance = std::min(minDistance, distance);
//                break;
//            }
//            if (dx > 0) { rayPos.x = wallPosition.x + 140; } else if (dx < 0) { rayPos.x = wallPosition.x - 40; }
//            if (dy < 0) { rayPos.y = wallPosition.y + 140; } else if (dy > 0) { rayPos.y = wallPosition.y - 40; }
            currentDistance += 40;
            //std::sqrt(std::pow(nextRayPos.x - rayPos.x, 2) + std::pow(nextRayPos.y - rayPos.y, 2));
        }
        return {x,y};
    }*/

    /* float distanceToClosestWall(sf::Vector2f point, float angle, std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls) {
         float minDistance = std::numeric_limits<float>::max();
         sf::Vector2f rayPos = point;
         const float maxDistance = 1000.f;

         float dx = sin(angle * PI / 180.f);
         float dy = cos(angle * PI / 180.f);

         // if found


         float currentDistance = 0.f;
         while (currentDistance <= maxDistance) {
             sf::Vector2i wallPosition((((int)rayPos.x / 40) * 40) + 20, (((int)rayPos.y / 40) * 40) + 20);
             if (walls.count(sf::Vector2f (wallPosition.x, wallPosition.y))> 0) {
                 sf::FloatRect wallBounds = walls[sf::Vector2f(wallPosition)].sprite.getGlobalBounds();
                 minDistance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
                                           std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
                 //minDistance = std::min(minDistance, distance);
                 break;
             }

             sf::Vector2f nextRayPos = rayPos;
             if (dx > 0) {
                 nextRayPos.x = rayPos.x + (rayPos.x * dx);
             } else if (dx < 0) {
                 nextRayPos.x = rayPos.x - (rayPos.x * dx);
             }
             if (dy < 0) {
                 nextRayPos.y = rayPos.y + (rayPos.y * dx);
             } else if (dy > 0) {
                 nextRayPos.y = rayPos.y - (rayPos.y * dx);
             }




             currentDistance += std::sqrt(std::pow(nextRayPos.x - rayPos.x, 2) + std::pow(nextRayPos.y - rayPos.y, 2));
             rayPos = nextRayPos;
         }
         return minDistance;
     }*/

/*    void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f &playerPos,
                  std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls) {
        // Create a render texture
        // Number of rays to cast
        const int numRays = 2;
        // Maximum distance a ray can travel
        const float maxDistance = 1000.f;

        // Maximum number of steps for each ray
        //const int maxSteps = 20;

        for (int i = 0; i < numRays; i++) {
            // Calculate the direction of the ray
            float angle = (static_cast<float>(i) / numRays * 360.f) + 90;
            float dx = sin(angle * PI / 180.f);
            float dy = cos(angle * PI / 180.f);
            dy = -dy;

            sf::Vector2f collide_pos = closestWall(playerPos, angle, walls);




            //rayPos = sf::Vector2f (playerPos.x + 150, playerPos.y + 150);
            // Draw the ray onto the render texture
            sf::Vertex line[] = {
                    sf::Vertex(playerPos),
                    sf::Vertex(collide_pos)
            };
            line[0].color = sf::Color::White;
            line[1].color = sf::Color(200, 200, 200);
            //window.draw(line, 2, sf::Lines);
            renderTexture.draw(line, 2, sf::Lines);
        }
    }*/
/*
      float distanceToScene(sf::Vector2f point, const std::vector<Player> &walls) {
          float minDistance = std::numeric_limits<float>::max();
          for (const auto &wall: walls) {
              sf::FloatRect wallBounds = wall.sprite.getGlobalBounds();
              float distance = std::max(std::max(wallBounds.left - point.x, point.x - wallBounds.left - wallBounds.width),
                                        std::max(wallBounds.top - point.y, point.y - wallBounds.top - wallBounds.height));
              minDistance = std::min(minDistance, distance);
          }
          return minDistance;
      }

    void castRays(sf::RenderTexture &renderTexture, const sf::Vector2f& playerPos, const std::vector<Player>& walls) {
        // Create a render texture
        // Number of rays to cast
        const int numRays = 120;

        // Maximum distance a ray can travel
        const float maxDistance = 1000.f;

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
    }*/
