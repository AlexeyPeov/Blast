#pragma once

#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include <random>

const short nickname_length = 15;


struct Object {
    sf::Uint64 id = 0;
    char nickname[nickname_length] = "anonymous";
    int hp = 100;
    short in_game_action = 0;
    sf::Uint8 team = 1;
    int kills = 0;
    int deaths = 0;
    float pos_x = 0;
    float pos_y = 0;
    float rotation = 0;
    float missile_rotation = 0;
    sf::Uint8 main_menu_action = 0;
    sf::Uint64 tick = 0;
    sf::Uint32 sync = 0;
};
//  2^5 = 32 - current_round 0-4
//  2^4 = 15 - team_t_score  5-8
//  2^4 = 15 - team_ct_score 9-12
//  13 - is_before_round
//  14 - is_in_round
//  15 - is_retake
//  16 - is_after_round
//  2^8 - time(seconds)     17-24


namespace object {


    void synchronize_host(
            Object &host,
            uint8_t current_round,
            uint8_t team_t_score,
            uint8_t team_ct_score,
            bool is_before_round,
            bool is_in_round,
            bool is_retake,
            bool is_after_round,
            uint8_t seconds
            );

    void extract_sync_values(
            const Object &object,
            uint8_t &current_round,
            uint8_t &team_t_score,
            uint8_t &team_ct_score,
            bool &is_before_round,
            bool &is_in_round,
            bool &is_retake,
            bool &is_after_round,
            uint8_t &seconds
    );

    void synchronize_with_host(Object &host, Object &not_host);

    Object find_host(std::vector<Object> objects);

    uint8_t extract_seconds_left(const Object &object);

    void wants_or_needs_to_reload(Object &object);

    void doesnt_want_or_need_to_reload(Object &object);

    bool does_want_or_need_to_reload(Object &object);

    void run(Object &object);

    void walk(Object &object);

    bool is_running(Object &object);

    void shoot(Object &object);

    void dont_shoot(Object &object);

    bool is_shooting(Object &object);

    void reload_start(Object &object);

    void reload_end(Object &object);

    bool is_reloading(Object &object);


    void has_bomb(Object &object);

    void doesnt_have_bomb(Object &object);

    bool is_bomb_carrier(Object &object);

    bool drops_bomb(Object &object);

    void drop_bomb(Object &object);
    void dont_drop_bomb(Object &object);

    void plant_bomb(Object & object);
    void not_plant_bomb(Object & object);

    bool is_bomb_planted(Object &object);

    void defused(Object &object);
    void not_defused(Object &object);

    bool is_bomb_defused(Object &object);

    void choose_map_1(Object &object);
    void choose_map_2(Object &object);
    void choose_map_3(Object &object);

    void choose_map(Object &object, short map);

    void unchoose_maps(Object &object);

    void choose_death_match(Object &object);
    void choose_takeover(Object &object);
    void choose_game_mode(Object &object, short gamemode);

    void ready(Object &object);

    bool is_ready(Object &object);

    void set_host(Object &object);
    bool is_host(Object & object);
    void set_not_host(Object &object);

    short which_map_is_chosen(Object &object);
    short which_game_mode_is_chosen(Object &object);


    std::vector<char> serialize_object(const Object& object);

    std::vector<char> serialize_objects(const std::vector<Object>& objects);

    void deserialize_objects(const std::vector<char>& data, std::vector<Object>& objects);

    void deserialize_object(const std::vector<char>& data, Object & object);

    void copy_string_to_nickname(std::string &string, Object &object);

    void reset(Object &object);

    sf::Packet& operator<<(sf::Packet& packet, const Object& object);

    sf::Packet& operator>>(sf::Packet& packet, Object& object);

    uint64_t generate_random_id();
}