#include "../Headers/Map.h"
#include "../Headers/Levels.h"

std::string current_dir() {
    return std::filesystem::current_path().string();
}

void Map::init_map_textures() {

    // release
//        this->player_texture.loadFromFile(current_dir() + "/textures/personStationary.png");
//
//        this->wall_texture_unbreakable.loadFromFile(current_dir() + "/textures/unbreakableBorder.png");
//        this->floor_texture.loadFromFile(current_dir() + "/textures/floor.png");
//        this->wall_texture_5.loadFromFile(current_dir() + "/textures/border5.png");
//        this->wall_texture_4.loadFromFile(current_dir() + "/textures/border4.png");
//        this->wall_texture_3.loadFromFile(current_dir() + "/textures/border3.png");
//        this->wall_texture_2.loadFromFile(current_dir() + "/textures/border2.png");
//        this->wall_texture_1.loadFromFile(current_dir() + "/textures/border1.png");
//
//        this->missile_texture.loadFromFile(current_dir() + "/textures/missle.png");
//
//        this->explosion_texture.loadFromFile(current_dir() + "/textures/explosion.png");

    //clion debug
    this->player_texture.loadFromFile(current_dir() + "/../textures/personStationary.png");

    this->wall_texture_unbreakable.loadFromFile(current_dir() + "/../textures/unbreakableBorder.png");
    this->floor_texture.loadFromFile(current_dir() + "/../textures/floor.png");
    this->wall_texture_5.loadFromFile(current_dir() + "/../textures/border5.png");
    this->wall_texture_4.loadFromFile(current_dir() + "/../textures/border4.png");
    this->wall_texture_3.loadFromFile(current_dir() + "/../textures/border3.png");
    this->wall_texture_2.loadFromFile(current_dir() + "/../textures/border2.png");
    this->wall_texture_1.loadFromFile(current_dir() + "/../textures/border1.png");

    this->missile_texture.loadFromFile(current_dir() + "/../textures/missle.png");

    this->explosion_texture.loadFromFile(current_dir() + "/../textures/explosion.png");


    this->player_sprite = sf::Sprite(player_texture);

    this->missile_sprite = sf::Sprite(missile_texture);

    this->explosion_sprite = sf::Sprite(explosion_texture);

    this->wall_sprite = sf::Sprite(wall_texture_5);
    this->unbreakable_wall_sprite = sf::Sprite(wall_texture_unbreakable);
    this->floor_sprite = sf::Sprite(floor_texture);

    explosion_sprite.setOrigin(40.f / 2.f, (float) explosion_sprite.getTexture()->getSize().y / 2.f);
}

void Map::init_walls(int level) {

    int *arr;

    if (level == 1) arr = &level_1[0];
    if (level == 2) arr = &level_2[0];
    if (level == 3) arr = &level_3[0];

    for (int position = 0; position < 800; position++) {

        Wall wall;

        int x = ((position % 40) * 40) + 20;
        int y = ((position / 40) * 40) + 20;


        if (arr[position] == UNBREAKABLE_WALL) {
            wall = {.sprite = unbreakable_wall_sprite, .hp = 99999999};
        } else if (arr[position] == WALL) {
            wall = {.sprite = wall_sprite, .hp = 5};
        } else {
            //add to vector of positions
            available_dm_spawn_positions.emplace_back(x,y);
        }

        if (arr[position] != FLOOR) {
            wall.sprite.setPosition(x, y);
            config_sprite(wall.sprite);
            walls.push_back(wall);
        } else {
            floor_sprite.setPosition(x, y);
            floor_sprite.setOrigin(floor_sprite.getTexture()->getSize().x / 2,
                                   floor_sprite.getTexture()->getSize().y / 2);
            floors.push_back(floor_sprite);
        }
    }

}

void Map::init_main_player() {
    float movement_speed = 2;
    int rotation_degree = 0;
    int hp = 100;
    main_player = Player(player_sprite, movement_speed, rotation_degree, hp, 0);
    config_sprite(main_player.sprite);
    main_player.sprite.setPosition(100, 100);
}

Player Map::init_new_player(int id, float pos_x, float pos_y) const {
    float movement_speed = 2;
    int rotation_degree = 0;
    int hp = 100;
    Player player = Player(player_sprite, movement_speed, rotation_degree, hp, id);
    config_sprite(player.sprite);
    player.sprite.setPosition(pos_x, pos_y);
    return player;
}

void Map::init_missile_as_connected_player(Player &player) {
    int movement_speed = 40;
    int rotation_degree = player.rotation_degree;
    Missile missile = Missile(missile_sprite, movement_speed, rotation_degree);
    missile.player_who_shot = &player;

    config_sprite(missile.sprite);

    missile.sprite.setRotation(player.sprite.getRotation());

    float xToRad = missile.sprite.getRotation() * M_PI / 180;
    float dx = 10 * sin(xToRad);
    float dy = 10 * cos(xToRad);
    missile.sprite.setPosition(player.sprite.getPosition().x + dx, player.sprite.getPosition().y - dy);

    player.timeSinceLastShot = 0;

    missiles.push_back(missile);
}

bool Map::init_missile_as_main_player(Player &player) {
    if (player.timeSinceLastShot > player.shootDelay) {
        int movement_speed = 40;
        int rotation_degree = player.rotation_degree;
        Missile missile = Missile(missile_sprite, movement_speed, rotation_degree);
        missile.player_who_shot = &player;

        config_sprite(missile.sprite);

        missile.sprite.setRotation(player.sprite.getRotation());

        float xToRad = missile.sprite.getRotation() * M_PI / 180;
        float dx = 10 * sin(xToRad);
        float dy = 10 * cos(xToRad);
        missile.sprite.setPosition(player.sprite.getPosition().x + dx, player.sprite.getPosition().y - dy);

        player.timeSinceLastShot = 0;

        missiles.push_back(missile);
        return true;
    }
    return false;
}

void Map::init_explosion(Missile &missile) {
    Animation explosion = Animation(explosion_sprite, 680 / 17, 40, 17, 2);
    explosion.sprite.setPosition(missile.sprite.getPosition());
    explosions.push_back(explosion);
}

void Map::update_walls() {
    for (auto wall = walls.begin(); wall != walls.end();) {

        if (wall->hp < 5) {
            if (wall->hp == 4) { wall->sprite.setTexture(wall_texture_4); }
            else if (wall->hp == 3) { wall->sprite.setTexture(wall_texture_3); }
            else if (wall->hp == 2) { wall->sprite.setTexture(wall_texture_2); }
            else if (wall->hp == 1) { wall->sprite.setTexture(wall_texture_1); }
        }
        if (wall->hp <= 0) {
            wall = walls.erase(wall);
        } else {
            wall++;
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
    //std::cout << "AMOUNT OF MISSILES: " << missiles.size() << "\n";
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

    /*
     * check if there are new connected players
     *
     *      if client.objects.size() > players.size()
     *          players[id] = client.object;
     *
     *
     *
     * check if there are players that disconnected
     *        if client.objects.size() < players.size()
     *              delete the player that is not present
     *
     *
     *
     * */
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
            players[object.id] = init_new_player(object.id, object.pos_x, object.pos_y);
        }
        if (object.hp > 0) {
            bool is_shooting = object::is_shooting(object);

            players[object.id].hp = object.hp;
            players[object.id].sprite.setRotation(object.rotation);
            players[object.id].sprite.setPosition(object.pos_x, object.pos_y);
            if (is_shooting) {
                std::cout << "OTHER PLAYER SHOOTIN\n";
                init_missile_as_connected_player(players[object.id]);
            }
        }
    }
}

void Map::update_player() {
    if (main_player.hp > 0) {
        main_player.timeSinceLastShot += 1;
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



void Map::main_player_move(sf::View &view, sf::RenderWindow &window, Client &client, bool gained_focus, bool not_in_game_pause, float deltaTime) {

    if (main_player.id == 0) {
        main_player.id = client.id;
    }
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mouse_position);

    // Update the view gradually if the mouse is on the full top/bottom/left/right of the screen
    if(gained_focus && not_in_game_pause){
        if (mouse_position.x <= 5) {
            view.move(-3.0f * deltaTime, 0);
            window.setView(view);
        } else if (mouse_position.x >= window.getSize().x - 5) {
            view.move(3.0f * deltaTime, 0);
            window.setView(view);
        } else if (mouse_position.y <= 5) {
            view.move(0, -3.0f * deltaTime);
            window.setView(view);
        } else if (mouse_position.y >= window.getSize().y - 5) {
            view.move(0, 3.0f * deltaTime);
            window.setView(view);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            view.setCenter(main_player.sprite.getPosition());
            window.setView(view);
        }
    }
    if (main_player.hp > 0) {
        if(gained_focus && not_in_game_pause) {
        main_player.move(worldMousePos);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (init_missile_as_main_player(main_player)) {
                    std::cout << "MAIN PLAYER INIT MISSILE\n";
                    object::shoot(client.object);
                }
            }
        }
        client.object.pos_x = main_player.sprite.getPosition().x;
        client.object.pos_y = main_player.sprite.getPosition().y;
        client.object.rotation = main_player.sprite.getRotation();
    }
    client.object.hp = main_player.hp;
}


void Map::check_collision_walls_players() {
    for (auto &wall: walls) {
        int wall_can_move = false;
        int player_can_move = true;
        for (auto &[id, player]: players) {
            collision(wall.sprite, player.sprite, wall_can_move, player_can_move);
        }
        collision(wall.sprite, main_player.sprite, wall_can_move, player_can_move);
    }
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

            for (auto &wall: walls) {
                if (collision(wall.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                    wall.hp -= 1;
                    missile.life = false;
                    init_explosion(missile);
                    break;
                }
            }
            for (auto &[id, player]: players) {
                if (missile.player_who_shot != &player && player.hp > 0) {
                    if (collision(player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                        player.hp -= 50;
                        missile.life = false;
                        init_explosion(missile);
                        break;
                    }
                }
            }
            if (missile.player_who_shot != &main_player && main_player.hp > 0) {
                if (collision(main_player.sprite, missile.sprite, wall_can_move, missile_can_move)) {
                    main_player.hp -= 50;
                    missile.life = false;
                    init_explosion(missile);

                    if(main_player.hp <= 0){
                        missile.player_who_shot->score++;
                    }

                    break;
                }
            }
        }
    }
}

void Map::draw_walls(sf::RenderWindow &window) {
    for (const auto &wall: walls) window.draw(wall.sprite);
}

void Map::draw_floors(sf::RenderWindow &window) {
    for (const auto &floor: floors) window.draw(floor);
}

void Map::draw_missiles(sf::RenderWindow &window) {
    for (const auto &missile: missiles) window.draw(missile.sprite);
}

void Map::draw_players(sf::RenderWindow &window) {
    for (const auto &[id, player]: players) {
        if (player.hp > 0) {
            window.draw(player.sprite);
        }
    }
    if (main_player.hp > 0) {
        window.draw(main_player.sprite);
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