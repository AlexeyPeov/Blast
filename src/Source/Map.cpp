#include "../Headers/Map.h"
#include "../Headers/Levels.h"
#include "../Headers/RayCaster.h"

std::string current_dir() {
    return std::filesystem::current_path().string();
}

void Map::init_map_textures() {

    this->team1_player_texture.loadFromFile(current_dir() + "/textures/personStationary.png");
    this->team2_player_texture.loadFromFile(current_dir() + "/textures/team2_player_image.png");

    this->wall_texture_unbreakable.loadFromFile(current_dir() + "/textures/unbreakableBorder.png");
    this->floor_texture.loadFromFile(current_dir() + "/textures/floor_new.png");
    this->wall_texture_5.loadFromFile(current_dir() + "/textures/border5.png");
    this->wall_texture_4.loadFromFile(current_dir() + "/textures/border4.png");
    this->wall_texture_3.loadFromFile(current_dir() + "/textures/border3.png");
    this->wall_texture_2.loadFromFile(current_dir() + "/textures/border2.png");
    this->wall_texture_1.loadFromFile(current_dir() + "/textures/border1.png");
    this->dropped_ammo_texture.loadFromFile(current_dir() + "/textures/dropped_ammo.png");

    this->missile_texture.loadFromFile(current_dir() + "/textures/missle.png");

    this->explosion_texture.loadFromFile(current_dir() + "/textures/explosion.png");


    this->team1_player_sprite = sf::Sprite(team1_player_texture);
    this->team2_player_sprite = sf::Sprite(team2_player_texture);

    this->missile_sprite = sf::Sprite(missile_texture);

    this->dropped_ammo_sprite.setTexture(dropped_ammo_texture);
    config_sprite(dropped_ammo_sprite);
    this->explosion_sprite = sf::Sprite(explosion_texture);


    this->wall_sprite = sf::Sprite(wall_texture_5);
    this->unbreakable_wall_sprite = sf::Sprite(wall_texture_unbreakable);
    this->floor_sprite = sf::Sprite(floor_texture);

    explosion_sprite.setOrigin(40.f / 2.f, (float) explosion_sprite.getTexture()->getSize().y / 2.f);
}

void Map::init_map_sounds(){

    if (!gun_reload_buffer.loadFromFile(current_dir() + "/sounds/gun_reload.wav")) {
        std::cerr << "failed to load reload sound\n";
    }

    if (!single_shot_buffer.loadFromFile(current_dir() + "/sounds/shot.wav")) {
        std::cerr << "failed to load shot sound\n";
    }

    if (!walking_buffer.loadFromFile(current_dir() + "/sounds/walking_sound.wav")) {
        std::cerr << "failed to load walking sound\n";
    }

    gun_reload_sound.setBuffer(gun_reload_buffer);
    single_shot_sound.setBuffer(single_shot_buffer);
    walking_sound.setBuffer(walking_buffer);

    gun_reload_sound.setVolume(60.f);

    walking_sound.setLoop(true);
}

void Map::init_walls(short level) {

    available_dm_spawn_positions.clear();
    walls_for_collision_map.clear();
    walls_map.clear();
    dropped_ammo.clear();


    int *arr;
    if (level == 1) {
        arr = &level_1[0];
        width = level_1_width;
        height = level_1_height;
    }
    else if (level == 2) { arr = &level_2[0]; width = level_2_width; height = level_2_height; }
    else if (level == 3) { arr = &dust_3[0];  width = dust_3_width; height = dust_3_height; }

    unbreakable_walls_texture.clear(sf::Color::Transparent);
    floors_texture.clear(sf::Color::Transparent);

    unbreakable_walls_texture.create(dust_3_width * 40, dust_3_height * 40);
    floors_texture.create(dust_3_width * 40, dust_3_height * 40);

    unbreakable_walls_texture.clear(sf::Color::Transparent);
    floors_texture.clear(sf::Color::Transparent);


    for (int position = 0; position < (width * height); position++) {

        Wall wall;

        int x = ((position % width) * 40) + 20;
        int y = ((position / width) * 40) + 20;

        if (arr[position] == UNBREAKABLE_WALL) {
            wall = {.sprite = unbreakable_wall_sprite, .hp = 99999999};
            wall.sprite.setPosition(x, y);
            config_sprite(wall.sprite);
            walls_for_collision_map[sf::Vector2f(x, y)] = wall;
            unbreakable_walls_texture.draw(wall.sprite);
        } else if (arr[position] == WALL) {
            wall = {.sprite = wall_sprite, .hp = 5};
            wall.sprite.setPosition(x, y);
            config_sprite(wall.sprite);
            walls_for_collision_map[sf::Vector2f(x, y)] = wall;
            walls_map[sf::Vector2f(x, y)] = wall;
            floor_sprite.setPosition(x, y);
            floor_sprite.setOrigin(floor_sprite.getTexture()->getSize().x / 2,
                                   floor_sprite.getTexture()->getSize().y / 2);
            floors_texture.draw(floor_sprite);
        } else if (arr[position] == FLOOR) {
            available_dm_spawn_positions.emplace_back(x,y);
            floor_sprite.setPosition(x, y);
            floor_sprite.setOrigin(floor_sprite.getTexture()->getSize().x / 2,
                                   floor_sprite.getTexture()->getSize().y / 2);
            floors_texture.draw(floor_sprite);
        }
    }
    unbreakable_walls_texture.display();
    floors_texture.display();

    unbreakable_walls_sprite.setTexture(unbreakable_walls_texture.getTexture());
    floors_sprite.setTexture(floors_texture.getTexture());
    floors_sprite.setColor(sf::Color(255,255,255,50));
    //std::cout << unbreakable_walls_and_floors_sprite.getPosition().x << " " <<  unbreakable_walls_and_floors_sprite.getPosition().y << "\n";
    //unbreakable_walls_and_floors_sprite.setPosition(0.f, unbreakable_walls_and_floors_texture.getSize().y);
    //unbreakable_walls_and_floors_sprite.setScale(1.f, -1.f);


}

void Map::init_main_player(short team) {
    float movement_speed = 2;
    float rotation_degree = 0;
    int hp = 100;
    sf::Sprite player_spr;
    if(team == 1 ) {
        main_player = Player(team1_player_sprite, movement_speed, rotation_degree, hp, 0);
    } else {
        main_player = Player(team2_player_sprite, movement_speed, rotation_degree, hp, 0);
    }
    config_sprite(main_player.sprite);
    main_player.sprite.setPosition(random_non_wall_position());
}

Player Map::init_new_player(int id, float pos_x, float pos_y, short team) const {
    float movement_speed = 2;
    float rotation_degree = 0;
    int hp = 100;
    Player player;
    if(team == 1 ) {
        player = Player(team1_player_sprite, movement_speed, rotation_degree, hp, id);
    } else {
        player = Player(team2_player_sprite, movement_speed, rotation_degree, hp, id);
    }
    config_sprite(player.sprite);
    player.sprite.setPosition(pos_x, pos_y);
    return player;
}



void Map::init_missile(Player &player, Object &object) {
    single_shot_sound.play();
    int movement_speed = 40;
    float rotation_degree = object.rotation;

    missile_sprite.setRotation(rotation_degree);
    float xToRad = missile_sprite.getRotation() * M_PI / 180;
    float dx = 10 * sin(xToRad);
    float dy = 10 * cos(xToRad);

    missile_sprite.setPosition(object.pos_x + dx, object.pos_y - dy);
    Missile missile = Missile(missile_sprite, movement_speed, rotation_degree);
    missile.previousPosition = {object.pos_x, object.pos_y};
    missile.player_who_shot = &player;

    config_sprite(missile_sprite);
    player.timeSinceLastShot = 0;
    player.mag_ammo--;
    missiles.push_back(missile);
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
            missile = missiles.erase(missile);
        }
    }
}

void Map::update_explosions() {
    for (auto explosion = explosions.begin(); explosion != explosions.end();) {
        explosion->update();
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

/*    void init_players(const Client &client) {

        int movement_speed = 3;
        int rotation_degree = 0;
        int hp = 100;
        for(auto player : client.objects){
            Player connected_player = Player(player_sprite, movement_speed, rotation_degree, hp);
            connected_player.sprite.setPosition(player.pos_x, player.pos_y);
            config_sprite(main_player.sprite);
            players.push_back(connected_player);
        }
    }*/


void Map::update_players(Client &client) {

    if (client.objects.size() < players.size()) {
        for (auto player = players.begin(); player != players.end();) {
            bool found = false;
            for (const auto &obj: client.objects) {
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

    for (auto &object: client.objects) {

        if (players.find(object.id) == players.end()) {
            players[object.id] = init_new_player(object.id, object.pos_x, object.pos_y, object.team);
        }
        if (object.hp > 0) {
            bool is_shooting = object::is_shooting(object);
            if (is_shooting) {
                //std::cout << "OTHER PLAYER SHOOTIN\n";
                init_missile(players[object.id], object);
                players[object.id].mag_ammo --;
            }
            players[object.id].hp = object.hp;
            players[object.id].sprite.setRotation(object.rotation);
            players[object.id].sprite.setPosition(object.pos_x, object.pos_y);
        }
    }
}

void Map::update_player(Client &client) {
    if (main_player.hp > 0) {
        if(object::is_shooting(client.object)){
            init_missile(main_player, client.object);
        }
        main_player.timeSinceLastShot += 1;
        if (main_player.if_wants_or_needs_to_reload()){
            gun_reload_sound.play();
        }
        if(main_player.reloading){
            main_player.reload_process++;
            main_player.reload();
        }
    }
}


/*    void main_player_move(sf::View &view, sf::RenderWindow &window, Client &client){

        if(main_player.id == 0){
            main_player.id = client.id;
        }

        if (main_player.hp > 0) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePos = window.mapPixelToCoords(mouse_position);

            view.setCenter(main_player.sprite.getPosition());
            window.setView(view);
            object::dont_move(client.object);
            object::dont_shoot(client.object);
            if (main_player.move(worldMousePos)) {
                object::move(client.object);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (init_missile(main_player)) {
                    object::shoot(client.object);
                }
            }
            client.object.pos_x = main_player.sprite.getPosition().x;
            client.object.pos_y = main_player.sprite.getPosition().y;
            client.object.rotation = main_player.sprite.getRotation();
        }
    }*/



void Map::main_player_move(sf::View &view, sf::RenderWindow &window, Client &client, bool gained_focus, float deltaTime) {

    if (main_player.id == 0) {
        main_player.id = client.id;
    }
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mouse_position);

    // Update the view gradually if the mouse is on the full top/bottom/left/right of the screen
    if (gained_focus && *gameState == GameState::IN_GAME) {
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
            view.setCenter(main_player.sprite.getPosition());
            window.setView(view);
        }
    }
    if (main_player.hp > 0) {
        if (gained_focus && *gameState == GameState::IN_GAME) {
            if (main_player.move(worldMousePos)){
                walking_sound.setVolume(60);
            } else {
                walking_sound.setVolume(0);
                walking_sound.play();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (main_player.can_shoot()) {
                    std::cout << "MAIN PLAYER INIT MISSILE\n";
                    object::shoot(client.object);
                }
            }
        }
        client.object.pos_x = main_player.sprite.getPosition().x;
        client.object.pos_y = main_player.sprite.getPosition().y;
        client.object.rotation = main_player.sprite.getRotation();
    }
    client.object.bullets = main_player.mag_ammo + main_player.leftover_ammo;
    client.object.hp = main_player.hp;
    client.object.kills = main_player.kills;
    client.object.deaths = main_player.deaths;
}


void Map::check_collision_walls_players() {

    // check collision on top, bottom, left, right to the square a player is standing on
    int x = main_player.sprite.getPosition().x;
    int y = main_player.sprite.getPosition().y;
    sf::Vector2f player_pos = sf::Vector2f((x / 40) * 40 + 20, (y / 40) * 40 + 20);

    sf::Vector2f theoretical_wall_pos[4] = {
            {player_pos.x, player_pos.y - 40},
            {player_pos.x, player_pos.y + 40},
            {player_pos.x - 40, player_pos.y},
            {player_pos.x + 40, player_pos.y},
    };

    int wall_can_move = false;
    int player_can_move = true;
    for(auto position : theoretical_wall_pos){
        if (walls_for_collision_map.count(position) > 0) {
            collision(walls_for_collision_map[position].sprite, main_player.sprite, wall_can_move, player_can_move);
        }
    }

   /* for (auto &wall: walls) {
        int wall_can_move = false;
        int player_can_move = true;
        for (auto &[id, player]: players) {
            collision(wall.sprite, player.sprite, wall_can_move, player_can_move);
        }
        collision(wall.sprite, main_player.sprite, wall_can_move, player_can_move);
    }
    for (auto &wall: unbreakable_walls) {
        int wall_can_move = false;
        int player_can_move = true;
        for (auto &[id, player]: players) {
            collision(wall.sprite, player.sprite, wall_can_move, player_can_move);
        }
        collision(wall.sprite, main_player.sprite, wall_can_move, player_can_move);
    }
    */






}

void Map::check_collision_player_players() {
    if (main_player.hp > 0) {
        for (auto &[player_id, other_player]: players) {
            int main_player_can_move = false;
            int other_player_can_move = false;
            collision(main_player.sprite, other_player.sprite, main_player_can_move, other_player_can_move);
        }
    }
}

void Map::check_collision_players_ammo(){

    auto it = dropped_ammo.begin();
    while (it != dropped_ammo.end()){
        bool picked_up = false;
        auto &[amount, ammo] = *it;
        for (auto &[id, player] : players){
            if(player.hp > 0 && player.sprite.getPosition() != ammo.getPosition()){
                if (collision(ammo, player.sprite, false, false)){
                    player.leftover_ammo += amount;
                    if (player.leftover_ammo > max_ammo){
                        player.leftover_ammo = max_ammo;
                    }
                    picked_up = true;
                    break;
                }
            }
        }

        if (collision(ammo, main_player.sprite, false, false)){
            if(main_player.hp > 0){
                main_player.leftover_ammo += amount;
                if (main_player.leftover_ammo > max_ammo){
                    main_player.leftover_ammo = max_ammo;
                }
                picked_up = true;
            }
        }


        if(!picked_up) {
            it++;
        } else {
            it = dropped_ammo.erase(it);
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


        /*// new
        float x = missile.sprite.getPosition().x;
        float y = missile.sprite.getPosition().y;
        sf::Vector2f theoretical_wall_pos = sf::Vector2f((((int)x) / 40) * 40 + 20, (((int)y) / 40) * 40 + 20);
        if (walls_for_collision_map.count(theoretical_wall_pos) > 0) {
            if(walls_map.count(theoretical_wall_pos) > 0){
                mn++;
                std::cout << "|mn" << mn << "," <<   x << "," << y << "|&wpos:" << theoretical_wall_pos.x << "," << theoretical_wall_pos.y << "|\n";
                walls_map[theoretical_wall_pos].hp--;
                update_wall(walls_map[theoretical_wall_pos]);
            }
            missile.life = false;
            init_explosion(missile);
        }

        for (auto &[id, player]: players) {
            if (missile.player_who_shot != &player && player.hp > 0) {
                if (collision(player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                    player.hp -= missile.damage;
                    missile.life = false;

                    if (player.hp <= 0) {
                        dropped_ammo_sprite.setPosition(player.sprite.getPosition());
                        dropped_ammo.emplace_back(player.bullets, dropped_ammo_sprite);
                        //std::cout << player.bullets <<  " bullets dropped\n";
                        if(missile.player_who_shot == &main_player)
                            main_player.kills++;
                    }

                    init_explosion(missile);
                }
            }
        }
        if (missile.player_who_shot != &main_player && main_player.hp > 0) {
            if (collision(main_player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                main_player.hp -= missile.damage;
                missile.life = false;

                if (main_player.hp <= 0) {
                    dropped_ammo_sprite.setPosition(main_player.sprite.getPosition());
                    dropped_ammo.emplace_back(main_player.bullets, dropped_ammo_sprite);
                    main_player.deaths++;
                }
                init_explosion(missile);
            }
        }*/



        for (int i = 1; i <= steps; ++i) {
            if (!missile.life) break;
            float t = static_cast<float>(i) / steps;

            missile.sprite.setPosition(missile.previousPosition + missileDisplacement * t);
            float x = missile.sprite.getPosition().x;
            float y = missile.sprite.getPosition().y;
            sf::Vector2f theoretical_wall_pos = sf::Vector2f((((int)x) / 40) * 40 + 20, (((int)y) / 40) * 40 + 20);
            if (walls_for_collision_map.count(theoretical_wall_pos) > 0) {
                if(walls_map.count(theoretical_wall_pos) > 0){
                    walls_map[theoretical_wall_pos].hp--;
                    update_wall(walls_map[theoretical_wall_pos]);
                }
                missile.life = false;
                init_explosion(missile);
            }

//            for (auto &wall: walls) {
//                if (collision(wall.sprite, missile.sprite, wall_can_move, missile_can_move)) {
//                    wall.hp -= 1;
//                    missile.life = false;
//                    init_explosion(missile);
//                    break;
//                }
//            }
//
//            for (auto &wall: unbreakable_walls) {
//                if (collision(wall.sprite, missile.sprite, wall_can_move, missile_can_move)) {
//                    wall.hp -= 1;
//                    missile.life = false;
//                    init_explosion(missile);
//                    break;
//                }
//            }

            for (auto &[id, player]: players) {
                if (missile.player_who_shot != &player && player.hp > 0) {
                    if (collision(player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                        std::cout << "pl_id:" << player.id << " misslePlId:" << missile.player_who_shot->id << "\n";
                        player.hp -= missile.damage;
                        missile.life = false;

                        if (player.hp <= 0) {
                            dropped_ammo_sprite.setPosition(player.sprite.getPosition());
                            dropped_ammo.emplace_back(player.leftover_ammo, dropped_ammo_sprite);
                            //std::cout << player.bullets <<  " bullets dropped\n";
                            if(missile.player_who_shot == &main_player)
                                main_player.kills++;
                        }

                        init_explosion(missile);
                        break;
                    }
                }
            }
            if (missile.player_who_shot != &main_player && main_player.hp > 0) {
                if (collision(main_player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                    main_player.hp -= missile.damage;
                    missile.life = false;

                    if (main_player.hp <= 0) {
                        dropped_ammo_sprite.setPosition(main_player.sprite.getPosition());
                        dropped_ammo.emplace_back(main_player.leftover_ammo, dropped_ammo_sprite);
                        main_player.deaths++;
                    }
                    init_explosion(missile);


                    break;
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
    for (const auto& [id, wall]: walls_map) {window.draw(wall.sprite);}
}



void Map::draw_missiles(sf::RenderWindow &window) {
    for (const auto &missile: missiles) window.draw(missile.sprite);
}

void Map::draw_dropped_ammo(sf::RenderWindow &window) {
    for (const auto &[amount, ammo] : dropped_ammo) window.draw(ammo);
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
