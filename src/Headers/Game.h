#pragma once

#include <SFML/Graphics.hpp>
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
    uint x = 560;
    uint y = 315;
//    uint x = 430;
//    uint y = 240;
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
    sf::Font font;
    sf::View view;
    Server server;
    Client client;
    bool gained_focus = false;
    bool is_running = true;
    GameState gameState = GameState::MAIN_MENU;
    MultiplayerAction multiplayerAction = MultiplayerAction::NOTHING;

    MainMenu mainMenu;
    Round round = Round::HAS_NOT_STARTED;
    GameMode gameMode = GameMode::NONE;

public:
    Game() : desktop(sf::VideoMode::getDesktopMode()),
             window(sf::VideoMode(800, 600), "Blast", sf::Style::Titlebar | sf::Style::Close){
        //sf::VideoMode(1600, 800), "Blast", sf::Style::Titlebar | sf::Style::Close
        //window(desktop, "Blast", sf::Style::Fullscreen),
        view = sf::View(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
        view.setCenter((sf::Vector2f)window.getPosition());
        //window.setView(view);
        window.setVerticalSyncEnabled(true);
        // Load the font and create the label
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        map.gameState = &gameState;
        map.init_map_textures();
        mainMenu = MainMenu(font, videoMode, client, multiplayerAction, map, gameMode);

    }

    void run();

    void death_match();

    void takeover();

    void next_round();

    void handleMultiplayerAction();

    void round_duration();

    void handleKeyBindings();

    void draw_score_menu();

    void draw_in_game_pause_menu();

    void draw_in_game_options_menu();
};