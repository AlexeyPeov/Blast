#pragma once

#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include <random>

#define SHOOT 1
#define DONT_SHOOT 0

const short nickname_length = 15;


struct Object {
    uint64_t id = 0;
    char nickname[nickname_length] = "anonymous";
    int hp = 100;
    short in_game_action = 0;
    uint8_t team = 1;
    int kills = 0;
    int deaths = 0;
    float pos_x = 0;
    float pos_y = 0;
    float rotation = 0;
    float missile_rotation = 0;
    uint8_t team_won = 0;
    uint8_t main_menu_action = 0;
    uint64_t tick = 0;
};




namespace object {

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