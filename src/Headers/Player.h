#ifndef PLAYER_H
#define PLAYER_H


#include <utility>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>


#include "Entity.h"
#include "Constants.h"
#include "Animation.h"
#include "Enums.h"
#include "Object.h"
#include "KeyBoard.h"
#include "Mouse.h"


struct Player : Entity {
    uint64 id = 0;
    int32 hp = 0;
    sf::Int16 kills = 0;
    sf::Int16 deaths = 0;
    sf::Uint32 shoot_timer = 0;
    sf::Uint32 plant_or_defuse_timer = 0;
    int16 mag_ammo = 30;
    int16 leftover_ammo = MAX_AMMO;
    sf::Uint32 reload_timer = 0;
    uint8 team;

    bool camera_centered = false;

    PlayerState player_state = {0};

    sf::Sound running_sound;
    sf::Sound single_shot_sound;
    sf::Sound reload_sound;

    Animation plant_animation;
    Animation defuse_animation;


    Player(){}
    Player(sf::Sprite sprite, float movement_speed, float rotation_degree, int hp, uint64_t id, uint8 team, Animation &plant_animation, Animation &defuse_animation)
        : Entity{ std::move(sprite), movement_speed, rotation_degree}, hp{hp}, id{id}, team{team}, plant_animation{plant_animation}, defuse_animation{defuse_animation}{
        this->movement_speed = movement_speed;
        this->rotation_degree = rotation_degree;
        this-> hp = hp;
        this->id = id;
        this->team = team;
        this->plant_animation = plant_animation;
        this->defuse_animation = defuse_animation;
    }

    void reload();

    bool can_shoot();

    bool if_wants_or_needs_to_reload();

    bool reloaded();

    void handle_movement();

    static bool movementKeysPressed();

    float missile_rotation_based_on_movement() const;

    void drop_bomb(std::pair<bool, sf::Sprite> &bomb, sf::Vector2f position);

    void transfer_data_from(const PlayerObject& object);

    void transfer_data_to(PlayerEvent &player_event, bool gained_focus);

    void plant_bomb(sf::Sprite &plant_area, std::pair<bool, sf::Sprite> &bomb, bool pressed_plant_button);

    void defuse_bomb(std::pair<bool, sf::Sprite> &bomb, bool pressed_defuse_button);

    void clear_bomb_related_flags();

    void freeze();


    /*void move_on_map_offline(sf::View &view, sf::RenderWindow &window, Client &client, GameState &gameState, bool focus, float deltaTime) {

        this->gained_focus = focus;
        if (id == 0) {
            id = client.id;
        }
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mouse_position);
        shooting = false;

        // Update the view gradually if the mouse is on the full top/bottom/left/right of the screen
        if (gained_focus && gameState == GameState::IN_GAME) {
            if (mouse_position.x <= 5) {
                view.move(-3.0f * deltaTime, 0);
                window.setView(view);
            } else if (mouse_position.x >= (window.getSize().x - 5)) {
                view.move(3.0f * deltaTime, 0);
                window.setView(view);
            } else if (mouse_position.y <= 5) {
                view.move(0, -3.0f * deltaTime);
                window.setView(view);
            } else if (mouse_position.y >= (window.getSize().y - 5)) {
                view.move(0, 3.0f * deltaTime);
                window.setView(view);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                view.setCenter(sprite.getPosition());
                window.setView(view);
            }
        }
        if (hp > 0) {
            if (gained_focus && gameState == GameState::IN_GAME) {
                if (move(worldMousePos) && running){


                    if(std::abs(client.object.pos_x - sprite.getPosition().x) < 2 && std::abs(client.object.pos_y - sprite.getPosition().y) < 2){
                        running = false;
                    }
                    if(running){
                        running_sound.setVolume(60);
                        running_sound.setPosition(client.object.pos_x, client.object.pos_y, 0.f);
                    } else {
                        running_sound.setVolume(0);
                        running_sound.play();
                    }
                } else {
                    running_sound.setVolume(0);
                    running_sound.play();
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (can_shoot()) {
                        shooting = true;
                    } else {
                        shooting = false;
                    }
                } else {
                    shooting = false;
                }
            }
            //   client.object.pos_x = main_player.sprite.getPosition().x;
            //   client.object.pos_y = main_player.sprite.getPosition().y;
            //  client.object.rotation = main_player.sprite.getRotation();
        }

        //if (main_player.has_bomb) {object::has_bomb(client.object);}
        //client.object.hp = main_player.hp;
        //client.object.kills = main_player.kills;
        // client.object.deaths = main_player.deaths;
        // main_player.team_t = (client.object.team == 1);
    }*/

    void move_on_map(sf::View &view, sf::RenderWindow &window, GameState &gameState, bool gained_focus);

    void handle_camera_movement(sf::RenderWindow &window, bool gained_focus, GameState &gameState, sf::View &view, sf::Vector2i &mouse_position);

    void verify();

    void rotate(sf::Vector2f &mouse_position);

    void get_inputs(PlayerEvent &player_event);

    void verify_and_assign_player_state(PlayerEvent &player_event);

    void verify_need_to_reload(bool reload_button_pressed);

    void transfer_data_to(PlayerObject &object);

    //void defuse_bomb(std::pair<bool, sf::Sprite> &bomb, bool obj_shooting, Animation &defuse_animation);
};
#endif