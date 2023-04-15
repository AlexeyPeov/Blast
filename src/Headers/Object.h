#pragma once

#include <vector>
#include <cstring>

#define MOVE 1
#define SHOOT 2

struct Object {
    int id;
    float pos_x;
    float pos_y;
    float rotation;
    short action;
};


namespace object{

    void move(Object &object){
        object.action |= MOVE;
    }

    void shoot(Object &object){
        object.action |= SHOOT;
    }

    void dont_move(Object &object){
        object.action &= ~MOVE;
    }

    void dont_shoot(Object &object){
        object.action &= ~SHOOT;
    }

    bool is_moving(Object &object){
        if (object.action & MOVE) {
            return true;
        }
        return false;
    }

    bool is_shooting(Object &object){
        if (object.action & SHOOT) {
            return true;
        }
        return false;
    }

    std::vector<char> serialize_object(const Object& object) {
        std::vector<char> data;
        data.resize(sizeof(Object));
        memcpy(data.data(), &object, sizeof(Object));
        return data;
    }

    std::vector<char> serialize_objects(const std::vector<Object>& objects) {
        std::vector<char> data;
        data.resize(objects.size() * sizeof(Object));
        memcpy(data.data(), objects.data(), data.size());
        return data;
    }

    void deserialize_objects(const std::vector<char>& data, std::vector<Object>& objects) {
        if (data.size() % sizeof(Object) != 0) {
            std::cerr << "Error: data size is not a multiple of Object size\n";
            return;
        }
        size_t object_count = data.size() / sizeof(Object);
        objects.resize(object_count);
        memcpy(objects.data(), data.data(), data.size());
    }

    void deserialize_object(const std::vector<char>& data, Object & object) {
        if (data.size() < sizeof(Object)) {
            std::cerr << "Error: not enough data to deserialize Object\n";
            return;
        }
        memcpy(&object, data.data(), sizeof(Object));
    }
}