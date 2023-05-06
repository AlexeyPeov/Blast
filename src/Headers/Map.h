#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <iostream>
#include <filesystem>
#include <valarray>
#include "Player.h"
#include "SpriteMethods.h"
#include "Animation.h"
#include "Missile.h"
#include "Enums.h"
#include "Mouse.h"
#include <unordered_set>

#define IRRELEVANT_WALL 3
#define UNBREAKABLE_WALL 2
#define WALL 1
#define FLOOR 0

#include "Server.h"

struct Wall {
    sf::Sprite sprite;
    int hp = 4;
};

std::string working_dir();

struct Vector2fHash {
    std::size_t operator()(const sf::Vector2f& v) const {
        std::size_t h1 = std::hash<float>{}(v.x);
        std::size_t h2 = std::hash<float>{}(v.y);
        return h1 ^ (h2 << 1);
    }
};

struct Map {

    sf::Texture wall_texture_5, wall_texture_4, wall_texture_3, wall_texture_2, wall_texture_1, wall_texture_unbreakable;
    sf::Texture floor_texture;
    sf::Texture team1_player_texture;
    sf::Texture team2_player_texture;
    sf::Texture explosion_texture;
    sf::Texture dropped_ammo_texture;
    sf::Texture bomb_texture;
    sf::Texture a_site_texture;
    sf::Texture plant_anim_texture;
    sf::Texture defuse_anim_texture;

    int width = 0;
    int height = 0;
    short map_level = 0;

    sf::Texture missile_texture;

    sf::Sprite wall_sprite;
    sf::Sprite unbreakable_wall_sprite;
    sf::Sprite floor_sprite;
    sf::Sprite team1_player_sprite;
    sf::Sprite team2_player_sprite;
    sf::Sprite explosion_sprite;
    sf::Sprite missile_sprite;
    sf::Sprite dropped_ammo_sprite;
    sf::Sprite bomb_sprite;
    sf::Sprite a_site_sprite;


    sf::Sprite plant_anim_sprite;
    sf::Sprite defuse_anim_sprite;

    sf::RenderTexture unbreakable_walls_texture;
    sf::RenderTexture floors_texture;

    sf::Sprite unbreakable_walls_sprite;
    sf::Sprite floors_sprite;

    // sounds

    sf::SoundBuffer gun_reload_buffer;
    sf::SoundBuffer single_shot_buffer;
    sf::SoundBuffer running_buffer;
    sf::SoundBuffer bomb_tick_buffer;
    sf::SoundBuffer bomb_explosion_buffer;

    sf::SoundBuffer bomb_planted_buffer;
    sf::SoundBuffer bomb_defused_buffer;

    sf::SoundBuffer t_win_buffer;
    sf::SoundBuffer ct_win_buffer;


    sf::Sound bomb_tick_sound;
    sf::Sound bomb_explosion_sound;

    sf::Sound bomb_planted_sound;
    sf::Sound bomb_defused_sound;

    sf::Sound t_win_sound;
    sf::Sound ct_win_sound;


    Animation plant_animation;
    Animation defuse_animation;

    std::vector<sf::Vector2f> available_dm_spawn_positions;

    //std::vector<Wall> walls;
    //std::vector<Wall> unbreakable_walls;
    std::vector<std::pair<int, sf::Sprite>> dropped_ammo;
    std::pair<bool, sf::Sprite> bomb;
    std::unordered_map<int, Player> players;
    std::vector<Animation> explosions;
    std::vector<Missile> missiles;


    Player main_player;

    std::unordered_map<sf::Vector2f, Wall, Vector2fHash> walls_for_collision_map;
    std::unordered_map<sf::Vector2f, Wall, Vector2fHash> walls_map;


    GameState *gameState = nullptr;


    bool bomb_planted = false;
    bool bomb_defused = false;

    void init_map_textures();

    void init_walls(short level);

    void init_main_player(short team);

    Player init_new_player(int id, float pos_x, float pos_y, short team) const;

    void init_explosion(Missile &missile);

    void update_walls();

    static void update_missile(Missile &missile);

    void update_missiles();

    void update_explosions();

    void update_players(Client &client);

    void update_player(Client &client);

    void check_collision_walls_players();

    void check_collision_player_players();

    void check_collision_missiles_walls_players();

    void draw_walls(sf::RenderWindow &window);

    void draw_missiles(sf::RenderWindow &window);

    void draw_players(sf::RenderWindow &window);

    void draw_explosions(sf::RenderWindow &window);

    sf::Vector2f random_non_wall_position();

    void check_collision_players_ammo();

    void draw_dropped_ammo(sf::RenderWindow &window);

    void update_wall(Wall &wall);

    void draw_floors(sf::RenderWindow &window) const;

    void init_missile(Player &player, Object &object);

    void init_map_sounds();

    void spawn_bomb(sf::Vector2f position);

    void check_collision_players_bomb();

    sf::Vector2f calculate_3x3_non_wall_position(const sf::Vector2f &position, const float rotation) const;

    bool team_t_alive_online(Client &client);

    bool team_ct_alive_online(Client &client);

    bool team_t_alive_offline();

    bool team_ct_alive_offline();

    void reset_for_new_round();

    void bomb_explode();

    void draw_plant_defuse_animations(sf::RenderWindow &window);
};
