#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"

const uint8_t BEFORE_ROUND_TIME_SECONDS = 5;
const uint8_t AFTER_ROUND_TIME_SECONDS = 4;
const uint8_t ROUND_TIME_SECONDS =  165;//165;
const uint8_t TIME_TO_DEFUSE_BOMB = 45;

const uint8_t BOMB_TICK_TIMER = 72;
const uint8_t CHANGE_TEAM_ROUND = 17;
const uint8_t ROUNDS_NEEDED_TO_WIN = 16;


const uint8_t TEAM_T = 1;
const uint8_t TEAM_CT = 2;

struct TeamOnline{
    Object* objects[5] = {nullptr};


    void insert(Object &object){
        for(auto &obj : objects){
            if(obj == nullptr){
                obj = &object;
                return;
            }
        }
    }

    void clear(){
        for (auto  &obj : objects){
            obj = nullptr;
        }
    }

    static sf::Vector2f get_spawn_position(Object &object){
        sf::Vector2f position = {0,0};

        float default_spawn_x = 0;
        float default_spawn_y = 0;

        if(object.team == TEAM_T){
            default_spawn_x = 188;
            default_spawn_y = 1790;

//            default_spawn_x = 280;
//            default_spawn_y = 445;
        } else if(object.team == TEAM_CT){
            default_spawn_x = 310;
            default_spawn_y = 445;
        }
        position = {default_spawn_x, default_spawn_y};
        return position;
    }
    static sf::Vector2f get_bomb_spawn_position(){
        return sf::Vector2f {188 + 40, 1790};
    }
};

struct TeamOffline{
    Player* players[5] = {nullptr};
};

struct Takeover {

    Map *map;
    Client *client;

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

    TeamOnline team_t_online;
    TeamOnline team_ct_online;

    TeamOffline team_t_offline;
    TeamOffline team_ct_offline;


    explicit Takeover(Map *map, Client *client) {
        this->map = map;
        this->client = client;
    }

    Takeover(){}

    ~Takeover(){}

    void init(){
        if(client->active){
            int size = client->objects.size();
            for (int i = 0; i < size; i++){
                if(client->objects[i].team == TEAM_T){
                    team_t_online.insert(client->objects[i]);
                } else if(client->objects[i].team == TEAM_CT){
                    team_ct_online.insert(client->objects[i]);
                }
            }

            if(client->object.team == TEAM_T){
                team_t_online.insert(client->object);
            } else if(client->object.team == TEAM_CT){
                team_ct_online.insert(client->object);
            }

        } else {
            this->team_t_offline = {};
            this->team_ct_offline = {};
            // todo : offline implementation
        }
    }

    void before_round() {

        if(!is_reset_for_new_round){
            reset_for_new_round();
        }

        if (map->main_player.team_t) {
            map->main_player.sprite.setPosition(team_t_online.get_spawn_position(client->object));
        } else {
            map->main_player.sprite.setPosition(team_ct_online.get_spawn_position(client->object));
        }
        map->main_player.freeze();

        map->main_player.hp = 100;
        map->main_player.mag_ammo = mag_capacity;
        map->main_player.leftover_ammo = max_ammo;

        map->spawn_bomb(team_t_online.get_bomb_spawn_position());


        if(is_host(client->object)){
            cool_down(BEFORE_ROUND_TIME_SECONDS, &is_before_round);
        } else {
            cool_down(extract_seconds_left(find_host(client->objects)), &is_in_round);
        }
    }

    void in_round() {
        if (!map->team_t_alive_online(*client)) {
            is_in_round = false;
            score_ct++;
            current_round_team_won = TEAM_CT;
            some_team_won = true;
        }
        if (!map->team_ct_alive_online(*client)) {
            is_in_round = false;
            score_t++;
            some_team_won = true;
            current_round_team_won = TEAM_T;
        }

        if (map->bomb_planted) {
            bomb_planted = true;
            is_in_round = false;
            is_retake = true;
            map->bomb_planted_sound.play();
        }
        if(is_host(client->object)){
            cool_down(ROUND_TIME_SECONDS, &is_in_round);
        } else {
            cool_down(extract_seconds_left(find_host(client->objects)), &is_in_round);
        }
    }

    void retake() {
        ready++;
        if (!map->team_ct_alive_online(*client)) {
            is_retake = false;
            score_t++;
            some_team_won = true;
            current_round_team_won = TEAM_T;
        }

        if (ready >= bomb_tick_timer) {
            map->bomb_tick_sound.play();
            bomb_tick_timer -= 1;
            ready = 0;
        }

        if (map->bomb_defused) {
            is_retake = false;
            score_ct++;
            some_team_won = true;
            current_round_team_won = TEAM_CT;
            map->bomb_defused_sound.play();
        }

        if(is_host(client->object)){
            cool_down(TIME_TO_DEFUSE_BOMB, &is_retake);
        } else {
            cool_down(extract_seconds_left(find_host(client->objects)), &is_in_round);
        }
    }

    void after_round() {
        if (bomb_planted && !map->bomb_defused && !some_team_won) {
            map->bomb_explode();
            score_t++;
            current_round_team_won = TEAM_T;
            some_team_won = true;
        }

        if (!bomb_planted && !some_team_won) {
            score_ct++;
            current_round_team_won = TEAM_CT;
            some_team_won = true;
        }

        if(current_round_team_won == TEAM_T){
            map->t_win_sound.play();
            current_round_team_won = 0;
        } else if(current_round_team_won == TEAM_CT){
            if(map->bomb_defused_sound.getStatus() != sf::Sound::Status::Playing){
                map->ct_win_sound.play();
                current_round_team_won = 0;
            }
        }
        if(is_host(client->object)){
            cool_down(AFTER_ROUND_TIME_SECONDS, &is_after_round);
        } else {
            cool_down(extract_seconds_left(find_host(client->objects)), &is_in_round);
        }
        is_reset_for_new_round = false;
    }

    void reset_for_new_round() {
        if(!game_over){
            current_round++;
            is_before_round = true;
            is_in_round = true;
            is_retake = false;
            is_after_round = true;
            some_team_won = false;
            bomb_tick_timer = BOMB_TICK_TIMER;

            bomb_planted = false;
            map->reset_for_new_round();
            map->main_player.clear_bomb_related_flags();


            if (score_t == ROUNDS_NEEDED_TO_WIN) {
                game_over = true;
                is_before_round = false;
                is_in_round = false;
                is_retake = false;
                is_after_round = false;
                some_team_won = false;
                team_won = TEAM_T;
            }

            if (score_ct == ROUNDS_NEEDED_TO_WIN) {
                game_over = true;
                is_before_round = false;
                is_in_round = false;
                is_retake = false;
                is_after_round = false;
                some_team_won = false;
                team_won = TEAM_CT;
            }

            if (current_round == 31 && score_t == score_ct) {
                game_over = true;
                is_before_round = false;
                is_in_round = false;
                is_retake = false;
                is_after_round = false;
                some_team_won = false;
            }

            if(current_round == CHANGE_TEAM_ROUND){
                change_teams();
                std::cout << "CHANGED TEAMS\n";
            }
            is_reset_for_new_round = true;
        }
    }

    void change_teams(){

        config_sprite(map->team2_player_sprite);
        config_sprite(map->team1_player_sprite);

        for(auto &[id, p] : map->players){
            if(p.team_t){
                p.sprite = map->team2_player_sprite;
            } else {
                p.sprite = map->team1_player_sprite;
            }
        }

        if(map->main_player.team_t){
            map->main_player.team_t = false;
            map->main_player.sprite = map->team2_player_sprite;
        } else {
            map->main_player.team_t = true;
            map->main_player.sprite = map->team1_player_sprite;
        }

        uint8_t temp = score_t;
        score_t = score_ct;
        score_ct = temp;
    }

    void reset(){
        current_round = 1;
        game_started = false;
        game_over = false;
        is_before_round = true;
        is_in_round = true;
        is_retake = false;
        is_after_round = true;
        is_reset_for_new_round = false;
        bomb_planted = false;
        some_team_won = false;
        bomb_tick_timer = BOMB_TICK_TIMER;
        ready = 0;
        team_won = 0;
        score_t = 0;
        score_ct = 0;
        round_seconds_left = 0;
        cool_down_started = false;
        current_round_team_won = 0;

        team_t_online.clear();
        team_ct_online.clear();
    }

    void cool_down(int seconds, bool *to_set_to_false_after_cool_down){
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        if(!cool_down_started){
            start = std::chrono::system_clock::now();
            cool_down_started = true;
        } else {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
            round_seconds_left = seconds - elapsed.count();
            if(elapsed.count() >= seconds || *to_set_to_false_after_cool_down == false){
                *to_set_to_false_after_cool_down = false;
                cool_down_started = false;
            }
        }
    }

    void synchronize_with_host(){
        Object host = find_host(client->objects);
        if(is_host(host)){
            if(!game_over){
                client->object.sync = host.sync;
            }
        } else {
            if(client->active){
                client->disconnect();
            }
        }
        object::extract_sync_values(client->object, current_round, score_t, score_ct, is_before_round, is_in_round, is_retake, is_after_round, round_seconds_left);
    }

    void synchronize_host(Object &host){
        object::synchronize_host(host,current_round, score_t, score_ct, is_before_round, is_in_round, is_retake, is_after_round, round_seconds_left);
    }

    void update(){
        if(!game_started){
            init();
            game_started = true;
        }
        if(!game_over){
            if(is_before_round){
                before_round();
            } else if(is_in_round){
                in_round();
            } else if(is_retake){
                retake();
            } else if(is_after_round){
                after_round();
            } else {
                reset_for_new_round();

                // this is a very bad way of doing this ... too bad!
                if(map->main_player.team_t && client->object.team != TEAM_T){
                    client->object.team = TEAM_T;
                } else if(!map->main_player.team_t && client->object.team == TEAM_T) {
                    client->object.team = TEAM_CT;
                }
            }
        }

    }
};