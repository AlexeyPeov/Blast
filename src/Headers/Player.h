#pragma once
#include <utility>

#include "Entity.h"
#include "KeyBoard.h"
const int max_ammo = 90;
const int mag_capacity = 30;
const int reload_time = 60 * 3;

struct Player : Entity {
    int id = 0;
    int hp = 0;
    int kills = 0;
    int deaths = 0;
    int shootDelay = 6;
    int timeSinceLastShot = 0;
    int mag_ammo = 30;
    int leftover_ammo = max_ammo;
    int reload_process = 0;
    bool reloading = false;

    Player(){}
    Player(sf::Sprite sprite, float movement_speed, float rotation_degree, int hp, int id)
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
        if (timeSinceLastShot > shootDelay && mag_ammo > 0 && !reloading) {
            return true;
        }
        return false;
    }

    bool if_wants_or_needs_to_reload() {
        if((KeyBoard::keyClicked(sf::Keyboard::R) || mag_ammo == 0) && !reloading){
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
};
