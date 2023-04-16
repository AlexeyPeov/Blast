#include "SFML/Graphics.hpp"

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

    void init(sf::Font &font){
        box.setFillColor(sf::Color::Black);
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        text.setFont(font);
        text.setString("");
        cursor.setCharacterSize(12);
        cursor.setFillColor(sf::Color::White);
        cursor.setFont(font);
        cursor.setString("|");
    }

    void setPosition(float x, float y, float width, float height) {
        box.setSize(sf::Vector2f (width,height));
        box.setPosition(x, y);
        text.setPosition(box.getPosition().x + 4, box.getPosition().y + 2);
        cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, text.getPosition().y);

    }

    void handleEvent(sf::Event &event) {
        if(active){
            if (event.type == sf::Event::TextEntered) {
                // Handle backspace
                if (event.text.unicode == 8 && !inputString.empty()) {
                    inputString.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != 8 && inputString.size() < 15) {
                    // Append entered character to inputString
                    inputString += static_cast<char>(event.text.unicode);
                }
                text.setString(inputString);
                cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, text.getPosition().y);
            }
        }
    }

    void clearInput(){
        inputString = "";
        text.setString(inputString);
    }

    void update(sf::RenderWindow &window, float deltaTime = 0.5f) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mp = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mp);
            if (box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                active = true;
                box.setOutlineColor(sf::Color::Yellow);
            } else {
                active = false;
                box.setOutlineColor(sf::Color::White);
            }
        }
        if (active) {
            elapsedTime += deltaTime;
            if (elapsedTime >= blinkTime) {
                elapsedTime -= blinkTime;
                cursor.setString(cursor.getString() == "|" ? "" : "|");
            }
        } else {
            cursor.setString("");
        }
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(box);
        window.draw(text);
        window.draw(cursor);
    }

    int toInt() const{
        return std::stoi(this->inputString);
    }


};