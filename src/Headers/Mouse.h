
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

    static bool clicked() {
        static bool wasPressed = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!wasPressed) {
                wasPressed = true;
                return true;
            }
        } else {
            wasPressed = false;
        }
        return false;
    }
}

#endif