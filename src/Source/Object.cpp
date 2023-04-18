#include "../Headers/Object.h"

namespace object{

    void shoot(Object &object){
        object.action = SHOOT;
    }

    void dont_shoot(Object &object){
        object.action = DONT_SHOOT;
    }

    bool is_shooting(Object &object){
        return object.action == 1;
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