#ifndef TAKEOVER_H
#define TAKEOVER_H

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Map.h"


struct Takeover {

    Map *map;

    uint8_t current_round = 1;
    bool game_started = false;
    bool game_over = false;

    bool is_before_round = true;
    bool is_in_round = true;
    bool is_retake = false;
    bool is_after_round = true;
    bool is_reset_for_new_round = false;

    bool bomb_planted = false;
    bool some_team_won = false;

    uint8_t bomb_tick_timer = BOMB_TICK_TIMER;
    uint8_t ready = 0;

    uint8_t team_won = 0;
    uint8_t current_round_team_won = 0;


    uint8_t score_t = 0;
    uint8_t score_ct = 0;
    uint8_t round_seconds_left = 0;

    bool cool_down_started = false;
    std::chrono::system_clock::time_point start;


    Takeover(Map &map);

    Takeover();

    ~Takeover();

    void before_round();

    void in_round();

    void retake();

    void after_round();

    void change_teams(Player &player);

    void reset_for_new_round();

    void reset();

    void cool_down(int seconds, bool *to_set_to_false_after_cool_down);

    Sync sync_object();

    void sync_takeover(Sync &sync);

    void update();

    sf::Vector2f get_spawn_position(Player &object);

    sf::Vector2f get_bomb_spawn_position();
};

#endif
