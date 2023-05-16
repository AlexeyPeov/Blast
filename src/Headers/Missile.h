#ifndef MISSILE_H
#define MISSILE_H

#include <utility>

#include "Entity.h"
#include "Constants.h"
#include "Object.h"

struct Missile : Entity {

    uint64 id = 0; // zero by default, when online - server sets it
    bool life = true;
    uint64 player_who_shot_id = 0;
    sf::Vector2f previousPosition = {0,0};
    int32 damage = 25;

    Missile(sf::Sprite sprite, int movement_speed, float rotation_degree)
            : Entity{ std::move(sprite), static_cast<float>(movement_speed), rotation_degree} {
    }

    void transfer_data_from(MissileObject &missile_object){
        this->id = missile_object.id;
        this->life = missile_object.life;
        this->player_who_shot_id = missile_object.player_who_shot_id;
        this->sprite.setRotation(missile_object.rotation_degree);

        this->sprite.setPosition(missile_object.position_x, missile_object.position_y);
        this->previousPosition.x = missile_object.previous_position_x;
        this->previousPosition.y = missile_object.previous_position_y;
    }

    void transfer_data_to(MissileObject& missile_object){
        missile_object.id = this->id;
        missile_object.life = this->life;
        missile_object.player_who_shot_id = this->player_who_shot_id;
        missile_object.rotation_degree = this->rotation_degree;


        missile_object.position_x = this->sprite.getPosition().x;
        missile_object.position_y = this->sprite.getPosition().y;
        missile_object.previous_position_x = this->previousPosition.x;
        missile_object.previous_position_y = this->previousPosition.y;
    }
};

#endif