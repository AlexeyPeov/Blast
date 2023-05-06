#pragma once

#include <SFML/Graphics.hpp>
#include "RayCaster.h"
#include "Server.h"
#include "MainMenu.h"
#include <chrono>
#include <thread>
#include "Takeover.h"

struct Resolution {
    uint32_t x = 1280;
    uint32_t y = 720;
};

struct ViewSize {
    uint32_t x = 1280;
    uint32_t y = 720;

//    uint32_t x = 1280;
//    uint32_t y = 720;

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
    Client client = Client();

    sf::Shader shader;

    bool gained_focus = true;
    bool is_running = true;
    GameState gameState = GameState::MAIN_MENU;
    MultiplayerAction multiplayerAction = MultiplayerAction::NOTHING;

    MainMenu mainMenu;
    Round round = Round::HAS_NOT_STARTED;
    GameMode gameMode = GameMode::NONE;

    Takeover takeover = Takeover();



public:
    Game() : desktop(sf::VideoMode::getDesktopMode()),
             window(sf::VideoMode(700, 500), "Blast", sf::Style::Titlebar | sf::Style::Close){
        //sf::VideoMode(1600, 800), "Blast", sf::Style::Titlebar | sf::Style::Close
        //window(desktop, "Blast", sf::Style::Fullscreen),
        view = sf::View(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
        view.setCenter((sf::Vector2f)window.getPosition());
        //window.setView(view);
        window.setVerticalSyncEnabled(true);
        // Load the font and create the label
        font.loadFromFile(working_dir() + "/textures/DejaVuSans.ttf");
        map.gameState = &gameState;
        map.init_map_textures();
        mainMenu = MainMenu(font, videoMode, client, multiplayerAction, map, gameMode);
        map.init_map_sounds();
        takeover = Takeover(&map, &client);
        if (!shader.loadFromFile(working_dir() + "/shaders/invert_colors.frag", sf::Shader::Fragment)) {
                std::cerr << "Failed to load shader\n";
        }

    }

    void run();

    void death_match();

    void takeover_game_mode();

    void handleMultiplayerAction();

    void handleKeyBindings();

    void draw_score_menu();

    void draw_in_game_pause_menu();

    void draw_in_game_options_menu();

    void draw_user_interface();

    void handleEvents(sf::Event &e);

    void draw_team_won(int team);
};