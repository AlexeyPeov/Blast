#include "../Headers/Object.h"

namespace object{

    // action
// 0        1       2       3       4       5       6       7
// |        |       |        |      |        |      |        |
// shoot    map1   map2     map3    dm     tkovr   ready    host?
    void choose_map_1(Object &object){
        unchoose_maps(object);
        object.action |= (1 << 1);
    }
    void choose_map_2(Object &object){
        unchoose_maps(object);
        object.action |= (1 << 2);
    }
    void choose_map_3(Object &object){
        unchoose_maps(object);
        object.action |= (1 << 3);
    }

    void choose_map(Object &object, short map){
        if (map == 1){
            choose_map_1(object);
        } else if (map == 2){
            choose_map_2(object);
        } else if (map == 3){
            choose_map_3(object);
        }
    }

    void unchoose_maps(Object &object){
        object.action &= ~(1 << 1);
        object.action &= ~(1 << 2);
        object.action &= ~(1 << 3);
    }

    void choose_death_match(Object &object){
        object.action &= ~(1 << 5);
        object.action |= (1 << 4);
    }

    void choose_takeover(Object &object){
        object.action &= ~(1 << 4);
        object.action |= (1 << 5);
    }
    void choose_game_mode(Object &object, short gamemode){
        if (gamemode == 1){
            choose_death_match(object);
        } else if (gamemode == 2){
            choose_takeover(object);
        }
    }
    void ready(Object &object){
        if (is_ready(object)){
            object.action &= ~(1 << 6);
        } else {
            object.action |= (1 << 6);
        }
    }

    bool is_ready(Object &object){
        return (object.action & (1 << 6)) != 0;
    }

    void set_host(Object &object){
        object.action |= (1 << 7);
    }
    void set_not_host(Object &object){
        object.action &= ~(1 << 7);
    }

    short which_map_is_chosen(Object &object){
        if((object.action & (1 << 1)) != 0){
            //1
            return 1;
        } else if((object.action & (1 << 2)) != 0){
            //2
            return 2;
        } else if((object.action & (1 << 3)) != 0){
            //3
            return 3;
        }
        return 0;
    }

    short which_game_mode_is_chosen(Object &object){
        if((object.action & (1 << 4)) != 0){
            //dm
            return 1;
        } else if((object.action & (1 << 5)) != 0){
            //takeover
            return 2;
        }
        return 0;
    }

    bool is_host(Object &object){
        return (object.action & (1 << 7)) != 0;
    }
    void shoot(Object &object){
        object.action |= (1 << 0);
    }

    void dont_shoot(Object &object){
        object.action &= ~(1 << 0);
    }

    bool is_shooting(Object &object){
        return (object.action & (1 << 0)) != 0;
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
            std::cerr << "data size is not a multiple of Object size, not doing anything..\n";
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
    void copy_string_to_nickname(std::string &string, Object &object){
        if(string.empty()) return;

        int size = string.size();
        int max_char_pos = nickname_length - 1;
        if(size >= max_char_pos){
            std::copy(string.begin(), string.begin() + max_char_pos - 1, object.nickname);
            object.nickname[max_char_pos] = '\0';
        } else {
            std::copy(string.begin(), string.begin() + size, object.nickname);
            object.nickname[size + 1] = '\0';
        }
    }
}