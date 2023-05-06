#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
struct InputText {

    sf::RectangleShape box;
    sf::Text text = sf::Text();
    sf::Text cursor = sf::Text();
    std::string inputString;
    bool active = false;
    float elapsedTime = 0.0f;
    float blinkTime = 4.0f;

    InputText()= default;
    ~InputText()= default;

    void init(sf::Font &font, std::string str);

    void setPosition(float x, float y, float width, float height);

    void handleEvent(sf::Event &event);

    void clearInput();

    void update(sf::RenderWindow &window, float deltaTime = 0.5f);

    int toInt() const;

    void draw(sf::RenderWindow &window) const;

    uint16_t toUint16() const;
};