#include <SFML/Graphics.hpp>
#include "Map.h"

const uint8_t BEFORE_ROUND_TIME_SECONDS = 4;
const uint8_t AFTER_ROUND_TIME_SECONDS = 5;
const uint8_t ROUND_TIME_SECONDS =  165;//165;
const uint8_t TIME_TO_DEFUSE_BOMB = 45;

const uint8_t BOMB_TICK_TIMER = 72;
const uint8_t CHANGE_TEAM_ROUND = 16;
const uint8_t ROUNDS_NEEDED_TO_WIN = 16;


const uint8_t TEAM_T = 1;
const uint8_t TEAM_CT = 2;

struct Takeover {

    Map *map;

    uint8_t current_round = 1;
    bool game_over = false;

    bool is_before_round = true;
    bool is_in_round = true;
    bool is_retake = false;
    bool is_after_round = true;


    sf::Vector2f t_spawn = {188, 1790};
    sf::Vector2f ct_spawn = {310, 445};

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

    explicit Takeover(Map *map) {
        this->map = map;
    }

    Takeover(){}

    ~Takeover(){}

    void before_round() {
        cool_down(BEFORE_ROUND_TIME_SECONDS, &is_before_round);
        if (map->main_player.team_t) {
            map->main_player.sprite.setPosition(t_spawn);
        } else {
            map->main_player.sprite.setPosition(ct_spawn);
        }
        map->main_player.freeze();

        map->main_player.hp = 100;
        map->main_player.mag_ammo = mag_capacity;
        map->main_player.leftover_ammo = max_ammo; //

        map->spawn_bomb({t_spawn.x + 40, t_spawn.y});
    }

    void in_round() {
        if (!map->team_t_alive()) {
            is_in_round = false;
            score_ct++;
            current_round_team_won = TEAM_CT;
            some_team_won = true;
        }
        if (!map->team_ct_alive()) {
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
        cool_down(TIME_TO_DEFUSE_BOMB, &is_retake);
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
            map->reset();
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
            }
        }
    }

    void change_teams(){
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
        game_over = false;
        is_before_round = true;
        is_in_round = true;
        is_retake = false;
        is_after_round = true;
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
};