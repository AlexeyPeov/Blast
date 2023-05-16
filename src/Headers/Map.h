#ifndef MAP_H
#define MAP_H


#include <filesystem>
#include <valarray>
#include <unordered_set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Missile.h"
#include "PathFinder.h"
#include "Object.h"
#include "Player.h"
#include "Levels.h"


#define IRRELEVANT_WALL 3
#define UNBREAKABLE_WALL 2
#define WALL 1
#define FLOOR 0


struct Wall {
    sf::Sprite sprite;
    int hp = 4;
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
    sf::RenderTexture shadowCastTexture;

    uint32 width = 0;
    uint32 height = 0;
    int8 map_level = 0;

    uint64 main_player_id = 0;

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
    std::pair<bool, sf::Sprite> bomb; // if true - it's picked up, false - dropped
    std::unordered_map<uint64_t, Player> players;
    std::vector<Animation> explosions;
    std::vector<Missile> missiles;


    //Player main_player;

    std::unordered_map<sf::Vector2f, Wall, Vector2fHash> walls_for_collision_map;
    std::unordered_map<sf::Vector2f, Wall, Vector2fHash> walls_map;


    GameState *gameState = nullptr;


    bool bomb_planted = false;
    bool bomb_defused = false;


    Map() = default;
    ~Map() = default;

    void init_map_textures();

    void init_walls(short level);

    void init_main_player(short team);

    Player init_new_player(uint64_t id, float pos_x, float pos_y, uint8 team) const;

    void init_explosion(Missile &missile);

    void update_walls();

    static void update_missile(Missile &missile);

    void update_missiles();

    void update_explosions();

//    void update_players(Client &client); // WRONG!
//
//    void update_main_player(Client &client);

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

    void init_missile(Player &player, PlayerObject &object);

    void init_map_sounds();

    void spawn_bomb(sf::Vector2f position);

    void check_collision_players_bomb();

    sf::Vector2f calculate_3x3_non_wall_position(const sf::Vector2f &position, const float rotation) const ;

    bool team_t_alive();

    bool team_ct_alive();

    bool team_t_alive_offline();

    bool team_ct_alive_offline();

    void reset_for_new_round();

    void bomb_explode();

    void draw_plant_defuse_animations(sf::RenderWindow &window);

    void init_missile(Player &player);

    void update_bots();

    void update_player_online(Player &player, PlayerObject &object, PlayerEvent &player_event);

    void update_main_player();

    void check_collision_walls_players_online();

    void update_players_online(std::unordered_map<uint64_t, PlayerObject> &objects);

    void check_collision_missiles_walls_players_online(std::unordered_map<uint64_t, PlayerObject> &objects);

    void update_online(std::vector<PlayerObject> &player_objects,
                       std::vector<MissileObject> &missile_objects);

    void update_player(Player &player);

    void update_and_draw_players(sf::RenderWindow &window, sf::Vector2f &mouse_position, bool gained_focus);

    void update_players(PlayerEvent &player_event);

    void play_tick(std::vector<std::pair<uint64, PlayerEvent>> &player_events);

    void update_players(std::vector<std::pair<uint64, PlayerEvent>> &player_events);

    void check_collision_players();

    void play_tick_and_draw(sf::RenderWindow &window, sf::Vector2f mouse_position, bool gained_focus);

    void update_and_draw_missiles(sf::RenderWindow &window);

    void update_and_draw_explosions(sf::RenderWindow &window);
};
#endif