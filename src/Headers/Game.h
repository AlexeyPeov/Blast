#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "RayCaster.h"
#include "Server.h"
#include "MainMenu.h"
#include <chrono>
#include <thread>

struct Resolution {
    uint x = 1280;
    uint y = 720;
};

struct ViewSize {
    uint x = 430;
    uint y = 240;
//    uint x = 1920;
//    uint y = 1080;

};

class Game {

private:

    ViewSize viewSize;

    VideoMode videoMode = VideoMode::UNCHANGED;

    Map map;
    Resolution resolution;
    sf::VideoMode desktop;
    sf::RenderWindow window;
    sf::RectangleShape button;
    sf::Font font;
    sf::Text label;
    sf::View view;
    Server server;
    Client client;
    bool gained_focus = false;
    bool is_running = true;
    GameState gameState = GameState::MAIN_MENU;
    MultiplayerAction multiplayerAction = MultiplayerAction::NOTHING;

    MainMenu mainMenu;

public:
    Game() : desktop(sf::VideoMode::getDesktopMode()),
             window(sf::VideoMode(800, 600), "Blast", sf::Style::Titlebar | sf::Style::Close),
             button(sf::Vector2f(100, 50)) {
        //sf::VideoMode(1600, 800), "Blast", sf::Style::Titlebar | sf::Style::Close
        //window(desktop, "Blast", sf::Style::Fullscreen),
        view = sf::View(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
        view.setCenter((sf::Vector2f)window.getPosition());
        //window.setView(view);

        // Set the button color
        button.setFillColor(sf::Color(128, 128, 128));

        // Load the font and create the label
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        label.setFont(font);
        label.setString("Fullscreen");
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::Black);


        map.init_map_textures();
        map.init_main_player();
        map.init_walls(2);

        mainMenu = MainMenu(font, videoMode, client, multiplayerAction);

    }

    void run();

    void handleMultiplayerAction();
};