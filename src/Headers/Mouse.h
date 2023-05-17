
#ifndef MY_MOUSE_H
#define MY_MOUSE_H


#include <SFML/Graphics.hpp>

namespace Mouse{
    static bool cursorCollidesWithItem(sf::Vector2f &mousePos, sf::FloatRect menuItemBounds) {
        return (
                (float) mousePos.x >= menuItemBounds.left &&
                (float) mousePos.x <= menuItemBounds.left + menuItemBounds.width &&
                (float) mousePos.y >= menuItemBounds.top &&
                (float) mousePos.y <= menuItemBounds.top + menuItemBounds.height
        );
    }

    static bool clicked(sf::Mouse::Button button = sf::Mouse::Button::Left) {
        static std::map<sf::Mouse::Button, bool> buttonStates;
        bool isPressed = sf::Mouse::isButtonPressed(button);
        if (isPressed && !buttonStates[button]) {
            buttonStates[button] = true;
            return false;
        }
        if (!isPressed && buttonStates[button]) {
            buttonStates[button] = false;
            return true;
        }
        return false;
    }

}

#endif