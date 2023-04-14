#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <valarray>
#include "Levels.h"
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

std::string current_dir(){
    return std::filesystem::current_path().string();
}

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
    std::vector<Player> players;
    std::vector<Animation> explosions;
    std::vector<Missile> missiles;
    Player main_player;

    void init_map_textures() {

        this->player_texture.loadFromFile(current_dir() + "/textures/personStationary.png");

        this->wall_texture_unbreakable.loadFromFile(current_dir() + "/textures/unbreakableBorder.png");
        this->floor_texture.loadFromFile(current_dir() + "/textures/floor.png");
        this->wall_texture_5.loadFromFile(current_dir() + "/textures/border5.png");
        this->wall_texture_4.loadFromFile(current_dir() + "/textures/border4.png");
        this->wall_texture_3.loadFromFile(current_dir() + "/textures/border3.png");
        this->wall_texture_2.loadFromFile(current_dir() + "/textures/border2.png");
        this->wall_texture_1.loadFromFile(current_dir() + "/textures/border1.png");

        this->missile_texture.loadFromFile(current_dir() + "/textures/missle.png");

        this->explosion_texture.loadFromFile(current_dir() + "/textures/explosion.png");


        this->player_sprite = sf::Sprite(player_texture);

        this->missile_sprite = sf::Sprite(missile_texture);

        this->explosion_sprite = sf::Sprite(explosion_texture);

        this->wall_sprite = sf::Sprite(wall_texture_5);
        this->unbreakable_wall_sprite = sf::Sprite(wall_texture_unbreakable);
        this->floor_sprite = sf::Sprite(floor_texture);

        explosion_sprite.setOrigin(40.f / 2.f, (float) explosion_sprite.getTexture()->getSize().y / 2.f);
    }

    void init_walls(int level) {

        int *arr;

        if (level == 1) arr = &level_1[0];
        if (level == 2) arr = &level_2[0];
        if (level == 3) arr = &level_3[0];

        for (int position = 0; position < 800; position++) {

            Wall wall;

            int x = ((position % 40) * 40) + 20;
            int y = ((position / 40) * 40) + 20;


            if (arr[position] == UNBREAKABLE_WALL) {
                wall = {.sprite = unbreakable_wall_sprite, .hp = 99999999};
            } else if (arr[position] == WALL) {
                wall = {.sprite = wall_sprite, .hp = 5};
            }

            if (arr[position] != FLOOR) {
                wall.sprite.setPosition(x, y);
                config_sprite(wall.sprite);
                walls.push_back(wall);
            } else {
                floor_sprite.setPosition(x, y);
                floor_sprite.setOrigin(floor_sprite.getTexture()->getSize().x / 2,
                                       floor_sprite.getTexture()->getSize().y / 2);
                floors.push_back(floor_sprite);
            }
        }

    }

    void init_main_player(const Client &client) {
        int movement_speed = 3;
        int rotation_degree = 0;
        int hp = 100;
        main_player = Player(player_sprite, movement_speed, rotation_degree, hp, client.object.id);
        config_sprite(main_player.sprite);
        main_player.sprite.setPosition(100, 100);
    }

    void init_players(const Client &client) {

        int movement_speed = 3;
        int rotation_degree = 0;
        int hp = 100;
        for(auto player : client.objects){
            Player connected_player = Player(player_sprite, movement_speed, rotation_degree, hp, player.id);
            connected_player.sprite.setPosition(player.pos_x, player.pos_y);
            config_sprite(main_player.sprite);
            players.push_back(connected_player);
        }
    }

    void init_missile(Player &player) {
        if (player.timeSinceLastShot > player.shootDelay) {
            int movement_speed = 40;
            int rotation_degree = player.rotation_degree;
            Missile missile = Missile(missile_sprite, movement_speed, rotation_degree);
            config_sprite(missile.sprite);

            missile.sprite.setRotation(player.sprite.getRotation());

            float xToRad = missile.sprite.getRotation() * M_PI / 180;
            float dx = 30 * sin(xToRad);
            float dy = 30 * cos(xToRad);
            missile.sprite.setPosition(player.sprite.getPosition().x + dx, player.sprite.getPosition().y - dy);

            player.timeSinceLastShot = 0;

            missiles.push_back(missile);
        }
    }

    void init_explosion(Missile &missile) {
        Animation explosion = Animation(explosion_sprite, 680 / 17, 40, 17, 2);
        explosion.sprite.setPosition(missile.sprite.getPosition());
        explosions.push_back(explosion);
    }

    void update_walls() {
        for (auto wall = walls.begin(); wall != walls.end();) {

            if (wall->hp < 5) {
                if (wall->hp == 4) { wall->sprite.setTexture(wall_texture_4); }
                else if (wall->hp == 3) { wall->sprite.setTexture(wall_texture_3); }
                else if (wall->hp == 2) { wall->sprite.setTexture(wall_texture_2); }
                else if (wall->hp == 1) { wall->sprite.setTexture(wall_texture_1); }
            }
            if (wall->hp <= 0) {
                wall = walls.erase(wall);
            } else {
                wall++;
            }
        }
    }

    static void update_missile(Missile &missile){
        float xToRad = missile.sprite.getRotation() * M_PI / 180;
        float dx = missile.movement_speed * sin(xToRad);
        float dy = missile.movement_speed * cos(xToRad);
        missile.sprite.setPosition(missile.sprite.getPosition().x + dx, missile.sprite.getPosition().y - dy);
    }

    void update_missiles() {
        for (auto missile = missiles.begin(); missile != missiles.end();) {
            if (missile->life) {
                missile->previousPosition = missile->sprite.getPosition();
                update_missile(*missile);
                missile++;

            } else {
                missile = missiles.erase(missile);
            }
        }
    }

    void update_explosions() {
        for (auto explosion = explosions.begin(); explosion != explosions.end();) {
            explosion->update();
            if (!explosion->finished) {
                explosion++;
            } else {
                explosion = explosions.erase(explosion);
            }

        }
    }

    void update_players(Client &client) {

        /*
         * check if there are new connected players, if so - add them to list of players
         *
         *      if client.objects.size() > players.size()
         *          for each object in client.objects
         *              for each player in players
         *                  if object
         *
         *
         * check if there are players that disconnected, if so - delete them
         *
         *
         * */

        for (auto player = players.begin(); player != players.end(); ) {
            if (player->hp <= 0){
                player = players.erase(player);
            } else {
                player->timeSinceLastShot += 1;
                player++;
            }
        }
    }

    void update_player() {
        if (main_player.hp > 0) {
            main_player.timeSinceLastShot += 1;
        }
    }


    void main_player_move(sf::View &view, sf::RenderWindow &window){

        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mouse_position);

        view.setCenter(main_player.sprite.getPosition());
        window.setView(view);
        main_player.move(worldMousePos);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            init_missile(main_player);
        }
    }


    void check_collision_walls_players(){
        for(auto& wall : walls){
            int wall_can_move = false;
            int player_can_move = true;
            for (auto& player : players){
                collision(wall.sprite, player.sprite, wall_can_move, player_can_move);
            }
            collision(wall.sprite, main_player.sprite, wall_can_move, player_can_move);
        }
    }

    void check_collision_missiles_walls_players(){
        for (auto& missile : missiles) {

            sf::Vector2f missileDisplacement = missile.sprite.getPosition() - missile.previousPosition;
            float maxDisplacement = std::max(std::abs(missileDisplacement.x), std::abs(missileDisplacement.y));
            int steps = std::ceil(maxDisplacement);
            int wall_can_move = false;
            int missile_can_move = true;

            for (int i = 1; i <= steps; ++i) {
                if(!missile.life) break;
                float t = static_cast<float>(i) / steps;

                missile.sprite.setPosition(missile.previousPosition + missileDisplacement * t);

                for (auto& wall : walls) {
                    if (collision(wall.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                        wall.hp -= 1;
                        missile.life = false;
                        init_explosion(missile);
                        break;
                    }
                }
                for (auto& player : players) {
                    if (collision(player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                        player.hp -= 50;
                        missile.life = false;
                        init_explosion(missile);
                        break;
                    }
                }

                if (collision(main_player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                    main_player.hp -= 50;
                    missile.life = false;
                    init_explosion(missile);
                    break;
                }
            }
        }
    }


    void draw_walls(sf::RenderWindow &window){
        for (const auto& wall : walls) window.draw(wall.sprite);
    }
    void draw_floors(sf::RenderWindow &window){
        for (const auto& floor : floors) window.draw(floor);
    }
    void draw_missiles(sf::RenderWindow &window){
        for (const auto& missile : missiles) window.draw(missile.sprite);
    }
    void draw_players(sf::RenderWindow &window){
        for (const auto& player : players) window.draw(player.sprite);
    }
    void draw_explosions(sf::RenderWindow &window){
        window.draw(main_player.sprite);
        for (const auto& explosion : explosions) window.draw(explosion.sprite);
    }


    //castRays(window, map.players[0].sprite.getPosition(), map.walls);

};
