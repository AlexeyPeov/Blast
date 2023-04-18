#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <valarray>
#include "Player.h"
#include "SpriteMethods.h"
#include "Animation.h"
#include "Missile.h"

#define UNBREAKABLE_WALL 2
#define WALL 1
#define FLOOR 0

#include "Server.h"

struct Wall {
    sf::Sprite sprite;
    int hp = 4;
};

std::string current_dir();

struct Map {

    sf::Texture wall_texture_5, wall_texture_4, wall_texture_3, wall_texture_2, wall_texture_1, wall_texture_unbreakable;
    sf::Texture floor_texture;
    sf::Texture player_texture;
    sf::Texture explosion_texture;

    sf::Texture missile_texture;

    sf::Sprite wall_sprite;
    sf::Sprite unbreakable_wall_sprite;
    sf::Sprite floor_sprite;
    sf::Sprite player_sprite;
    sf::Sprite explosion_sprite;
    sf::Sprite missile_sprite;

    std::vector<Wall> walls;
    std::vector<sf::Sprite> floors;
    std::unordered_map<int, Player> players;
    std::vector<Animation> explosions;
    std::vector<Missile> missiles;
    Player main_player;

    void init_map_textures();

    void init_walls(int level);

    void init_main_player();

    Player init_new_player(int id, float pos_x, float pos_y) const;

    void init_missile_as_connected_player(Player &player);

    bool init_missile_as_main_player(Player &player);

    void init_explosion(Missile &missile);

    void update_walls();

    static void update_missile(Missile &missile);

    void update_missiles();

    void update_explosions();

    void update_players(Client &client);

    void update_player();

    void main_player_move(sf::View &view, sf::RenderWindow &window, Client &client, float deltaTime = 2.0);

    void check_collision_walls_players();

    void check_collision_player_players();

    void check_collision_missiles_walls_players();

    void draw_walls(sf::RenderWindow &window);

    void draw_floors(sf::RenderWindow &window);

    void draw_missiles(sf::RenderWindow &window);

    void draw_players(sf::RenderWindow &window);

    void draw_explosions(sf::RenderWindow &window);


};
