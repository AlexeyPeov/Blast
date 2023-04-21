#include "../Headers/RayCaster.h"

const char* blur_shader_code = R"(
            uniform sampler2D texture;
            uniform vec2 texSize;
            uniform float blurRadius;

            void main() {
                vec2 texCoord = gl_TexCoord[0].xy;
                vec4 color = vec4(0.0);
                float total = 0.0;
                for (float x = -blurRadius; x <= blurRadius; x += 1.0) {
                    for (float y = -blurRadius; y <= blurRadius; y += 1.0) {
                        vec2 offset = vec2(x, y) / texSize;
                        color += texture2D(texture, texCoord + offset);
                        total += 1.0;
                    }
                }
                gl_FragColor = color / total;
    }
)";

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
                  std::unordered_map<sf::Vector2f, Wall, Vector2fHash> &walls) {
//        sf::Shader blurShader;
//        if (!blurShader.loadFromMemory(blur_shader_code, sf::Shader::Fragment)) {
//            // Handle error
//        }
//
//        blurShader.setUniform("texture", renderTexture.getTexture());
//        blurShader.setUniform("texSize", sf::Vector2f(renderTexture.getSize()));
//        blurShader.setUniform("blurRadius", 2.f);


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
            line[0].color = sf::Color(200, 200, 200, 15);
            line[1].color = sf::Color(200, 200, 200, 35);
            renderTexture.draw(line, 2, sf::Lines);
        }
    }

}