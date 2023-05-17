#include "../Headers/Player.h"

void Player::reload() {
    if(player_state.reloading){
        reload_sound.setPosition(sprite.getPosition().x, sprite.getPosition().y, 0.f);
    if(leftover_ammo > 0 && reloaded()){
        int how_much_to_insert = MAG_CAPACITY - mag_ammo;
        if(how_much_to_insert > leftover_ammo) {
            how_much_to_insert = leftover_ammo;
        }
        leftover_ammo -= how_much_to_insert;
        mag_ammo += how_much_to_insert;
        player_state.reloading = false;
    }
    reload_timer++;
    }
}

bool Player::can_shoot() {
    if (shoot_timer > SHOOT_DELAY && mag_ammo > 0 && !player_state.reloading) {
        return true;
    }
    return false;
}

void Player::verify_need_to_reload(bool reload_button_pressed) {
    if((mag_ammo == 0 || reload_button_pressed) && !player_state.reloading && mag_ammo != MAG_CAPACITY && leftover_ammo > 0){
        reload_timer = 0;
        player_state.reloading = true;
        reload_sound.play();
    }
}

bool Player::reloaded(){
    if(reload_timer >= RELOAD_TIME){
        reload_timer = 0;
        return true;
    }
    return false;
}


bool Player::movementKeysPressed(){
    return  sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

float Player::missile_rotation_based_on_movement() const {
    std::uniform_real_distribution<float> distribution(-135.f / 2, 135.f / 2);
    float rotation = sprite.getRotation();
    if(player_state.running){
        rotation += distribution(generator);
    } else if(player_state.walking){
        distribution.param(std::uniform_real_distribution<float>::param_type(-25.f / 2, 25.f / 2));
        rotation += distribution(generator);
    }
    return rotation;
}

void Player::drop_bomb(std::pair<bool, sf::Sprite> &bomb, sf::Vector2f position) {
    if(player_state.has_bomb){
        player_state.has_bomb = false;
        bomb.first = BOMB_DROPPED;
        bomb.second.setPosition(position);
    }
}

void Player::transfer_data_from(const PlayerObject& object){
    this->id = object.id;
    this->hp = object.hp;
    this->kills = object.kills;
    this->deaths = object.deaths;
    this->mag_ammo = object.mag_ammo;
    this->leftover_ammo = object.leftover_ammo;
    this->team = object.team;


    this->reload_timer = object.reload_timer;
    this->shoot_timer = object.shoot_timer;
    this->plant_or_defuse_timer = object.plant_or_defuse_timer;

    this->sprite.setPosition(object.pos_x, object.pos_y);
    this->sprite.setRotation(object.rotation);


    this->player_state = object.player_state;
}

void Player::transfer_data_to(PlayerObject& object){
    object.id = this->id;
    object.hp = this->hp;
    object.kills = this->kills;
    object.deaths = this->deaths;
    object.mag_ammo = this->mag_ammo;
    object.leftover_ammo = this->leftover_ammo;
    object.team = this->team;

    object.rotation = this->sprite.getRotation();

    object.reload_timer = this->reload_timer;
    object.shoot_timer = this->shoot_timer;
    object.plant_or_defuse_timer = this->plant_or_defuse_timer;

    object.pos_x = this->sprite.getPosition().x;
    object.pos_y = this->sprite.getPosition().y;
    object.player_state = this->player_state;
}

void Player::transfer_data_to(PlayerEvent &player_event, bool gained_focus) {
    player_event.up_button_pressed = false;
    player_event.down_button_pressed = false;
    player_event.left_button_pressed = false;
    player_event.right_button_pressed =false;
    player_event.shoot_button_pressed =false;
    player_event.walk_silently_button_pressed = false;
    player_event.event_button_pressed = false;
    player_event.reload_button_pressed = false;
    player_event.drop_button_pressed = false;
    if(gained_focus){
        player_event.up_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
        player_event.down_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
        player_event.left_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        player_event.right_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        player_event.shoot_button_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        player_event.walk_silently_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
        player_event.event_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        player_event.reload_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
        player_event.drop_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G);


        player_event.rotation_whole_number = (uint32)sprite.getRotation();
        player_event.rotation_decimal_number = static_cast<uint32>(((sprite.getRotation() - player_event.rotation_whole_number) * 1000));

        player_event.quit_button_pressed = false; // todo : implement
    }
}

void Player::get_inputs(PlayerEvent &player_event){
    player_event.up_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    player_event.down_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    player_event.left_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    player_event.right_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    player_event.shoot_button_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    player_event.walk_silently_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
    player_event.event_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    player_event.reload_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
    player_event.drop_button_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G);

    player_event.rotation_whole_number = (uint32)sprite.getRotation();
    player_event.rotation_decimal_number = (uint32)(sprite.getRotation() - player_event.rotation_whole_number) * 1000;
}

void Player::verify_and_assign_player_state(PlayerEvent &player_event){

    if(player_event.walk_silently_button_pressed){
        player_state.running = false;
        player_state.walking = true;
        movement_speed = WALKING_MOVEMENT_SPEED;
    } else {
        movement_speed = RUNNING_MOVEMENT_SPEED;
        player_state.running = true;
        player_state.walking = false;
    }

    if(player_event.up_button_pressed || player_event.down_button_pressed || player_event.left_button_pressed || player_event.right_button_pressed){
        move(player_event.up_button_pressed, player_event.down_button_pressed, player_event.left_button_pressed, player_event.right_button_pressed);
    } else {
        player_state.walking = false;
        player_state.running = false;
    }


    player_state.shooting = player_event.shoot_button_pressed && can_shoot();

    player_state.planting_bomb = (team == TEAM_T) && player_event.event_button_pressed;

    player_state.defusing_bomb = (team == TEAM_CT) && player_event.event_button_pressed;

    verify_need_to_reload(player_event.reload_button_pressed);

    player_state.dropping_bomb = (team == TEAM_T) && player_event.drop_button_pressed;

    float rotation_whole = player_event.rotation_whole_number;
    float rotation_decimal = (float)player_event.rotation_decimal_number / 1000.f;

    sprite.setRotation(rotation_whole + rotation_decimal);

}

void Player::plant_bomb(sf::Sprite &plant_area, std::pair<bool, sf::Sprite> &bomb, bool pressed_plant_button) {
    if(team == TEAM_T && player_state.has_bomb && !player_state.planted_bomb){
        if(
                pressed_plant_button &&
                sprite_collision(sprite, plant_area, false, false) &&
                !player_state.walking && !player_state.running && !player_state.reloading && !player_state.shooting && !player_state.planted_bomb && hp > 0
                ){
            plant_or_defuse_timer++;
            plant_animation.sprite.setPosition(sprite.getPosition());
            plant_animation.update();
            std::cout << "PLANT ANIM " << plant_animation.elapsedTime << " " << plant_animation.currentFrame << "\n";
            if(plant_or_defuse_timer >= PLANT_TIME){
                player_state.planted_bomb = true;
                player_state.dropping_bomb = true;
                player_state.has_bomb = false;
                plant_or_defuse_timer = 0;
                plant_animation.reset();
                bomb.first = BOMB_DROPPED;
                bomb.second.setPosition(sprite.getPosition());
                //std::cout << "PLANTED!!\n";
            }
        } else {
            plant_or_defuse_timer = 0;
            plant_animation.reset();
        }
    }
}

void Player::defuse_bomb(std::pair<bool, sf::Sprite> &bomb, bool pressed_defuse_button) {
    if(team == TEAM_CT){
        if(plant_or_defuse_timer != 0) {
            defuse_animation.sprite.setPosition(bomb.second.getPosition());
            defuse_animation.update();
        }
        if(
                pressed_defuse_button &&
                sprite_collision(sprite, bomb.second, false, false) &&
                !player_state.walking && !player_state.running && !player_state.reloading && !player_state.shooting && !player_state.defused_bomb && hp > 0
                ){
            plant_or_defuse_timer++;
            if(plant_or_defuse_timer >= DEFUSE_TIME){
                player_state.defused_bomb = true;
                plant_or_defuse_timer = 0;
                defuse_animation.reset();
            }
        } else {
            plant_or_defuse_timer = 0;
            defuse_animation.reset();
        }
    }
}


void Player::clear_bomb_related_flags(){
    player_state.has_bomb = false;
    player_state.planted_bomb = false;
    player_state.defused_bomb = false;
    plant_or_defuse_timer = 0;
}

void Player::freeze(){
    shoot_timer = 0;
    running_sound.pause();
}


void Player::rotate(sf::Vector2f &mouse_position){
    float angle =
            (atan2(mouse_position.y - this->sprite.getPosition().y,
                   mouse_position.x - this->sprite.getPosition().x
            ) * 180 / M_PI) + 90;
    this->sprite.setRotation(angle);
}
