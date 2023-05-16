#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>

typedef sf::Uint8 uint8;
typedef sf::Uint16 uint16;
typedef sf::Uint32 uint32;
typedef sf::Uint64 uint64;

typedef sf::Int8 int8;
typedef sf::Int16 int16;
typedef sf::Int32 int32;
typedef sf::Int64 int64;

typedef float float32;
typedef double float64;




const size_t MAX_PLAYERS_ON_SERVER = 10;

const int32 MAX_MAP_WIDTH = 50;
const int32 MAX_MAP_HEIGHT = 50;

const int8 NICKNAME_LENGTH = 15;


const int32 MISSILE_DAMAGE = 25;
const int32 MISSILE_MOVEMENT_SPEED = 40;

const int16 MAX_AMMO = 90;
const int32 MAG_CAPACITY = 30;
const int32 RELOAD_TIME = 60 * 3;
const float32 RUNNING_MOVEMENT_SPEED = 2.9;
const float32 WALKING_MOVEMENT_SPEED = 1.5;

const int32 DEFUSE_TIME = 60 * 6;
const int32 PLANT_TIME = 60 * 3.5;

const int32 SHOOT_DELAY = 6;

const float32 CAMERA_SMOOTHNESS = 2.0;

const bool BOMB_DROPPED = true;
const bool BOMB_PICKED_UP = false;


//takeover
const uint8 BEFORE_ROUND_TIME_SECONDS = 5;
const uint8 AFTER_ROUND_TIME_SECONDS = 4;
const uint8 ROUND_TIME_SECONDS =  140;// 140
const uint8 TIME_TO_DEFUSE_BOMB_SECONDS = 44;

const uint8 BOMB_TICK_TIMER = 72;
const uint8 CHANGE_TEAM_ROUND = 10;
const uint8 ROUNDS_NEEDED_TO_WIN = 2; // 9
const uint8 AFTER_MAX_ROUND = 17;

const uint8 TEAM_T = 1;
const uint8 TEAM_CT = 2;

#endif