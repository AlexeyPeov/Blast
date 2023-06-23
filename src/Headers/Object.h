#ifndef OBJECT_H
#define OBJECT_H


#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <random>
#include <filesystem>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


#include "Constants.h"
#include "SpriteMethods.h"

std::string working_dir();

static std::mt19937 generator(std::random_device{}());

struct PlayerEvent{
    uint32 up_button_pressed : 1;
    uint32 down_button_pressed : 1;
    uint32 left_button_pressed : 1;
    uint32 right_button_pressed : 1;
    uint32 walk_silently_button_pressed : 1;
    uint32 shoot_button_pressed : 1;
    uint32 event_button_pressed : 1;
    uint32 reload_button_pressed : 1;
    uint32 drop_button_pressed : 1;
    uint32 quit_button_pressed : 1;
    uint32 change_team_to_t_button_pressed : 1;
    uint32 change_team_to_ct_button_pressed : 1;
    uint32 chose_map_1_button_pressed : 1;
    uint32 chose_map_2_button_pressed : 1;
    uint32 chose_map_3_button_pressed : 1;
    uint32 chose_deathmatch_button_pressed : 1;
    uint32 chose_takeover_button_pressed : 1;
    uint32 ready_button_pressed : 1;
    uint32 rotation_whole_number : 9;
    uint32 rotation_decimal_number : 9;

};

struct PlayerState{
    uint16 has_bomb : 1;
    uint16 planting_bomb : 1;
    uint16 defusing_bomb : 1;
    uint16 planted_bomb : 1;
    uint16 defused_bomb : 1;
    uint16 dropping_bomb : 1;
    uint16 reloading : 1;
    uint16 running : 1;
    uint16 walking : 1;
    uint16 shooting : 1;
};

struct MainMenuEvent{
    uint8 map1 : 1;
    uint8 map2 : 1;
    uint8 map3 : 1;
    uint8 death_match_game_mode : 1;
    uint8 takeover_game_mode : 1;
    uint8 host : 1;
    uint8 ready_to_play : 1;
    uint8 in_game : 1;

};

struct Sync{
    uint64 current_round : 5;
    uint64 team_t_score : 5;
    uint64 team_ct_score : 5;
    uint64 is_before_round : 1;
    uint64 is_in_round : 1;
    uint64 is_retake : 1;
    uint64 is_after_round : 1;
    uint64 round_seconds_left : 8;
    uint64 game_over : 1;
};

struct PlayerObject {
    uint64 id = 0;
    char nickname[NICKNAME_LENGTH] = "Anon";
    int32 hp = 100;
    uint8 team = 1;
    int16 kills = 0;
    int16 deaths = 0;
    int16 mag_ammo = 0;
    int16 leftover_ammo = 0;
    float32 pos_x = 0;
    float32 pos_y = 0;
    float32 rotation = 0;
    uint64 tick = 0;
    PlayerState player_state = {0};
    MainMenuEvent main_menu_event = {0};
    Sync sync = {0};



    uint32 shoot_timer = 0;
    uint32 plant_or_defuse_timer = 0;
    uint32 reload_timer = 0;
};

struct MissileObject{
    uint64 id = 0;
    bool life = true;
    uint64 player_who_shot_id = 0;
    float32 rotation_degree = 0.0;

    float32 position_x = 0.0;
    float32 position_y = 0.0;

    float32 previous_position_x = 0.0;
    float32 previous_position_y = 0.0;
};

struct BombObject{
    uint32 dropped : 1;
    uint32 pos_x : 15;
    uint32 pos_y : 15;
};



namespace obj {

    void set_default_values(PlayerObject &object);

    int16 which_map_is_chosen(PlayerObject &player_object);

    int16 which_game_mode_is_chosen(PlayerObject &player_object);

    void copy_string_to_nickname(std::string &string, PlayerObject &object);

    sf::Packet& operator << (sf::Packet& packet, const PlayerEvent &player_event);

    sf::Packet& operator >> (sf::Packet& packet, PlayerEvent &player_event);



    sf::Packet& operator << (sf::Packet& packet, const PlayerObject &object);

    sf::Packet& operator >> (sf::Packet& packet, PlayerObject& object);

    sf::Packet& operator << (sf::Packet& packet, const MissileObject &object);

    sf::Packet& operator >> (sf::Packet& packet, MissileObject& object);

    sf::Packet& operator << (sf::Packet& packet, const BombObject &object);

    sf::Packet& operator >> (sf::Packet& packet, BombObject& object);

    uint64 generate_random_id();

}

#endif