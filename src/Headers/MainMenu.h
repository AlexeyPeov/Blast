#include <SFML/Graphics.hpp>
#include "InputText.h"
#include "SpriteMethods.h"
#include <iostream>

enum class MenuState {
    MAIN_MENU,
    CHOOSING_GAME_STATE,
    SINGLE_PLAYER,
    MULTIPLAYER,
    OPTIONS,
    IN_GAME_OPTIONS,
    START,
    QUIT,
    CLOSED,
    IN_PAUSE,
};

enum class GameState {
    MAIN_MENU,
    IN_GAME,
    IN_GAME_PAUSE,
};

struct MainMenu {
    float buttonWidth = 100;
    float buttonHeight = 24;
    float buttonSpacing = 50;

    MenuState menuState = MenuState::MAIN_MENU;

    InputText ipInput;
    InputText portInput;

    sf::RectangleShape menuRect = sf::RectangleShape(sf::Vector2f(150, 200));

    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;

    sf::Font font;

    MainMenu()= default;

    MainMenu(sf::Font &somefont) {
        this->font = somefont;

        ipInput.init(somefont);
        portInput.init(somefont);

//        playText = sf::Text("Play", font);
//        optionsText = sf::Text("Options", font);
//        quitText = sf::Text("Quit", font);
//
//
//        singlePlayerText = sf::Text("Single Player", font);
//        multiplayerText = sf::Text("Multiplayer", font);
//
//        backText = sf::Text("Back", font);
//
//
//        chooseMapText = sf::Text("Choose Map", font);
//        map1Text = sf::Text("Map 1", font);
//        map2Text = sf::Text("Map 2", font);
//        map3Text = sf::Text("Map 3", font);
//        startText = sf::Text("Start", font);
//
//        enterServerIpText = sf::Text("Enter Server IP", font);
//        enterPortText = sf::Text("Enter Port", font);
//        connectText = sf::Text("Connect", font);
//
//
//        resizeWindowText = sf::Text("Resolution: ", font);
//        fullscreenText = sf::Text("Fullscreen", font);
//        hdText = sf::Text("1280x720", font);
    }
    void setUpText(sf::Text &text, int character_size, float pos_x, float pos_y, sf::Color color) const{
        text.setCharacterSize(character_size);
        text.setFillColor(color);
        text.setPosition(pos_x, pos_y);
        //sf::FloatRect text1Bounds = text1.getLocalBounds();
        //text.setOrigin(text1Bounds.left + text1Bounds.width / 2.0f, text1Bounds.top + text1Bounds.height / 2.0f);
    }

    void setMainMenuItems(sf::RenderWindow &window){

//        sf::Vector2f viewCenter = window.getView().getCenter();
//        sf::Vector2f viewSize = window.getView().getSize();
//
//        // Calculate menu position relative to current view
//        float menuX = viewCenter.x - 50;
//        float menuY = viewCenter.y - 25;
//
//
//        menuRect.setFillColor(sf::Color(128, 128, 128));
//        menuRect.setPosition(menuX, menuY);
//
//        playText.setCharacterSize(24);
//        playText.setFillColor(sf::Color::White);
//        playText.setPosition(menuX + 50, menuY + 50);
//
//        optionsText.setCharacterSize(24);
//        optionsText.setFillColor(sf::Color::White);
//        optionsText.setPosition(menuX + 50, menuY + 100);
//
//        quitText.setCharacterSize(24);
//        quitText.setFillColor(sf::Color::White);
//        quitText.setPosition(menuX + 50, menuY + 150);
//
//
//
//        singlePlayerText.setCharacterSize(24);
//        singlePlayerText.setFillColor(sf::Color::White);
//        singlePlayerText.setPosition(menuX + 50, menuY + 50);
//
//        multiplayerText.setCharacterSize(24);
//        multiplayerText.setFillColor(sf::Color::White);
//        multiplayerText.setPosition(menuX + 50, menuY + 150);
//
//        backText.setCharacterSize(24);
//        backText.setFillColor(sf::Color::White);
//        backText.setPosition(menuX + 50, menuY + 350);
//
//
//
//        chooseMapText.setCharacterSize(24);
//        chooseMapText.setFillColor(sf::Color::White);
//        chooseMapText.setPosition(menuX + 50, menuY + 50);
//
//        map1Text.setCharacterSize(24);
//        map1Text.setFillColor(sf::Color::White);
//        map1Text.setPosition(menuX + 50, menuY + 100);
//
//        map2Text.setCharacterSize(24);
//        map2Text.setFillColor(sf::Color::White);
//        map2Text.setPosition(menuX + 50, menuY + 150);
//
//        map3Text.setCharacterSize(24);
//        map3Text.setFillColor(sf::Color::White);
//        map3Text.setPosition(menuX + 50, menuY + 200);
//        ///4
//
//
//
//        enterServerIpText.setCharacterSize(24);
//        enterServerIpText.setFillColor(sf::Color::White);
//        enterServerIpText.setPosition(menuX + 50, menuY + 50);
//
//        ipInput.setPosition(menuX+ 50, menuY + 100, 120, 50);
//
//
//        enterPortText.setCharacterSize(24);
//        enterPortText.setFillColor(sf::Color::White);
//        enterPortText.setPosition(menuX + 50, menuY + 150);
//
//        portInput.setPosition(menuX+ 50, menuY + 200, 120, 50);
//
//        connectText.setCharacterSize(24);
//        connectText.setFillColor(sf::Color::White);
//        connectText.setPosition(menuX + 50, menuY + 250);
//
//
//
//        resizeWindowText.setCharacterSize(24);
//        resizeWindowText.setFillColor(sf::Color::White);
//        resizeWindowText.setPosition(menuX + 50, menuY + 50);
//
//        fullscreenText.setCharacterSize(24);
//        fullscreenText.setFillColor(sf::Color::White);
//        fullscreenText.setPosition(menuX + 50, menuY + 100);
//
//        hdText.setCharacterSize(24);
//        hdText.setFillColor(sf::Color::White);
//        hdText.setPosition(menuX + 50, menuY + 150);
    }

    bool mouseCursorCollidesWithMenuItem(sf::Vector2f &mousePos, sf::Vector2f menuItemPos) const {
        return (
                (float) mousePos.x >= menuItemPos.x &&
                (float) mousePos.x <= menuItemPos.x + buttonWidth &&
                (float) mousePos.y >= menuItemPos.y &&
                (float) mousePos.y <= menuItemPos.y + buttonHeight
        );
    }

    static bool clicked(){
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
/*
    void drawRectangle(sf::RenderWindow &window, sf::Font &font) {
        sf::Vector2f viewCenter = window.getView().getCenter();
        sf::Vector2f viewSize = window.getView().getSize();

        // Calculate rectangle position relative to current view
        float rectX = viewCenter.x - 50;
        float rectY = viewCenter.y - 25;

        sf::RectangleShape rectangle(sf::Vector2f(100, 50));
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(rectX, rectY);

        sf::Text text;
        text.setFont(font);
        text.setString("Text");
        text.setCharacterSize(50);
        text.setScale(0.2,0.2);
        text.setFillColor(sf::Color::White);

        // Center text within rectangle
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f, rectangle.getPosition().y + rectangle.getSize().y / 2.0f);

        // Change text color if mouse is over rectangle
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            text.setFillColor(sf::Color::Yellow);
        }

        window.draw(rectangle);
        window.draw(text);
    }
*/




    void drawMainMenu(sf::RenderWindow &window) {

        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mp);

        sf::Vector2f viewCenter = window.getView().getCenter();

        text1 = sf::Text("Play", font);
        text2 = sf::Text("Options", font);
        text3 = sf::Text("Quit", font);

        menuRect.setFillColor(sf::Color(128, 128, 128));
        menuRect.setPosition(viewCenter);
        center_rect_shape(menuRect);

        setUpText(text1, 12, viewCenter.x - 20, viewCenter.y - 40, sf::Color::White);
        setUpText(text2, 12, viewCenter.x - 20, viewCenter.y - 20, sf::Color::White);
        setUpText(text3, 12, viewCenter.x - 20, viewCenter.y, sf::Color::White);


        if (mouseCursorCollidesWithMenuItem(mousePos, text1.getPosition())) {
            text1.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::CHOOSING_GAME_STATE;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text2.getPosition())) {
            text2.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::OPTIONS;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
            text3.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::QUIT;
            }
        }
        window.draw(menuRect);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
    }

    void drawPauseMenu(sf::RenderWindow &window, GameState &gameState) {
       // setMainMenuItems(window);
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mp);

        sf::Vector2f viewCenter = window.getView().getCenter();

        text1 = sf::Text("Continue", font);
        text2 = sf::Text("Options", font);
        text3 = sf::Text("Exit to main menu", font);

        menuRect.setFillColor(sf::Color(128, 128, 128));
        menuRect.setPosition(viewCenter);
        center_rect_shape(menuRect);

        setUpText(text1, 12, viewCenter.x - 27, viewCenter.y - 40, sf::Color::White);
        setUpText(text2, 12, viewCenter.x - 25, viewCenter.y - 20, sf::Color::White);
        setUpText(text3, 12, viewCenter.x - 50, viewCenter.y, sf::Color::White);

        if (mouseCursorCollidesWithMenuItem(mousePos, text1.getPosition())) {
            text1.setFillColor(sf::Color::Yellow);
            if(clicked()){
                gameState = GameState::IN_GAME;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text2.getPosition())) {
            text2.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::IN_GAME_OPTIONS;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
            text3.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::MAIN_MENU;
                gameState = GameState::MAIN_MENU;
            }
        }
        window.draw(menuRect);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
    }

    void drawChoosingGameStateMenu(sf::RenderWindow &window) {
     //   setMainMenuItems(window);
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mp);

        sf::Vector2f viewCenter = window.getView().getCenter();

        text1 = sf::Text("Singleplayer", font);
        text2 = sf::Text("Multiplayer", font);
        text3 = sf::Text("Back", font);

        menuRect.setFillColor(sf::Color(128, 128, 128));
        menuRect.setPosition(viewCenter);
        center_rect_shape(menuRect);

        setUpText(text1, 12, viewCenter.x - 40, viewCenter.y - 40, sf::Color::White);
        setUpText(text2, 12, viewCenter.x - 35, viewCenter.y - 10, sf::Color::White);
        setUpText(text3, 12, viewCenter.x - 20, viewCenter.y + 20, sf::Color::White);


        if (mouseCursorCollidesWithMenuItem(mousePos, text1.getPosition())) {
            text1.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::SINGLE_PLAYER;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text2.getPosition())) {
            text2.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::MULTIPLAYER;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
            text3.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::MAIN_MENU;
            }
        }
        window.draw(menuRect);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
    }

    void drawSinglePlayerMenu(sf::RenderWindow &window) {

        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mp);

        sf::Vector2f viewCenter = window.getView().getCenter();

        text1 = sf::Text("Choose map: ", font);
        text2 = sf::Text("Map 1", font);
        text3 = sf::Text("Map 2", font);
        text4 = sf::Text("Map 3", font);
        text5 = sf::Text("Back", font);

        menuRect.setFillColor(sf::Color(128, 128, 128));
        menuRect.setPosition(viewCenter);
        center_rect_shape(menuRect);

        setUpText(text1, 12, viewCenter.x - 20, viewCenter.y - 40, sf::Color::White);
        setUpText(text2, 12, viewCenter.x - 20, viewCenter.y - 20, sf::Color::White);
        setUpText(text3, 12, viewCenter.x - 20, viewCenter.y, sf::Color::White);
        setUpText(text4, 12, viewCenter.x - 20, viewCenter.y + 20, sf::Color::White);
        setUpText(text5, 12, viewCenter.x - 20, viewCenter.y + 40, sf::Color::White);


        if (mouseCursorCollidesWithMenuItem(mousePos, text2.getPosition())) {
            text2.setFillColor(sf::Color::Yellow);
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
            text3.setFillColor(sf::Color::Yellow);
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getPosition())) {
            text4.setFillColor(sf::Color::Yellow);
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text5.getPosition())) {
            text5.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::MAIN_MENU;
            }
        }



        window.draw(menuRect);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
    }

    void drawMultiplayerMenu(sf::RenderWindow &window) {
     //   setMainMenuItems(window);
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mp);

        sf::Vector2f viewCenter = window.getView().getCenter();

        text1 = sf::Text("Enter Server IP", font);
        text2 = sf::Text("Enter Port", font);
        text3 = sf::Text("Connect", font);
        text4 = sf::Text("Back", font);

        menuRect.setFillColor(sf::Color(128, 128, 128));
        menuRect.setPosition(viewCenter);
        center_rect_shape(menuRect);

        setUpText(text1, 12, viewCenter.x - 45, viewCenter.y - 80, sf::Color::White);
        ipInput.setPosition(viewCenter.x - 70, viewCenter.y - 50, 140, 20);

        setUpText(text2, 12, viewCenter.x - 35, viewCenter.y - 20, sf::Color::White);
        portInput.setPosition(viewCenter.x - 70, viewCenter.y + 10, 140, 20);


        setUpText(text3, 12, viewCenter.x - 30, viewCenter.y + 40, sf::Color::White);
        setUpText(text4, 12, viewCenter.x - 20, viewCenter.y + 70, sf::Color::White);

        if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
            text3.setFillColor(sf::Color::Yellow);
            if(clicked()){
                menuState = MenuState::START;
            }
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getPosition())) {
            text4.setFillColor(sf::Color::Yellow);
            if(clicked()){
                ipInput.clearInput();
                portInput.clearInput();
                menuState = MenuState::CHOOSING_GAME_STATE;
            }
        }
        ipInput.update(window);
        portInput.update(window);
        window.draw(menuRect);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        ipInput.draw(window);
        portInput.draw(window);
    }

    void drawOptionsMenu(sf::RenderWindow &window) {
     //   setMainMenuItems(window);
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mp);

        sf::Vector2f viewCenter = window.getView().getCenter();

        text1 = sf::Text("Screen Resolution:", font);
        text2 = sf::Text("Fullscreen", font);
        text3 = sf::Text("1600x800", font);
        text4 = sf::Text("1280x720", font);
        text5 = sf::Text("Back", font);

        menuRect.setFillColor(sf::Color(128, 128, 128));
        menuRect.setPosition(viewCenter);
        center_rect_shape(menuRect);

        setUpText(text1, 12, viewCenter.x - 50, viewCenter.y - 60, sf::Color::White);
        setUpText(text2, 12, viewCenter.x - 30, viewCenter.y - 40, sf::Color::White);
        setUpText(text3, 12, viewCenter.x - 30, viewCenter.y - 20, sf::Color::White);
        setUpText(text4, 12, viewCenter.x - 30, viewCenter.y, sf::Color::White);
        setUpText(text5, 12, viewCenter.x - 20, viewCenter.y + 20, sf::Color::White);


        if (mouseCursorCollidesWithMenuItem(mousePos, text2.getPosition())) {
            text2.setFillColor(sf::Color::Yellow);
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
            text3.setFillColor(sf::Color::Yellow);
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getPosition())) {
            text4.setFillColor(sf::Color::Yellow);
        } else if (mouseCursorCollidesWithMenuItem(mousePos, text5.getPosition())) {
            text5.setFillColor(sf::Color::Yellow);
            if(clicked()){
                if(menuState == MenuState::IN_GAME_OPTIONS){
                    menuState = MenuState::IN_PAUSE;
                } else if(menuState == MenuState::OPTIONS){
                    menuState = MenuState::MAIN_MENU;
                }
            }
        }
        window.draw(menuRect);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
    }

    void draw(sf::RenderWindow &window){
        if (menuState == MenuState::MAIN_MENU) {
            drawMainMenu(window);
        } else if (menuState == MenuState::CHOOSING_GAME_STATE) {
            drawChoosingGameStateMenu(window);
        }else if (menuState == MenuState::SINGLE_PLAYER) {
            drawSinglePlayerMenu(window);
        } else if (menuState == MenuState::MULTIPLAYER) {
            drawMultiplayerMenu(window);
        } else if (menuState == MenuState::OPTIONS) {
            drawOptionsMenu(window);
        }
    }

    void draw_in_pause(sf::RenderWindow &window, GameState &gameState){
     //   setMainMenuItems(window);
     if(menuState == MenuState::IN_PAUSE){
         drawPauseMenu(window, gameState);
     } if (menuState == MenuState::IN_GAME_OPTIONS){
            drawOptionsMenu(window);
     }

//        if (menuState == MenuState::OPTIONS) {
//            drawOptionsMenu(window);
//        }
    }

};