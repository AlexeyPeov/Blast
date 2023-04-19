#pragma once

#include "SFML/Graphics.hpp"

namespace KeyBoard{
    static bool keyClicked(sf::Keyboard::Key key) {
        static bool wasClicked = false;
        if (sf::Keyboard::isKeyPressed(key)) {
            if (!wasClicked) {
                wasClicked = true;
                return true;
            }
        } else {
            wasClicked = false;
        }
        return false;
    }
}