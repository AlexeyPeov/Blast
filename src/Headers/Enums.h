#pragma once


enum Round{
    HAS_NOT_STARTED,
    START,
    IN_PROGRESS,
    OVER,
};

enum GameMode {
    DEATH_MATCH,
    TAKEOVER,
    NONE,
};


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
    START,
    QUIT,
};

enum GameState {
    MAIN_MENU,
    IN_GAME,
    IN_GAME_PAUSE,
    IN_GAME_OPTIONS,
};

enum ApplicationState {
    MENU,
    GAME,
};