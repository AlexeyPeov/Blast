#include <SFML/Graphics.hpp>
#include "InputText.h"
#include "SpriteMethods.h"
#include <iostream>
#include "Client.h"

enum MultiplayerAction{
    NOTHING,

    START_SERVER_AND_CLIENT,
    START_CLIENT,
    STOP_SERVER_AND_CLIENT,
};

enum VideoMode{
    FULLSCREEN,
    _1600x800,
    _1280x720,
    UNCHANGED,
};

enum class MenuState {
    MAIN_MENU,
    CHOOSING_GAME_STATE,
    SINGLE_PLAYER,
    IS_HOST,
    CLIENT,
    MULTIPLAYER_LOBBY,
    OPTIONS,
    IN_GAME_OPTIONS,
    START,
    QUIT,
    IN_GAME,
    IN_GAME_PAUSE,
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
    InputText nicknameInput;

    sf::RectangleShape menuRect = sf::RectangleShape(sf::Vector2f(450, 600));
    sf::CircleShape hostRadioBox = sf::CircleShape(6 * 3);

    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;

    sf::Text text1_in_game;
    sf::Text text2_in_game;
    sf::Text text3_in_game;
    sf::Text text4_in_game;
    sf::Text text5_in_game;

    sf::RectangleShape menu_rect_in_game = sf::RectangleShape(sf::Vector2f(150, 200));

    sf::Font font;


    VideoMode *gameVideoMode = nullptr;
    MultiplayerAction *multiplayerAction = nullptr;
    Client *client = nullptr;

    MainMenu()= default;

    MainMenu(sf::Font &font, VideoMode &gameVideoMode, Client &client, MultiplayerAction &multiplayerAction) {
        this->font = font;

        ipInput.init(font);
        portInput.init(font);
        nicknameInput.init(font);

        this->gameVideoMode = &gameVideoMode;
        this->client = &client;
        this->multiplayerAction = &multiplayerAction;

        menu_rect_in_game.setFillColor(sf::Color(128, 128, 128));
    }

    static void setUpText(sf::Text &text, int character_size, float pos_x, float pos_y, sf::Color color);

    static bool mouseCursorCollidesWithMenuItem(sf::Vector2f &mousePos, sf::FloatRect menuItemBounds);

    static bool clicked();

    void drawMainMenu(sf::RenderWindow &window);

    void drawPauseMenu(sf::RenderWindow &window, GameState &gameState);

    void drawChoosingGameStateMenu(sf::RenderWindow &window);

    void drawSinglePlayerMenu(sf::RenderWindow &window);

    void drawMultiplayerLobby(sf::RenderWindow &window);

    void drawIsHostMenu(sf::RenderWindow &window);

    void drawClientMenu(sf::RenderWindow &window);

    void drawOptionsMenu(sf::RenderWindow &window);

    void drawInGameOptionsMenu(sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

    void draw_in_pause(sf::RenderWindow &window, GameState &gameState);

};