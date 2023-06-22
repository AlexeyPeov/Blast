#pragma once

#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "Map.h"
#include "Server.h"
#include "Client.h"
#include "MainMenu.h"
#include "Takeover.h"
#include "RayCaster.h"


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
    std::thread server_thread;
    Client client = Client(obj::generate_random_id(), "", "", 0);

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
    Game();
    ~Game();

    void run();

    void death_match();

    void takeover_game_mode(bool online);

    void handleMultiplayerAction();

    void handleKeyBindings();

    void draw_score_menu();

    void draw_in_game_pause_menu();

    void draw_in_game_options_menu();

    void draw_user_interface();

    void handleEvents(sf::Event &e);

    void draw_team_won(int team);

    void handle_camera_movement(sf::Vector2f player_position, sf::Vector2i mouse_position);
};