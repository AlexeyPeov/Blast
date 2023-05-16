#include "../Headers/Map.h"



void Map::init_map_textures() {

    this->team1_player_texture.loadFromFile(working_dir() + "/textures/personStationary.png");
    this->team2_player_texture.loadFromFile(working_dir() + "/textures/team2_player_image.png");

    this->wall_texture_unbreakable.loadFromFile(working_dir() + "/textures/unbreakableBorder.png");
    this->floor_texture.loadFromFile(working_dir() + "/textures/floor_new.png");
    this->wall_texture_5.loadFromFile(working_dir() + "/textures/border5.png");
    this->wall_texture_4.loadFromFile(working_dir() + "/textures/border4.png");
    this->wall_texture_3.loadFromFile(working_dir() + "/textures/border3.png");
    this->wall_texture_2.loadFromFile(working_dir() + "/textures/border2.png");
    this->wall_texture_1.loadFromFile(working_dir() + "/textures/border1.png");
    this->dropped_ammo_texture.loadFromFile(working_dir() + "/textures/dropped_ammo.png");
    this->bomb_texture.loadFromFile(working_dir() + "/textures/bomb.png");
    this->a_site_texture.loadFromFile(working_dir() + "/textures/a_site.png");
    this->missile_texture.loadFromFile(working_dir() + "/textures/missle.png");

    this->plant_anim_texture.loadFromFile(working_dir() + "/textures/plant_anim.png");
    this->defuse_anim_texture.loadFromFile(working_dir() + "/textures/defuse_anim.png");


    this->explosion_texture.loadFromFile(working_dir() + "/textures/explosion.png");


    this->team1_player_sprite = sf::Sprite(team1_player_texture);
    this->team2_player_sprite = sf::Sprite(team2_player_texture);

    this->missile_sprite = sf::Sprite(missile_texture);
    center_sprite_origin(missile_sprite);
    this->a_site_sprite.setTexture(a_site_texture);
    center_sprite_origin(a_site_sprite);

    this->dropped_ammo_sprite.setTexture(dropped_ammo_texture);
    center_sprite_origin(dropped_ammo_sprite);
    this->explosion_sprite = sf::Sprite(explosion_texture);

    this->plant_anim_sprite = sf::Sprite(plant_anim_texture);
    this->defuse_anim_sprite = sf::Sprite(defuse_anim_texture);

    this->bomb_sprite.setTexture(bomb_texture);
    center_sprite_origin(bomb_sprite);

    bomb.first = true;
    bomb.second = bomb_sprite;

    this->wall_sprite = sf::Sprite(wall_texture_5);
    this->unbreakable_wall_sprite = sf::Sprite(wall_texture_unbreakable);
    this->floor_sprite = sf::Sprite(floor_texture);

    explosion_sprite.setOrigin(40.f / 2.f, (float) explosion_sprite.getTexture()->getSize().y / 2.f);
    defuse_anim_sprite.setOrigin(40.f / 2.f, (float) defuse_anim_sprite.getTexture()->getSize().y / 2.f);
    plant_anim_sprite.setOrigin(40.f / 2.f, (float) plant_anim_sprite.getTexture()->getSize().y / 2.f);


    plant_animation = Animation(plant_anim_sprite, 1200 / 30, 40, 30, PLANT_TIME / 30);
    defuse_animation = Animation(defuse_anim_sprite, 1200 / 30, 40, 30, DEFUSE_TIME / 30);

    shadowCastTexture.create(MAX_MAP_WIDTH * 40, MAX_MAP_HEIGHT * 40);

}

void Map::init_map_sounds() {

    if (!gun_reload_buffer.loadFromFile(working_dir() + "/sounds/gun_reload_mono.wav")) {
        std::cerr << "failed to load reload sound\n";
    }

    if (!single_shot_buffer.loadFromFile(working_dir() + "/sounds/shot_mono.wav")) {
        std::cerr << "failed to load shot sound\n";
    }

    if (!running_buffer.loadFromFile(working_dir() + "/sounds/walking_sound_mono.wav")) {
        std::cerr << "failed to load walking sound\n";
    }

    if (!bomb_tick_buffer.loadFromFile(working_dir() + "/sounds/bomb_tick.wav")) {
        std::cerr << "failed to load walking sound\n";
    }

    if (!bomb_explosion_buffer.loadFromFile(working_dir() + "/sounds/bomb_explosion.wav")) {
        std::cerr << "failed to load walking sound\n";
    }

    if (!bomb_planted_buffer.loadFromFile(working_dir() + "/sounds/bomb_planted.wav")) {
        std::cerr << "failed to load bomb planted sound\n";
    }

    if (!bomb_defused_buffer.loadFromFile(working_dir() + "/sounds/bomb_defused.wav")) {
        std::cerr << "failed to load bomb_defused sound\n";
    }

    if (!t_win_buffer.loadFromFile(working_dir() + "/sounds/t_win.wav")) {
        std::cerr << "failed to load t_win sound\n";
    }

    if (!ct_win_buffer.loadFromFile(working_dir() + "/sounds/ct_win.wav")) {
        std::cerr << "failed to load ct_win sound\n";
    }


    bomb_tick_sound.setBuffer(bomb_tick_buffer);
    bomb_explosion_sound.setBuffer(bomb_explosion_buffer);

    bomb_planted_sound.setBuffer(bomb_planted_buffer);
    bomb_defused_sound.setBuffer(bomb_defused_buffer);

    t_win_sound.setBuffer(t_win_buffer);
    ct_win_sound.setBuffer(ct_win_buffer);

    bomb_planted_sound.setVolume(20);
    bomb_defused_sound.setVolume(20);
    t_win_sound.setVolume(20);
    ct_win_sound.setVolume(20);


    bomb_tick_sound.setVolume(70);
    bomb_tick_sound.setMinDistance(40.f);
    bomb_tick_sound.setAttenuation(1.f);

    bomb_explosion_sound.setVolume(60);
    bomb_explosion_sound.setMinDistance(15.f);
    bomb_explosion_sound.setAttenuation(1.f);

}

void Map::init_walls(short level) {

    available_dm_spawn_positions.clear();
    walls_for_collision_map.clear();
    walls_map.clear();
    dropped_ammo.clear();

    map_level = level;

    const int *arr;
    if (level == 1) {
        arr = &level_1[0];
        width = level_1_width;
        height = level_1_height;
    } else if (level == 2) {
        arr = &level_2[0];
        width = level_2_width;
        height = level_2_height;
    }
    else if (level == 3) {
        arr = &dust_3_a[0];
        width = dust_3_a_width;
        height = dust_3_a_height;
    }

    unbreakable_walls_texture.clear(sf::Color::Transparent);
    floors_texture.clear(sf::Color::Transparent);

    unbreakable_walls_texture.create(dust_3_width * 40, dust_3_height * 40);
    floors_texture.create(dust_3_width * 40, dust_3_height * 40);

    unbreakable_walls_texture.clear(sf::Color::Transparent);
    floors_texture.clear(sf::Color::Transparent);

    sf::Vector2f a_site_pos = {860, 340};

    for (int position = 0; position < (width * height); position++) {

        Wall wall;

        int x = ((position % width) * 40) + 20;
        int y = ((position / width) * 40) + 20;

        if (arr[position] == UNBREAKABLE_WALL) {
            wall = {.sprite = unbreakable_wall_sprite, .hp = 99999999};
            wall.sprite.setPosition(x, y);
            center_sprite_origin(wall.sprite);
            walls_for_collision_map[sf::Vector2f(x, y)] = wall;
            unbreakable_walls_texture.draw(wall.sprite);
        } else if (arr[position] == WALL) {
            wall = {.sprite = wall_sprite, .hp = 5};
            wall.sprite.setPosition(x, y);
            center_sprite_origin(wall.sprite);
            walls_for_collision_map[sf::Vector2f(x, y)] = wall;
            walls_map[sf::Vector2f(x, y)] = wall;
            floor_sprite.setPosition(x, y);
            floor_sprite.setOrigin(floor_sprite.getTexture()->getSize().x / 2,
                                   floor_sprite.getTexture()->getSize().y / 2);
            floors_texture.draw(floor_sprite);
        } else if (arr[position] == FLOOR) {
            available_dm_spawn_positions.emplace_back(x, y);
            floor_sprite.setPosition(x, y);
            floor_sprite.setOrigin(floor_sprite.getTexture()->getSize().x / 2,
                                   floor_sprite.getTexture()->getSize().y / 2);
            floors_texture.draw(floor_sprite);
        }
    }
    a_site_sprite.setPosition(a_site_pos);
    floors_texture.draw(a_site_sprite);
    unbreakable_walls_texture.display();
    floors_texture.display();

    unbreakable_walls_sprite.setTexture(unbreakable_walls_texture.getTexture());
    floors_sprite.setTexture(floors_texture.getTexture());
    floors_sprite.setColor(sf::Color(255, 255, 255, 50));
    //std::cout << unbreakable_walls_and_floors_sprite.getPosition().x << " " <<  unbreakable_walls_and_floors_sprite.getPosition().y << "\n";
    //unbreakable_walls_and_floors_sprite.setPosition(0.f, unbreakable_walls_and_floors_texture.getSize().y);
    //unbreakable_walls_and_floors_sprite.setScale(1.f, -1.f);


}

/*void Map::init_main_player(short team) {
    float movement_speed = WALKING_MOVEMENT_SPEED;
    float rotation_degree = 0;
    int hp = 100;
    sf::Sprite player_spr;
    if (team == 1) {
        main_player = Player(team1_player_sprite, movement_speed, rotation_degree, hp, 0);
    } else {
        main_player = Player(team2_player_sprite, movement_speed, rotation_degree, hp, 0);
    }
    center_sprite_origin(main_player.sprite);
    main_player.sprite.setPosition(random_non_wall_position());

    main_player.single_shot_sound.setBuffer(single_shot_buffer);
    main_player.running_sound.setBuffer(running_buffer);
    main_player.reload_sound.setBuffer(gun_reload_buffer);


    main_player.reload_sound.setVolume(60.f);

    main_player.running_sound.setLoop(true);
    main_player.running_sound.setMinDistance(15.f);
    main_player.running_sound.setAttenuation(1.f);


    main_player.reload_sound.setMinDistance(5.f);
    main_player.reload_sound.setAttenuation(2.f);

    main_player.single_shot_sound.setMinDistance(1.f);
    main_player.single_shot_sound.setAttenuation(20.f);


//    main_player.reload_sound.setVolume(0);
//    main_player.single_shot_sound.setVolume(0);
}*/

Player Map::init_new_player(uint64_t id, float pos_x, float pos_y, uint8 team) const {
    float movement_speed = WALKING_MOVEMENT_SPEED;
    float rotation_degree = 0;
    int hp = 100;
    Player player;
    if (team == TEAM_T) {
        player = Player(team1_player_sprite, movement_speed, rotation_degree, hp, id, team);
    } else if (team == TEAM_CT) {
        player = Player(team2_player_sprite, movement_speed, rotation_degree, hp, id, team);
    } else {
        std::cerr << "NO TEAM NO GAME, FUCK OFF\n";
        exit(-1);
    }
    center_sprite_origin(player.sprite);
    player.sprite.setPosition(pos_x, pos_y);

    player.single_shot_sound.setBuffer(single_shot_buffer);
    player.running_sound.setBuffer(running_buffer);
    player.reload_sound.setBuffer(gun_reload_buffer);


    player.reload_sound.setVolume(60.f);

    player.running_sound.setLoop(true);
    player.running_sound.setMinDistance(55.f);
    player.running_sound.setAttenuation(20.f);


    player.reload_sound.setMinDistance(45.f);
    player.reload_sound.setAttenuation(25.f);

    player.single_shot_sound.setMinDistance(400.f);
    player.single_shot_sound.setAttenuation(15.f);


    return player;
}


void Map::init_missile(Player &player) {
    static uint64 missile_id = 0;
    player.single_shot_sound.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y, 0.f);

    player.single_shot_sound.play();
    float rotation_degree = player.missile_rotation_based_on_movement();

    missile_sprite.setRotation(rotation_degree);
    float xToRad = rotation_degree * M_PI / 180;
    float dx = 10 * sin(xToRad);
    float dy = 10 * cos(xToRad);

    center_sprite_origin(missile_sprite);
    missile_sprite.setPosition(player.sprite.getPosition().x + dx, player.sprite.getPosition().y - dy);
    Missile missile = Missile(missile_sprite, MISSILE_MOVEMENT_SPEED, rotation_degree);
    missile.id = missile_id;
    missile.previousPosition = {player.sprite.getPosition()};
    missile.player_who_shot_id = player.id;
    player.shoot_timer = 0;
    player.mag_ammo--;
    missiles.push_back(missile);
    missile_id++;
}


void Map::init_explosion(Missile &missile) {
    Animation explosion = Animation(explosion_sprite, 680 / 17, 40, 17, 2);
    explosion.sprite.setPosition(missile.sprite.getPosition());
    explosions.push_back(explosion);
}


void Map::update_wall(Wall &wall) {
    if (wall.hp < 5) {
        if (wall.hp == 4) { wall.sprite.setTexture(wall_texture_4); }
        else if (wall.hp == 3) { wall.sprite.setTexture(wall_texture_3); }
        else if (wall.hp == 2) { wall.sprite.setTexture(wall_texture_2); }
        else if (wall.hp == 1) { wall.sprite.setTexture(wall_texture_1); }
        else if (wall.hp <= 0) {
            available_dm_spawn_positions.emplace_back(wall.sprite.getPosition());
            walls_for_collision_map.erase(wall.sprite.getPosition());
            walls_map.erase(wall.sprite.getPosition());
        }
    }
}

void Map::update_missile(Missile &missile) {
    double xToRad = missile.sprite.getRotation() * M_PI / 180;
    double dx = missile.movement_speed * sin(xToRad);
    double dy = missile.movement_speed * cos(xToRad);
    missile.sprite.setPosition(missile.sprite.getPosition().x + dx, missile.sprite.getPosition().y - dy);
}

void Map::update_missiles() {
    for (auto missile = missiles.begin(); missile != missiles.end();) {
        if (missile->life) {
            missile->previousPosition = missile->sprite.getPosition();
            update_missile(*missile);
            missile++;

        } else {
            init_explosion(*missile);
            missile = missiles.erase(missile);

        }
    }
}

void Map::update_and_draw_missiles(sf::RenderWindow &window) {
    for (auto missile = missiles.begin(); missile != missiles.end();) {
        if (missile->life) {
            missile->previousPosition = missile->sprite.getPosition();
            update_missile(*missile);
            window.draw(missile->sprite);
            missile++;

        } else {
            init_explosion(*missile);
            std::cout << "ERASED MISSILE - CL\n";
            missile = missiles.erase(missile);
        }
    }
}

void Map::update_explosions() {
    for (auto explosion = explosions.begin(); explosion != explosions.end();) {
        explosion->update();
        if (!explosion->finished) {
            explosion++;
        } else {
            explosion = explosions.erase(explosion);
        }

    }
}

void Map::update_and_draw_explosions(sf::RenderWindow &window) {
    for (auto explosion = explosions.begin(); explosion != explosions.end();) {
        explosion->update();
        window.draw(explosion->sprite);
        if (!explosion->finished) {
            /* if (explosion->currentFrame == 1){
                 for (auto& [id, player] : players) {
                     float distance = std::sqrt(std::pow(player.sprite.getPosition().x - explosion->sprite.getPosition().x, 2) +
                                                std::pow(player.sprite.getPosition().y - explosion->sprite.getPosition().y, 2));
                     if (distance <= 50) {
                         player.hp -= 25;
                     }
                 }

                 float distance = std::sqrt(std::pow(main_player.sprite.getPosition().x - explosion->sprite.getPosition().x, 2) +
                                            std::pow(main_player.sprite.getPosition().y - explosion->sprite.getPosition().y, 2));
                 if (distance <= 50) {
                     main_player.hp -= 25;
                 }
                 std::cout << main_player.hp << "\n";
             }*/
            explosion++;
        } else {
            explosion = explosions.erase(explosion);
        }

    }
}

/*void Map::update_bots() {

    for (auto &[id, player]: players) {
        if (player.hp > 0) {
            if (player.shooting) {
                //std::cout << "OTHER PLAYER SHOOTIN\n";
                init_missile(player);
                player.mag_ammo--;
            }
            if (player.if_wants_or_needs_to_reload()) {
                player.reload_sound.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y, 0);
                player.reload_sound.play();
            }

            if (player.planted_bomb) {
                bomb.first = true;
                bomb.second.setPosition(player.sprite.getPosition());
                bomb_planted = true;
                bomb_tick_sound.setPosition(bomb.second.getPosition().x, bomb.second.getPosition().y, 0.f);
                bomb_explosion_sound.setPosition(bomb.second.getPosition().x, bomb.second.getPosition().y, 0.f);
            }

            if (player.defused_bomb) {
                bomb_defused = true;
                main_player.defused_bomb = true;
            }

            if (player.reloading) {
                player.reload_sound.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y, 0);
            }

            if (player.wants_to_drop_bomb()) {
                bomb.first = true;
                bomb.second.setPosition(
                        calculate_3x3_non_wall_position({player.sprite.getPosition().x, player.sprite.getPosition().y},
                                                        player.sprite.getRotation() - 90));
            }

            if (player.running) {
                player.running_sound.setVolume(60);
                player.running_sound.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y, 0.f);
            } else {
                player.running_sound.setVolume(0);
                player.running_sound.play();
            }
            // todo : AI
//            players[object.id].team_t = (object.team == 1);
//            players[object.id].has_bomb = object::is_bomb_carrier(object);
//            players[object.id].sprite.setRotation(object.rotation);
//            players[object.id].sprite.setPosition(object.pos_x, object.pos_y);
        } else {
            if (player.has_bomb) {
                player.wants_to_drop_bomb();
                bomb.first = true;
                bomb.second.setPosition(
                        calculate_3x3_non_wall_position({player.sprite.getPosition().x, player.sprite.getPosition().y},
                                                        player.sprite.getRotation() - 90));
            }
        }

//        players[object.id].hp = object.hp;

    }
}*/

sf::Vector2f Map::calculate_3x3_non_wall_position(const sf::Vector2f &position, const float rotation) const {

    // rotaton is sprite.getRotation()
    //      +   +   +
    //      +  pos  +
    //      +   +   +
    sf::Vector2f current_pos = sf::Vector2f(((int) position.x / 40) * 40 + 20, ((int) position.y / 40) * 40 + 20);

    std::vector<sf::Vector2f> offsets = {

            {-40, -40},
            {-40, 0},
            {-40, 40},
            {40,  0},
            {0,   -40},
            {40,  -40},
            {0,   40},
            {40,  40}

    };

    std::sort(offsets.begin(), offsets.end(), [&](const sf::Vector2f &a, const sf::Vector2f &b) {

        float angle_a = std::atan2(a.y, a.x) - rotation * (M_PI / 180.0f);
        float angle_b = std::atan2(b.y, b.x) - rotation * (M_PI / 180.0f);

        angle_a = std::fmod(angle_a + 2 * M_PI, 2 * M_PI);
        angle_b = std::fmod(angle_b + 2 * M_PI, 2 * M_PI);

        return angle_a < angle_b;
    });

    for (const auto &offset: offsets) {
        sf::Vector2f pos = current_pos + offset;
        if (walls_for_collision_map.count(pos) == 0) {
            return pos;
        }
    }

    return position;

}

/*void Map::update_main_player() {
    main_player.handle_movement();
    if (main_player.hp > 0) {
        sf::Listener::setPosition(main_player.sprite.getPosition().x, main_player.sprite.getPosition().y, 0.f);
        if (main_player.shooting) {
            init_missile(main_player);
        }
        main_player.plant_bomb(a_site_sprite, bomb.second, main_player.shooting, plant_animation);
        main_player.defuse_bomb(bomb.second, main_player.shooting, defuse_animation);

        if (main_player.planted_bomb && main_player.has_bomb) {
            main_player.has_bomb = false;
            bomb.first = true;
            std::cout << "PLANTED MAIN PLAYER\n";
            this->bomb_planted = true;
            bomb_tick_sound.setPosition(bomb.second.getPosition().x, bomb.second.getPosition().y, 0.f);
            bomb_explosion_sound.setPosition(bomb.second.getPosition().x, bomb.second.getPosition().y, 0.f);
        }

        if (main_player.defused_bomb && !bomb_defused) {
            puts("MAIN PLAYER DEFUSED\n");
            bomb_defused = true;
        }

        if (main_player.wants_to_drop_bomb()) {
            main_player.has_bomb = false;
            bomb.first = true;
            bomb.second.setPosition(calculate_3x3_non_wall_position(main_player.sprite.getPosition(),
                                                                    main_player.sprite.getRotation() - 90));
        }
        main_player.shoot_timer += 1;
        if (main_player.if_wants_or_needs_to_reload()) {
            main_player.reload_sound.setPosition(main_player.sprite.getPosition().x, main_player.sprite.getPosition().y,
                                                 0.f);
            main_player.reload_sound.play();
        }
        if (main_player.reloading) {
            main_player.reload_sound.setPosition(main_player.sprite.getPosition().x, main_player.sprite.getPosition().y,
                                                 0.f);
            main_player.reload_timer++;
            main_player.reload();
        }
        main_player.single_shot_sound.setPosition(main_player.sprite.getPosition().x,
                                                  main_player.sprite.getPosition().y, 0);
    } else {
        if (main_player.has_bomb) {
            bomb.first = true;
            bomb.second.setPosition(calculate_3x3_non_wall_position(main_player.sprite.getPosition(),
                                                                    main_player.sprite.getRotation() - 90));
            main_player.has_bomb = false;
            std::cout << "bomb dropped, mainpl\n";
        }
    }
}*/

void Map::update_player(Player &player) {

    if (player.hp > 0) {

        if (player.player_state.shooting) {
            init_missile(player);
        }

        if (player.player_state.planting_bomb) {
            //check which team
            player.plant_bomb(a_site_sprite, bomb, plant_animation);
        }

        if (player.player_state.defusing_bomb) {
            //check which team
            player.defuse_bomb(bomb, defuse_animation);
        }

//        if(player.team == TEAM_T && !player.player_state.planting_bomb){
//            player.plant_or_defuse_timer = 0;
//        }
//        if(player.team == TEAM_CT && !player.player_state.defusing_bomb){
//            player.plant_or_defuse_timer = 0;
//        }

//        if(!player.player_state.planting_bomb || !player.player_state.defusing_bomb){
//                player.plant_or_defuse_timer = 0;
//        }


        if(player.player_state.planted_bomb){
            bomb_planted = true;
            bomb_tick_sound.setPosition(bomb.second.getPosition().x, bomb.second.getPosition().y, 0.f);
            bomb_explosion_sound.setPosition(bomb.second.getPosition().x, bomb.second.getPosition().y, 0.f);
        }

        if(player.player_state.defused_bomb){
            bomb_defused = true;
        }

        if (player.player_state.reloading) {
            player.reload();
        }


        if (player.player_state.dropping_bomb) {
            player.drop_bomb(bomb, calculate_3x3_non_wall_position(player.sprite.getPosition(), player.sprite.getRotation() - 90));
        }



        if (player.player_state.running) {
            player.running_sound.setVolume(60);
            player.running_sound.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y, 0.f);
        } else {
            player.running_sound.setVolume(0);
            player.running_sound.play();
        }

        player.shoot_timer += 1;

    } else {
        if (player.player_state.has_bomb) {
            player.drop_bomb(bomb, calculate_3x3_non_wall_position(player.sprite.getPosition(), player.sprite.getRotation() - 90));
            std::cout << "bomb dropped from dead player\n";
        }
    }
    std::cout << "BOMB POS AT UPDATE_PLAYER: " << player.id  << "HAS? " << player.player_state.has_bomb << " DROPPING? " << player.player_state.dropping_bomb << " pos: " << bomb.second.getPosition().x << " " << bomb.second.getPosition().y << "\n";

    PlayerState playerState = player.player_state;
    player.player_state = {0};
    player.player_state.has_bomb = playerState.has_bomb; // todo : make better
    //player.player_state.dropping_bomb = playerState.dropping_bomb; // todo : make better
    //player.player_state.reloading = playerState.reloading;
}


void Map::spawn_bomb(sf::Vector2f position) {
    bomb.first = true;
    bomb.second.setPosition(position);
}

void Map::check_collision_walls_players() {

    // check collision on top, bottom, left, right to the square a player is standing on
    int wall_can_move = false;
    int player_can_move = true;

    for(auto  &[id, player] : players){
        int x = player.sprite.getPosition().x;
        int y = player.sprite.getPosition().y;
        sf::Vector2f player_pos = sf::Vector2f((x / 40) * 40 + 20, (y / 40) * 40 + 20);

        sf::Vector2f theoretical_wall_pos[4] = {
                {player_pos.x,      player_pos.y - 40},
                {player_pos.x,      player_pos.y + 40},
                {player_pos.x - 40, player_pos.y},
                {player_pos.x + 40, player_pos.y},
        };
        for (auto position: theoretical_wall_pos) {
            if (walls_for_collision_map.count(position) > 0) {
                sprite_collision(walls_for_collision_map[position].sprite, player.sprite, wall_can_move,
                                 player_can_move);
            }
        }
    }
}

void Map::check_collision_walls_players_online() {

    // check collision on top, bottom, left, right to the square a player is standing on

    for (auto &[id, player]: players) {

        int x = player.sprite.getPosition().x;
        int y = player.sprite.getPosition().y;
        sf::Vector2f player_pos = sf::Vector2f((x / 40) * 40 + 20, (y / 40) * 40 + 20);

        sf::Vector2f theoretical_wall_pos[4] = {
                {player_pos.x,      player_pos.y - 40},
                {player_pos.x,      player_pos.y + 40},
                {player_pos.x - 40, player_pos.y},
                {player_pos.x + 40, player_pos.y},
        };

        int wall_can_move = false;
        int player_can_move = true;
        for (auto position: theoretical_wall_pos) {
            if (walls_for_collision_map.count(position) > 0) {
                sprite_collision(walls_for_collision_map[position].sprite, player.sprite, wall_can_move,
                                 player_can_move);
            }
        }
    }
}

void Map::check_collision_players() {

    int player_can_move = false;
    int other_player_can_move = false;

    for(auto player = players.begin(); player != players.end(); player++){
        if(player->second.hp > 0){
            for(auto other_player = std::next(player, 1); other_player != players.end(); other_player++){
                if(other_player->second.hp > 0){
                    sprite_collision(player->second.sprite, other_player->second.sprite, player_can_move, other_player_can_move);
                }
            }
        }
    }
}

void Map::check_collision_players_ammo() {

    auto pair_of_ammo_amount_and_ammo_sprite = dropped_ammo.begin();
    while (pair_of_ammo_amount_and_ammo_sprite != dropped_ammo.end()) {
        bool picked_up = false;
        auto &[amount, ammo] = *pair_of_ammo_amount_and_ammo_sprite;
        for (auto &[id, player]: players) {
            if (player.hp > 0 && player.sprite.getPosition() != ammo.getPosition()) {
                if (sprite_collision(ammo, player.sprite, false, false)) {
                    player.leftover_ammo += amount;
                    if (player.leftover_ammo > MAX_AMMO) {
                        player.leftover_ammo = MAX_AMMO;
                    }
                    picked_up = true;
                    break;
                }
            }
        }
        if (!picked_up) {
            pair_of_ammo_amount_and_ammo_sprite++;
        } else {
            pair_of_ammo_amount_and_ammo_sprite = dropped_ammo.erase(pair_of_ammo_amount_and_ammo_sprite);
        }
    }

}

void Map::check_collision_players_bomb() {
    for (auto &[id, player]: players) {
        if (player.hp > 0 && player.team == TEAM_T && bomb.first == BOMB_DROPPED && !bomb_planted) {
            if (sprite_collision(bomb.second, player.sprite, false, false)) {
                player.player_state.has_bomb = true;
                bomb.first = BOMB_PICKED_UP;
                break;
            }
        }
    }
}

void Map::check_collision_missiles_walls_players() {
    for (auto &missile: missiles) {
        sf::Vector2f missileDisplacement = missile.sprite.getPosition() - missile.previousPosition;
        float maxDisplacement = std::max(std::abs(missileDisplacement.x), std::abs(missileDisplacement.y));
        int steps = std::ceil(maxDisplacement);
        int wall_can_move = false;
        int missile_can_move = true;

        for (int i = 1; i <= steps; ++i) {
            if (!missile.life) break;
            float t = static_cast<float>(i) / steps;

            missile.sprite.setPosition(missile.previousPosition + missileDisplacement * t);
            float x = missile.sprite.getPosition().x;
            float y = missile.sprite.getPosition().y;
            sf::Vector2f theoretical_wall_pos = sf::Vector2f((((int) x) / 40) * 40 + 20, (((int) y) / 40) * 40 + 20);
            if (walls_for_collision_map.count(theoretical_wall_pos) > 0) {
                if (walls_map.count(theoretical_wall_pos) > 0) {
                    walls_map[theoretical_wall_pos].hp--;
                    update_wall(walls_map[theoretical_wall_pos]);
                }
                missile.life = false;
            }

            for (auto &[id, player]: players) {
                if (missile.player_who_shot_id != player.id && player.hp > 0) {
                    if (sprite_collision(player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                        player.hp -= missile.damage;
                        missile.life = false;

                        if (player.hp <= 0) {
                            dropped_ammo_sprite.setPosition(player.sprite.getPosition());
                            dropped_ammo.emplace_back(player.leftover_ammo, dropped_ammo_sprite);
                            //std::cout << player.bullets <<  " bullets dropped\n";
                            players[missile.player_who_shot_id].kills ++;
                            player.deaths++;
                        }

                        break;
                    }
                }
            }
        }
    }
}

void Map::draw_floors(sf::RenderWindow &window) const {
    sf::RenderStates states;
    states.blendMode = sf::BlendAlpha;
    window.draw(floors_sprite, states);
}

void Map::draw_walls(sf::RenderWindow &window) {
    window.draw(unbreakable_walls_sprite);
    for (const auto &[id, wall]: walls_map) { window.draw(wall.sprite); }
}

void Map::draw_missiles(sf::RenderWindow &window) {
    for (const auto &missile: missiles) window.draw(missile.sprite);
}

void Map::draw_dropped_ammo(sf::RenderWindow &window) {
    for (const auto &[amount, ammo]: dropped_ammo) window.draw(ammo);

    auto &[dropped, bomb_spr] = bomb;
    if (dropped) { window.draw(bomb_spr); }
}

void Map::draw_players(sf::RenderWindow &window) {
    for (const auto &[id, player]: players) {
        if (player.hp > 0) {
            window.draw(player.sprite);
        }
    }
}

void Map::draw_explosions(sf::RenderWindow &window) {
    for (const auto &explosion: explosions) window.draw(explosion.sprite);
}

void Map::draw_plant_defuse_animations(sf::RenderWindow &window) {
    if (plant_animation.elapsedTime > 0) {
        window.draw(plant_animation.sprite);
    }
    if (defuse_animation.elapsedTime > 0) {
        window.draw(defuse_animation.sprite);
    }
}

sf::Vector2f Map::random_non_wall_position() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    long duration = value.count();
    srand(duration);
    return available_dm_spawn_positions.at(rand() % available_dm_spawn_positions.size());

}

/*

std::vector<sf::Vector2f> Map::calculateFov() {
    std::vector<sf::Vector2f> fov;

    std::vector<sf::Rect<float>> walls_bounds;
    walls_bounds.reserve(walls.size());
    for(auto &wall : walls){
        walls_bounds.emplace_back(wall.sprite.getGlobalBounds());
    }

    // Cast rays in a circle around the player
    for (float angle = 0; angle < 360; angle += 2) {
        // Calculate the direction of the ray
        float dx = std::cos(angle * PI / 180.f);
        float dy = std::sin(angle * PI / 180.f);

        // March the ray until it hits a wall
        sf::Vector2f rayPos = main_player.sprite.getPosition();
        while (true) {
            // Check if the ray hit a wall
            bool hitWall = false;
            for (const auto& rect : walls_bounds) {

                if (rect.contains(rayPos)) {
                    hitWall = true;
                    break;
                }
            }

            if (hitWall) {
                // Add the intersection point to the FOV
                fov.push_back(rayPos);
                break;
            }

            // Move the ray forward
            rayPos.x += dx;
            rayPos.y += dy;
        }
    }

    return fov;
}*/

bool Map::team_t_alive() {
    bool has_players = false;
    for (auto &[id, object]: players) {
        if (object.team == TEAM_T) {
            has_players = true;
            //std::cout << "TEAM_T PLAYER " << id << " HP: " << object.hp << "\n";
            if (object.hp > 0) {
                return true;
            }
        }
    }
    if (!has_players) return true;

    return false;
}

bool Map::team_ct_alive() {
    bool has_players = false;
    for (auto &[id, object]: players) {
        if (object.team == TEAM_CT) {
            has_players = true;
            //std::cout << "TEAM_CT PLAYER " << id << " HP: " << object.hp << "\n";
            if (object.hp > 0) {
                return true;
            }
        }
    }
    if (!has_players) return true;
    return false;
}


//void Map::bomb_explode() {
//    sf::Sprite bomb_explosion = explosion_sprite;
//    bomb_explosion.setScale(3.5, 3.5);
//    Animation explosion = Animation(bomb_explosion, 680 / 17, 40, 17, 5);
//    explosion.sprite.setPosition(bomb.second.getPosition());
//
//    center_sprite_origin(missile_sprite);
//
//    bomb_explosion_sound.play();
//
//    for (int i = 0; i < 15; i++) { // 720
//        int angle = i % 360;
//        float xToRad = angle * M_PI / 180;
//        float dx = 10 * sin(xToRad);
//        float dy = 10 * cos(xToRad);
//        missile_sprite.setRotation(angle);
//        missile_sprite.setPosition(bomb.second.getPosition().x + dx, bomb.second.getPosition().y - dy);
//        Missile missile = Missile(missile_sprite, 40, angle);
//        missile.previousPosition = {bomb.second.getPosition().x, bomb.second.getPosition().y};
//        missiles.push_back(missile);
//    }
//    explosions.push_back(explosion);
//}

void Map::bomb_explode() {
    sf::Sprite bomb_explosion = explosion_sprite;
    bomb_explosion.setScale(4.5, 4.5);
    Animation explosion = Animation(bomb_explosion, 680 / 17, 40, 17, 5);
    explosion.sprite.setPosition(bomb.second.getPosition());

    center_sprite_origin(missile_sprite);

    bomb_explosion_sound.play();

    float max_damage = 200.0f;
    float damage_radius = 700.0f;
    for (auto &[id, player] : players) {
        float distance = std::hypot(player.sprite.getPosition().x - bomb.second.getPosition().x,
                                    player.sprite.getPosition().y - bomb.second.getPosition().y);
        if (distance <= damage_radius) {
            float damage = max_damage * (1.0f - distance / damage_radius);
            // apply damage to player
            if(damage > player.hp) damage = player.hp;
            player.hp -= damage;
        }
    }

    explosions.push_back(explosion);
}

void Map::reset_for_new_round() {
    bomb_planted = false;
    bomb_defused = false;
    bomb.first = false;
    init_walls(map_level);
}

void Map::update_online(std::vector<PlayerObject> &player_objects, std::vector<MissileObject> &missile_objects){
    // update players

    //check if objects < players
    //      erase disconected players
    if (player_objects.size() < players.size()) {
        for (auto player = players.begin(); player != players.end();) {
            bool found = false;
            for (const auto &obj: player_objects) {
                if (player->first == obj.id) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                player = players.erase(player);
            } else {
                player++;
            }
        }
    }

    // for player : players
    //      player.transfer_data_from(player_objects[player.id])
    //      update_player(player);
    for (auto &object: player_objects) {
        std::cout << "CLIENT, MAP, PLAYER_OBJECT, id = " << object.id << " PLANT TIMER: " << object.plant_or_defuse_timer << "\n";
        if (players.find(object.id) == players.end()) {
            players[object.id] = init_new_player(object.id, object.pos_x, object.pos_y, object.team);
        }
        if(players[object.id].player_state.has_bomb && !object.player_state.has_bomb && !bomb_planted){
            players[object.id].drop_bomb(
                    bomb, calculate_3x3_non_wall_position(players[object.id].sprite.getPosition(), players[object.id].sprite.getRotation() - 90));
        } // todo : THIS IS A DUMB FIX, PLEASE REVISIT, ALSO WORKS SHITTY, PLEASE
        players[object.id].transfer_data_from(object);

        update_player(players[object.id]);
    }
    missiles.clear(); // todo: this is bad, need to redo later

    for(auto &missile_object : missile_objects){
        Missile missile = Missile(missile_sprite, MISSILE_MOVEMENT_SPEED, 0.0);
        missile.transfer_data_from(missile_object);
        missiles.push_back(missile);
    }
}

void Map::update_and_draw_players(sf::RenderWindow &window, sf::Vector2f &mouse_position, bool gained_focus) {
    for (auto &[id, player]: players) {

        if(player.hp > 0) {
            if (id == main_player_id && gained_focus) {
                PlayerEvent player_event = {0};
                player.rotate(mouse_position);
                player.get_inputs(player_event);
                player.verify_and_assign_player_state(player_event);
                //std::cout << "CLIENT PLAYER PLANT TIMER BEFORE UPDATE: " << player.plant_or_defuse_timer << "\n";
            }

            update_player(player);
            //std::cout << "CLIENT PLAYER PLANT TIMER AFTER UPDATE: " << player.plant_or_defuse_timer << "\n";
            window.draw(player.sprite);
        }
    }
}

void Map::update_players(std::vector<std::pair<uint64, PlayerEvent>> &player_events){
    for(auto &[id, player_event] : player_events){
        if(players[id].hp > 0){
            players[id].verify_and_assign_player_state(player_event);
            std::cout << "SERVER UPDATE_PLAYERS PLAYER DROPS BOMB:  " << players[id].player_state.dropping_bomb << " HAS_BOMB? "
                      << players[id].player_state.has_bomb << "\n";
            update_player(players[id]);
            std::cout << "SERVER UPDATE_PLAYERS PLAYER DROPS BOMB AFTER UPDATE:  " << players[id].player_state.dropping_bomb << " HAS_BOMB? "
                      << players[id].player_state.has_bomb << "\n";
            //std::cout << "PLANTING AT SERVER UPDATE PLAYERS: " << players[id].plant_or_defuse_timer << "\n";
        }
    }
}

void Map::play_tick(std::vector<std::pair<uint64, PlayerEvent>> &player_events){
    update_players(player_events);
    update_missiles();
    update_explosions();

    check_collision_missiles_walls_players();
    check_collision_players();
    check_collision_players_ammo();
    check_collision_players_bomb();
    check_collision_walls_players();
}

void Map::play_tick_and_draw(sf::RenderWindow &window, sf::Vector2f mouse_position, bool gained_focus) {
    update_and_draw_players(window, mouse_position, gained_focus);
    update_and_draw_missiles(window);
    update_explosions();


    check_collision_missiles_walls_players();
    check_collision_players();
    check_collision_players_ammo();
    check_collision_players_bomb();
    check_collision_walls_players();
}
