#pragma once
#include <utility>

#include "Entity.h"
#include "KeyBoard.h"
#include "Object.h"
#include "SpriteMethods.h"
#include "Animation.h"
#include "Client.h"
#include "Enums.h"
#include <random>

const int max_ammo = 90;
const int mag_capacity = 30;
const int reload_time = 60 * 3;
const float running_ms = 2.9;
const float walking_ms = 1.5;

const int defuse_time = 60 * 6;
const int plant_time = 60 * 3.5;

const int SHOOT_DELAY = 6;
static std::mt19937 generator(std::random_device{}());

struct Player : Entity {
    uint64_t id = 0;
    int hp = 0;
    int kills = 0;
    int deaths = 0;
    int timeSinceLastShot = 0;
    int timer = 0;
    int mag_ammo = 30;
    int leftover_ammo = max_ammo;
    int reload_process = 0;
    bool team_t = false;


    bool has_bomb = false;

    bool planted_bomb = false;
    bool defused_bomb = false;

    sf::Sound running_sound;
    sf::Sound single_shot_sound;
    sf::Sound reload_sound;

    bool reloading = false;
    bool running = true;
    bool walking = false;
    bool shooting = false;

    bool gained_focus = false;

    Player(){}
    Player(sf::Sprite sprite, float movement_speed, float rotation_degree, int hp, uint64_t id)
        : Entity{ std::move(sprite), movement_speed, rotation_degree}, hp{hp}, id{id}{}

    void reload(){
        if(leftover_ammo > 0 && reloaded()){
            int how_much_to_insert = mag_capacity - mag_ammo;
            if(how_much_to_insert > leftover_ammo) {
                how_much_to_insert = leftover_ammo;
            }
            leftover_ammo -= how_much_to_insert;
            mag_ammo += how_much_to_insert;
            reloading = false;
        }
    }

    bool can_shoot() const{
        if (timeSinceLastShot > SHOOT_DELAY && mag_ammo > 0 && !reloading) {
            return true;
        }
        return false;
    }

    bool if_wants_or_needs_to_reload() {
        if((KeyBoard::keyClicked(sf::Keyboard::R) || mag_ammo == 0) && !reloading && mag_ammo != mag_capacity && leftover_ammo > 0){
            reloading = true;
            return true;
        }
        return false;
    }

    bool reloaded(){
        if(reload_process >= reload_time){
            reload_process = 0;
            return true;
        }
        return false;
    }

    void handle_movement(){
        if(hp > 0){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && movementKeysPressed()){
                movement_speed = walking_ms;
                running = false;
                walking = true;
            } else if (movementKeysPressed()) {
                movement_speed = running_ms;
                running = true;
                walking = false;
            } else {
                running = false;
                walking = false;
            }
        } else {
            running = false;
            walking = false;
        }
    }

    static bool movementKeysPressed(){
        return  sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    }

    float missile_rotation_based_on_movement() const {
        std::uniform_real_distribution<float> distribution(-135.f / 2, 135.f / 2);
        float rotation = sprite.getRotation();
        if(running){
            rotation += distribution(generator);
        } else if(walking){
            distribution.param(std::uniform_real_distribution<float>::param_type(-25.f / 2, 25.f / 2));
            rotation += distribution(generator);
        }
        return rotation;
    }

    bool wants_to_drop_bomb(){
        if((KeyBoard::keyClicked(sf::Keyboard::G)) && has_bomb){
            has_bomb = false;
            return true;
        }
        return false;
    }

    void transfer_data_from(Object& object){
        id = object.id;
        hp = object.hp;
        kills = object.kills;
        deaths = object.deaths;
        team_t = (object.team == 1);

        has_bomb = object::is_bomb_carrier(object);

        reloading = object::is_reloading(object);
        running = object::is_running(object);
    }
    void transfer_data_to(Object& object) {
        object.hp = hp;
        object.kills = kills;
        object.deaths = deaths;
        if(has_bomb){
            object::has_bomb(object);
        } else {
            object::doesnt_have_bomb(object);
        }


        if (shooting) {
            object::shoot(object);
            object.missile_rotation = missile_rotation_based_on_movement();
        }


        if(reloading){
            object::reload_start(object);
        } else {
            object::reload_end(object);
        }

        if(running){
            object::run(object);
        } else {
            object::walk(object);
        }

        object.pos_x = sprite.getPosition().x;
        object.pos_y = sprite.getPosition().y;
        object.rotation = sprite.getRotation();
        team_t = (object.team == 1);
    }

    void plant_bomb(sf::Sprite &plant_area, sf::Sprite &bomb, bool obj_shooting, Animation &plant_animation){
        if(team_t && has_bomb && !this->planted_bomb){
            if(timer != 0) {
                plant_animation.sprite.setPosition(sprite.getPosition());
                plant_animation.update();
            } else {
                timer = 0;
                plant_animation.reset();
            }
            if(
                    sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
                    collision(sprite, plant_area, false, false) &&
                    !walking && !running && !reloading && !obj_shooting && !planted_bomb && hp > 0
                    ){
                timer++;
                if(timer >= plant_time){
                    this->planted_bomb = true;
                    plant_animation.reset();
                    bomb.setPosition(sprite.getPosition());
                }
            } else {
                timer = 0;
                plant_animation.reset();
            }
        }
    }

    void defuse_bomb(sf::Sprite &bomb, bool obj_shooting, Animation &defuse_animation){
        if(!team_t){
            if(timer != 0) {
                defuse_animation.sprite.setPosition(bomb.getPosition());
                defuse_animation.update();
            } else {
                defuse_animation.reset();
            }
            if(
                    sf::Keyboard::isKeyPressed(sf::Keyboard::E)
                    && collision(sprite, bomb, false, false) &&
                    !walking && !running && !reloading && !obj_shooting && !defused_bomb && hp > 0
                    ){
                timer++;
                if(timer >= defuse_time){
                    defused_bomb = true;
                }
            } else {
                timer = 0;
                defuse_animation.reset();
            }
        }
    }

    void clear_bomb_related_flags(){
        has_bomb = false;
        planted_bomb = false;
        defused_bomb = false;
        timer = 0;
    }

    void freeze(){
        timeSinceLastShot = 0;
        running_sound.pause();
    }

    void move_on_map(sf::View &view, sf::RenderWindow &window, Client &client, GameState &gameState, bool focus, float deltaTime) {

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
    }

};
