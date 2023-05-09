#include "../Headers/Object.h"

namespace object{

    // action
// 0        1       2       3       4       5       6       7
// |        |       |        |      |        |      |        |
// shoot    map1   map2     map3    dm     tkovr   ready    host?


//  in_game_action
//  shoot - 0
//  wants_reload - 1
//  reload_event - 2
//  run/walk     - 3
//  has/doesnt have bomb - 4
//  drop bomb - 5
//  plant bomb - 6
//  defuse - 7
//
//

    void choose_map_1(Object &object){
        unchoose_maps(object);
        object.main_menu_action |= (1 << 1);
    }
    void choose_map_2(Object &object){
        unchoose_maps(object);
        object.main_menu_action |= (1 << 2);
    }
    void choose_map_3(Object &object){
        unchoose_maps(object);
        object.main_menu_action |= (1 << 3);
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
        object.main_menu_action &= ~(1 << 1);
        object.main_menu_action &= ~(1 << 2);
        object.main_menu_action &= ~(1 << 3);
    }

    void choose_death_match(Object &object){
        object.main_menu_action &= ~(1 << 5);
        object.main_menu_action |= (1 << 4);
    }

    void choose_takeover(Object &object){
        object.main_menu_action &= ~(1 << 4);
        object.main_menu_action |= (1 << 5);
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
            object.main_menu_action &= ~(1 << 6);
        } else {
            object.main_menu_action |= (1 << 6);
        }
    }

    bool is_ready(Object &object){
        return (object.main_menu_action & (1 << 6)) != 0;
    }

    void set_host(Object &object){
        object.main_menu_action |= (1 << 7);
    }
    void set_not_host(Object &object){
        object.main_menu_action &= ~(1 << 7);
    }

    short which_map_is_chosen(Object &object){
        if((object.main_menu_action & (1 << 1)) != 0){
            //1
            return 1;
        } else if((object.main_menu_action & (1 << 2)) != 0){
            //2
            return 2;
        } else if((object.main_menu_action & (1 << 3)) != 0){
            //3
            return 3;
        }
        return 0;
    }

    short which_game_mode_is_chosen(Object &object){
        if((object.main_menu_action & (1 << 4)) != 0){
            //dm
            return 1;
        } else if((object.main_menu_action & (1 << 5)) != 0){
            //takeover
            return 2;
        }
        return 0;
    }

    bool is_host(Object &object){
        return (object.main_menu_action & (1 << 7)) != 0;
    }
    void shoot(Object &object){
        object.in_game_action |= (1 << 0);
    }

    void dont_shoot(Object &object){
        object.in_game_action &= ~(1 << 0);
    }

    bool is_shooting(Object &object){
        if((object.in_game_action & (1 << 0)) != 0){
            dont_shoot(object);
            return true;
        }
        return false;
    }

    void wants_or_needs_to_reload(Object &object){
        object.in_game_action |= (1 << 1);
    }

    void doesnt_want_or_need_to_reload(Object &object){
        object.in_game_action &= ~(1 << 1);
    }

    bool does_want_or_need_to_reload(Object &object){
        return (object.in_game_action & (1 << 1)) != 0;
    }

    void reload_start(Object &object){
        object.in_game_action |= (1 << 3);
    }

    void reload_end(Object &object){
        object.in_game_action &= ~(1 << 3);
    }

    bool is_reloading(Object &object){
        return (object.in_game_action & (1 << 3)) != 0;
    }

    void run(Object &object){
        object.in_game_action |= (1 << 2);
    }

    void walk(Object &object){
        object.in_game_action &= ~(1 << 2);
    }

    bool is_running(Object &object){
        if((object.in_game_action & (1 << 2)) != 0){
            walk(object);
            return true;
        }
        return false;
    }


    void has_bomb(Object &object){
        object.in_game_action |= (1 << 4);
    }

    void doesnt_have_bomb(Object &object){
        object.in_game_action &= ~(1 << 4);
    }

    bool is_bomb_carrier(Object &object){
        return (object.in_game_action & (1 << 4)) != 0;
    }

    void drop_bomb(Object &object){
     //   if(is_bomb_carrier(object)){
            object.in_game_action |= (1 << 5);
            doesnt_have_bomb(object);
     //   }
    }

    void dont_drop_bomb(Object &object){
    //    if(is_bomb_carrier(object)){
            object.in_game_action &= ~(1 << 5);
     //   }
    }

    bool drops_bomb(Object &object){
       // if(is_bomb_carrier(object)){
            if ((object.in_game_action & (1 << 5)) != 0){
                return true;
            }
     //   }
        return false;
    }

    void plant_bomb(Object &object){
        object.in_game_action |= (1 << 6);
    }
    void not_plant_bomb(Object &object){
        object.in_game_action &= ~(1 << 6);
    }

    bool is_bomb_planted(Object &object) {
        return (object.in_game_action & (1 << 6)) != 0;
    }

    void defused(Object &object){
        object.in_game_action |= (1 << 7);
    }
    void not_defused(Object &object){
        object.in_game_action &= ~(1 << 7);
    }

    bool is_bomb_defused(Object &object) {
        return (object.in_game_action & (1 << 7)) != 0;
    }

    void synchronize_with_host(Object &host, Object &not_host){
        if(!is_host(not_host) && is_host(host)){
            not_host.sync = host.sync;
        }
    }

    void synchronize_host(
            Object &host,
            uint8_t current_round,
            uint8_t team_t_score,
            uint8_t team_ct_score,
            bool is_before_round,
            bool is_in_round,
            bool is_retake,
            bool is_after_round,
            uint8_t seconds
    ){
        if(is_host(host)){
            host.sync = 0;


//            host.sync |= (current_round & 0b11111) << 0;
//            host.sync |= (team_t_score & 0b1111) << 5;
//            host.sync |= (team_ct_score & 0b1111) << 9;
//
//            host.sync |= (is_before_round & 0b1) << 13;
//            host.sync |= (is_in_round & 0b1) << 14;
//            host.sync |= (is_retake & 0b1) << 15;
//            host.sync |= (is_after_round & 0b1) << 16;
//            host.sync |= (seconds & 0b11111111) << 17;


            host.sync |= (current_round & 0b11111) << 0;
            host.sync |= (team_t_score & 0b11111) << 5;
            host.sync |= (team_ct_score & 0b11111) << 10;

            host.sync |= (is_before_round & 0b1) << 15;
            host.sync |= (is_in_round & 0b1) << 16;
            host.sync |= (is_retake & 0b1) << 17;
            host.sync |= (is_after_round & 0b1) << 18;
            host.sync |= (seconds & 0b11111111) << 19;
        }
    }

    void extract_sync_values(
            const Object &object,
            uint8_t &current_round,
            uint8_t &team_t_score,
            uint8_t &team_ct_score,
            bool &is_before_round,
            bool &is_in_round,
            bool &is_retake,
            bool &is_after_round,
            uint8_t &seconds
    ) {
        current_round = (object.sync >> 0) & 0b11111;
        team_t_score = (object.sync >> 5) & 0b11111;
        team_ct_score = (object.sync >> 10) & 0b11111;
        is_before_round = (object.sync >> 15) & 0b1;
        is_in_round = (object.sync >> 16) & 0b1;
        is_retake = (object.sync >> 17) & 0b1;
        is_after_round = (object.sync >> 18) & 0b1;
        seconds = (object.sync >> 19) & 0b11111111;
    }

    uint8_t extract_seconds_left(const Object &object) {
        return (object.sync >> 19) & 0b11111111;
    }

    Object find_host(std::vector<Object> objects){
        for(auto& object : objects){
            if (is_host(object)){
                return object;
            }
        }
        Object obj;
        return obj;
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
        if(string.empty()) {
            std::strcpy(object.nickname, "anonymous");
            return;
        }

        int size = string.size();
        int max_char_pos = nickname_length - 1;

        for(int i = 0; i < nickname_length; i++){
            object.nickname[i] = '\0';
        }

        if(size >= max_char_pos){
            std::copy(string.begin(), string.begin() + max_char_pos - 1, object.nickname);
            object.nickname[max_char_pos] = '\0';
        } else {
            std::copy(string.begin(), string.begin() + size, object.nickname);
            object.nickname[size + 1] = '\0';
        }
    }
    void reset(Object &object){
        object = Object();
    }

    sf::Packet& operator<<(sf::Packet& packet, const Object& object) {
        return packet << object.id << object.nickname << object.hp << object.in_game_action
                      << object.team << object.kills << object.deaths << object.pos_x
                      << object.pos_y << object.rotation << object.missile_rotation
                      << object.main_menu_action << object.tick << object.sync;
    }

    sf::Packet& operator>>(sf::Packet& packet, Object& object) {
        return packet >> object.id >> object.nickname >> object.hp >> object.in_game_action
                      >> object.team >> object.kills >> object.deaths >> object.pos_x
                      >> object.pos_y >> object.rotation >> object.missile_rotation
                      >> object.main_menu_action >> object.tick >> object.sync;
    }

    uint64_t generate_random_id() {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<uint64_t> distribution;
        return distribution(generator);
    }

}