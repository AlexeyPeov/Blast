#ifndef MY_KEYBOARD_H
#define MY_KEYBOARD_H

#include <SFML/Graphics.hpp>

namespace KeyBoard{
    static bool keyClicked(sf::Keyboard::Key key) {
        static std::map<sf::Keyboard::Key, bool> keyStates;
        bool isPressed = sf::Keyboard::isKeyPressed(key);
        if (isPressed && !keyStates[key]) {
            keyStates[key] = true;
            return false;
        }
        if (!isPressed && keyStates[key]) {
            keyStates[key] = false;
            return true;
        }
        return false;
    }
}

#endif