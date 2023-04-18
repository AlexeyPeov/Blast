#include "../Headers/InputText.h"


void InputText::init(sf::Font &font) {
    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(3);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setString("");
    cursor.setCharacterSize(36);
    cursor.setFillColor(sf::Color::White);
    cursor.setFont(font);
    cursor.setString("|");
}

void InputText::setPosition(float x, float y, float width, float height) {
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(x, y);
    text.setPosition(box.getPosition().x + 4, box.getPosition().y + 2);
    cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, text.getPosition().y);

}

void InputText::handleEvent(sf::Event &event) {
    if (active) {
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

void InputText::clearInput() {
    inputString = "";
    text.setString(inputString);
}

void InputText::update(sf::RenderWindow &window, float deltaTime) {
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

int InputText::toInt() const {
    try {
        int value = std::stoi(inputString);
        return value;
    } catch (const std::invalid_argument &e) {
        return 0;
    }
}

void InputText::draw(sf::RenderWindow &window) const {
    window.draw(box);
    window.draw(text);
    window.draw(cursor);
}
