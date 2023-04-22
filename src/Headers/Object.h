#pragma once

#include <vector>
#include <cstring>
#include <string>
#include <iostream>

#define SHOOT 1
#define DONT_SHOOT 0

const short nickname_length = 15;


struct Object {
    int id = 0;
    char nickname[nickname_length] = "aboba";
    int hp = 0;
    int bullets = 120;
    short team = 1;
    int kills = 0;
    int deaths = 0;
    float pos_x = 0;
    float pos_y = 0;
    float rotation = 0;
    uint8_t action = 0;
};


namespace object {

    void shoot(Object &object);

    void dont_shoot(Object &object);

    bool is_shooting(Object &object);

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
}