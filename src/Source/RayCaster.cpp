#include "../Headers/RayCaster.h"

const char *blur_shader_code = R"(
            uniform sampler2D texture;
uniform vec2 texSize;
uniform float blurRadius;

const int MAX_SAMPLES = 20;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);

    // Calculate the number of pixels to sample
    int sampleCount = int(blurRadius * 2.0 + 1.0);
    sampleCount = min(sampleCount, MAX_SAMPLES);

    // Calculate the weights for each pixel
    float sigma = blurRadius / 2.0;
    float weightSum = 0.0;
    float weights[MAX_SAMPLES];
    for (int i = 0; i < sampleCount; i++) {
        float x = float(i) - blurRadius;
        weights[i] = exp(-(x * x) / (2.0 * sigma * sigma));
        weightSum += weights[i];
    }

    // Normalize the weights
    for (int i = 0; i < sampleCount; i++) {
        weights[i] /= weightSum;
    }

    // Sample the pixels and apply the weights
    for (int i = 0; i < sampleCount; i++) {
        float x = float(i) - blurRadius;
        vec2 offset = vec2(x / texSize.x, 0.0);
        color += texture2D(texture, texCoord + offset) * weights[i];
    }

    gl_FragColor = color;
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

        sf::Shader blurShader;
        if (!blurShader.loadFromMemory(blur_shader_code, sf::Shader::Fragment)) {
            std::cerr << "DIDNT OPEN THE SHADER\n";
        }
        sf::RenderStates render;
        render.blendMode = sf::BlendNone;

        const int maxSteps = 250;
        const int step_distance = 3;


        for (int i = 0; i < num_rays; i++) {
            float angle = static_cast<float>(i) / num_rays * 360.f;
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
//            line[0].color = sf::Color(255, 255, 255, 35);
//            line[1].color = sf::Color(255, 255, 255, 55);
//            renderTexture.draw(line, 2, sf::Lines);
            sf::Vector2f lineVector = sf::Vector2f(rayPos.x + dx * 5, rayPos.y + dy * 5) - playerPos;
            float lineLength = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);

            sf::RectangleShape line(sf::Vector2f(lineLength, 2));

            line.setPosition(playerPos);
            line.setRotation(angle);
            line.setFillColor(sf::Color(255, 255, 255, 15));
            renderTexture.draw(line, render);
        }
    }

}