#ifndef TAKEOVER_H
#define TAKEOVER_H

#include <SFML/Graphics.hpp>

#include "Object.h"

struct TeamOnline{
    Player* players[5] = {nullptr};


    void insert(Player &player){
        for(auto &pl : players){
            if(pl == nullptr){
                pl = &player;
                return;
            }
        }
    }

    void clear(){
        for (auto  &obj : players){
            obj = nullptr;
        }
    }

    static sf::Vector2f get_spawn_position(Player &object){
        sf::Vector2f position = {0,0};

        float default_spawn_x = 0;
        float default_spawn_y = 0;

        if(object.team == TEAM_T){
            default_spawn_x = 188;
            default_spawn_y = 1790;

//            default_spawn_x = 710;
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
//        return sf::Vector2f { 710, 445};
    }
};

struct TeamOffline{
    Player* players[5] = {nullptr};
};

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

    TeamOnline team_t_online;
    TeamOnline team_ct_online;

    TeamOffline team_t_offline;
    TeamOffline team_ct_offline;


    Takeover(Map &map) {
        this->map = &map;
    }

    Takeover(){}

    ~Takeover(){}

    void init() {
        for (auto &[id, player] : map->players){
            if(player.team == TEAM_T){
                team_t_online.insert(player);
            } else if(player.team == TEAM_CT){
                //player.sprite.setTexture(map->team2_player_texture);
                team_ct_online.insert(player);
            }
        }
    }

    void before_round() {

        map->spawn_bomb(TeamOnline::get_bomb_spawn_position());

        cool_down(BEFORE_ROUND_TIME_SECONDS, &is_before_round);

        for(auto &[id, object] : map->players){
            sf::Vector2f spawn = TeamOnline::get_spawn_position(object);
            object.sprite.setPosition(spawn);
            object.player_state.shooting = false;
            //std::cout << "BEFORE ROUND SET POS " << spawn.x << " " << spawn.y << "\n";
            object.hp = 100;
            object.mag_ammo = MAG_CAPACITY;
            object.leftover_ammo = MAX_AMMO;
           // object.sync = sync_object();
        }

    }

    void in_round() {
        if (!map->team_t_alive()) {
            //std::cout << "TAKEOVER SAYS TEAM T IS DEAD\n";
            is_in_round = false;
            score_ct++;
            current_round_team_won = TEAM_CT;
            some_team_won = true;
        } else if (!map->team_ct_alive()) {
            //std::cout << "TAKEOVER SAYS TEAM CT IS DEAD\n";
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
//        for(auto &[id, object] : objects){
//            object.sync = sync_object();
//        }
        cool_down(ROUND_TIME_SECONDS, &is_in_round);

    }

    void retake() {
        ready++;
        if (!map->team_ct_alive()) {
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

//        for(auto &[id, object] : map->players){
//            object.sync = sync_object();
//        }

        cool_down(TIME_TO_DEFUSE_BOMB_SECONDS, &is_retake);

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

        cool_down(AFTER_ROUND_TIME_SECONDS, &is_after_round);

//        for(auto &[id, object] : objects){
//            object.sync = sync_object();
//        }

        is_reset_for_new_round = false;
    }

    void change_teams(Player &player) {
        if(player.team == TEAM_T){
            player.team = TEAM_CT;
            player.sprite.setTexture(map->team2_player_texture);
        } else {
            player.team = TEAM_T;
            player.sprite.setTexture(map->team1_player_texture);
        }
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

            for(auto & player : map->players){
                player.second.clear_bomb_related_flags();
            }


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

            if (current_round == AFTER_MAX_ROUND && score_t == score_ct) {
                game_over = true;
                is_before_round = false;
                is_in_round = false;
                is_retake = false;
                is_after_round = false;
                some_team_won = false;
            }

            if(current_round == CHANGE_TEAM_ROUND){
                for(auto &[id, object] : map->players){
                    change_teams(object);
                }
                uint8_t temp = score_t;
                score_t = score_ct;
                score_ct = temp;

                TeamOnline temp_team = team_t_online;
                team_t_online = team_ct_online;
                team_ct_online = temp_team;
                std::cout << "CHANGED TEAMS\n";
            }

            for(auto &[id, object] : map->players){
                //object.sync = sync_object();
                object.player_state = {0};
            }
            is_reset_for_new_round = true;
        }
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

    Sync sync_object() {
        return Sync {
                .current_round  = current_round,
                .team_t_score  = score_t,
                .team_ct_score = score_ct,
                .is_before_round = is_before_round,
                .is_in_round  = is_in_round,
                .is_retake = is_retake,
                .is_after_round = is_after_round,
                .round_seconds_left = round_seconds_left,
                .game_over = game_over,
        };
    }

    void sync_takeover(Sync &sync){
        current_round = sync.current_round;
        score_t = sync.team_t_score;
        score_ct = sync.team_ct_score;
        is_before_round = sync.is_before_round;
        is_in_round = sync.is_in_round;
        is_retake = sync.is_retake;
        is_after_round = sync.is_after_round;
        game_over = sync.game_over;
       // some_team_won = sync.some_team_won;
    }

    void update() {
        if (is_before_round) {
            before_round();
        } else if (is_in_round) {
            in_round();
        } else if (is_retake) {
            retake();
        } else if (is_after_round) {
            after_round();
        } else {
            reset_for_new_round();
        }
    }
};

#endif
