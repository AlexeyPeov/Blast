#include "../Headers/Object.h"

std::string working_dir() {
    return std::filesystem::current_path().string();
}


namespace obj {

    void freeze(PlayerObject &object, sf::Vector2f position) {

    }

    void set_default_values(PlayerObject &object) {
        object.hp = 100;
        object.kills = 0;
        object.deaths = 0;
        object.sync = {0};
        object.player_state = {0};
    }


    /*void reload(Player &player, PlayerObject &object) {

        if (object.leftover_ammo > 0 && reloaded(object)) {
            int how_much_to_insert = MAG_CAPACITY - object.mag_ammo;
            if (how_much_to_insert > object.leftover_ammo) {
                how_much_to_insert = object.leftover_ammo;
            }
            object.leftover_ammo -= how_much_to_insert;
            object.mag_ammo += how_much_to_insert;
            object.player_state.reloading = false;

            player.leftover_ammo = object.leftover_ammo;
            player.mag_ammo = object.mag_ammo;
            player.reloading = false;

        }
    }*/

    bool can_shoot(PlayerObject &object) {
        if (object.shoot_timer > SHOOT_DELAY && object.mag_ammo > 0 && !object.player_state.reloading) {
            object.player_state.shooting = true;
            return true;
        }
        return false;
    }


    bool reloaded(PlayerObject &object) {
        if (object.reload_timer >= RELOAD_TIME) {
            object.reload_timer = 0;
            return true;
        }
        return false;
    }


    double missile_rotation_based_on_movement(PlayerObject &object, double &rotation) {
        std::uniform_real_distribution<double> distribution(-135.f / 2, 135.f / 2);
        if (object.player_state.running) {
            rotation += distribution(generator);
        } else if (object.player_state.walking) {
            distribution.param(std::uniform_real_distribution<double>::param_type(-25.f / 2, 25.f / 2));
            rotation += distribution(generator);
        }
        return rotation;
    }

    short which_map_is_chosen(PlayerObject &player_object){
        if(player_object.main_menu_event.map1) {std::cout << "MAP1\n"; return 1; }
        if(player_object.main_menu_event.map2) {std::cout << "MAP2\n"; return 2; }
        if(player_object.main_menu_event.map3) {std::cout << "MAP3\n"; return 3; }
        return 0;
    }

    short which_game_mode_is_chosen(PlayerObject &player_object){
        if(player_object.main_menu_event.death_match_game_mode) {std::cout << "DEATHMATCH GAME MODE\n"; return 1; }
        if(player_object.main_menu_event.takeover_game_mode) {std::cout << "TAKEOVER GAME MODE\n"; return 2; }
        return 0;
    }

    void copy_string_to_nickname(std::string &string, PlayerObject &object){
        if(string.empty()) {
            std::strcpy(object.nickname, "anonymous");
            return;
        }

        size_t size = string.size();
        int max_char_pos = NICKNAME_LENGTH - 1;

        for(int i = 0; i < NICKNAME_LENGTH; i++){
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

    /*void plant_bomb(PlayerObject &object, Player &player, sf::Sprite &plant_area, std::pair<bool, sf::Sprite> &bomb) {
        if (object.team == TEAM_T && object.player_state.has_bomb && !object.player_state.planted_bomb) {

            if (
                    sprite_collision(player.sprite, plant_area, false, false) &&
                    !object.player_state.walking &&
                    !object.player_state.running &&
                    !object.player_state.reloading &&
                    !object.player_state.shooting &&
                    !object.player_state.planted_bomb &&
                    object.hp > 0
                    ) {
                object.plant_or_defuse_timer++;
                player.plant_or_defuse_timer++;

                if (object.plant_or_defuse_timer >= PLANT_TIME) {
                    object.player_state.planted_bomb = true;
                    object.player_state.has_bomb = false;
                    player.planted_bomb = true;
                    player.has_bomb = false;
                    bomb.second.setPosition(player.sprite.getPosition());
                    bomb.first = BOMB_DROPPED;
                }
            } else {
                object.plant_or_defuse_timer = 0;
                player.plant_or_defuse_timer = 0;
            }
        }
    }

    void defuse_bomb(PlayerObject &object, Player &player, std::pair<bool, sf::Sprite> &bomb) {
        if (object.team == TEAM_CT) {

            if (
                    sprite_collision(player.sprite, bomb.second, false, false) &&
                    !object.player_state.walking &&
                    !object.player_state.running &&
                    !object.player_state.reloading &&
                    !object.player_state.shooting &&
                    !object.player_state.defused_bomb &&
                    object.hp > 0
                    ) {
                object.plant_or_defuse_timer++;
                player.plant_or_defuse_timer++;
                if (object.plant_or_defuse_timer >= DEFUSE_TIME) {
                    object.player_state.defused_bomb = true;
                    player.defused_bomb = true;
                }
            } else {
                object.plant_or_defuse_timer = 0;
                player.plant_or_defuse_timer = 0;
            }
        }
    }

    void drop_bomb(Player &player, PlayerObject &object, std::pair<bool, sf::Sprite> &bomb, Map &map) {
        player.has_bomb = false;
        object.player_state.has_bomb = false;

        bomb.first = BOMB_DROPPED;
        object.player_state.dropped_bomb = true;


        bomb.second.setPosition(map.calculate_3x3_non_wall_position(player.sprite.getPosition(),
                                                                    player.sprite.getRotation() - 90));
    }

    void move(Player &player, PlayerObject &object, PlayerEvent &player_event) {

        bool W = player_event.up_button_pressed;
        bool S = player_event.down_button_pressed;
        bool A = player_event.left_button_pressed;
        bool D = player_event.right_button_pressed;

        float movement_speed = 0;
        if (player_event.walk_silently_button_pressed && (W || S || A || D)) {
            movement_speed = WALKING_MOVEMENT_SPEED;

            object.player_state.walking = true;
            object.player_state.running = false;

            player.walking = true;
            player.running = false;
        } else if (W || S || A || D) {
            movement_speed = RUNNING_MOVEMENT_SPEED;
            object.player_state.running = true;
            object.player_state.walking = false;

            player.running = true;
            player.walking = false;
        } else {
            object.player_state.running = false;
            object.player_state.walking = false;

            player.running = false;
            player.walking = false;
        }

        sf::Vector2f movement = {0, 0};
        if (W) {
            movement.y -= 1;
        }
        if (S) {
            movement.y += 1;
        }
        if (A) {
            movement.x -= 1;
        }
        if (D) {
            movement.x += 1;
        }

        // Normalize movement vector
        float length = sqrt(movement.x * movement.x + movement.y * movement.y);
        if (length > 0) {
            movement /= length;
            object.pos_x += movement.x * movement_speed;
            object.pos_y += movement.y * movement_speed;
        }

        player.sprite.setPosition(object.pos_x, object.pos_y);

    }*/

    sf::Packet &operator<<(sf::Packet &packet, const PlayerEvent &player_event) {
        return packet
                << *(sf::Uint32 *) &player_event;
    }

    sf::Packet &operator>>(sf::Packet &packet, PlayerEvent &player_event) {
        return packet
                >> *(sf::Uint32 *) &player_event;
    }



    sf::Packet &operator<<(sf::Packet &packet, const PlayerObject &object) {
        return packet << object.id << object.nickname << object.hp << object.team
                      << object.kills << object.deaths
                      << object.mag_ammo << object.leftover_ammo
                      << object.pos_x << object.pos_y << object.rotation << object.tick
                      << *(uint16*)&object.player_state << *(uint8*)&object.main_menu_event << *(uint64*)&object.sync
                      << object.shoot_timer << object.plant_or_defuse_timer << object.reload_timer;
    }

    sf::Packet &operator>>(sf::Packet &packet, PlayerObject &object) {
        return packet >> object.id >> object.nickname >> object.hp >> object.team
                      >> object.kills >> object.deaths
                      >> object.mag_ammo >> object.leftover_ammo
                      >> object.pos_x >> object.pos_y >> object.rotation >> object.tick
                      >> *(uint16*)&object.player_state >> *(uint8*)&object.main_menu_event >> *(uint64*)&object.sync
                      >> object.shoot_timer >> object.plant_or_defuse_timer >> object.reload_timer;
    }

    sf::Packet &operator<<(sf::Packet &packet, const MissileObject &object) {
        return packet << object.id << object.life << object.player_who_shot_id << object.rotation_degree
                      << object.position_x << object.position_y << object.previous_position_x
                      << object.previous_position_y;
    }

    sf::Packet &operator>>(sf::Packet &packet, MissileObject &object) {
        return packet
        >> object.id
        >> object.life
        >> object.player_who_shot_id
        >> object.rotation_degree
        >> object.position_x
        >> object.position_y
        >> object.previous_position_x
        >> object.previous_position_y;
    }


    sf::Packet& operator << (sf::Packet& packet, const BombObject &object){
        return packet
                << *(uint32*) &object;
    }

    sf::Packet& operator >> (sf::Packet& packet, BombObject& object){
        return packet
                >> *(uint32*) &object;
    }


    uint64 generate_random_id() {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<uint64> distribution;
        return distribution(generator);
    }

}

