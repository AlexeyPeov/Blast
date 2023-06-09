#include "../Headers/MainMenu.h"


void MainMenu::setUpText(sf::Text &text, int character_size, float pos_x, float pos_y, sf::Color color) {
    text.setCharacterSize(character_size);
    text.setFillColor(color);
    text.setPosition(pos_x, pos_y);
    //sf::FloatRect text1Bounds = text1.getLocalBounds();
    //text.setOrigin(text1Bounds.left + text1Bounds.width / 2.0f, text1Bounds.top + text1Bounds.height / 2.0f);
}

void MainMenu::drawMainMenu(sf::RenderWindow &window) {

    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1 = sf::Text("Play", font);
    text2 = sf::Text("Options", font);
    text3 = sf::Text("Quit", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    setUpText(text1, 36, viewCenter.x - 20 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 20 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 20 * 3, viewCenter.y, sf::Color::White);


    if (Mouse::cursorCollidesWithItem(mousePos, text1.getGlobalBounds())) {
        text1.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::CHOOSING_GAME_STATE;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::OPTIONS;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::QUIT;
        }
    }
    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
}

void MainMenu::drawChoosingGameStateMenu(sf::RenderWindow &window) {
    //   setMainMenuItems(window);
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1 = sf::Text("Singleplayer", font);
    text2 = sf::Text("Multiplayer", font);
    text3 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    setUpText(text1, 36, viewCenter.x - 40 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 35 * 3, viewCenter.y - 10 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 20 * 3, viewCenter.y + 20 * 3, sf::Color::White);


    if (Mouse::cursorCollidesWithItem(mousePos, text1.getGlobalBounds())) {
        text1.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::SINGLE_PLAYER;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::IS_HOST;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::MAIN_MENU;
        }
    }
    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
}

void MainMenu::drawSinglePlayerMenu(sf::RenderWindow &window) {

    static short map_chosen = 1;

    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1 = sf::Text("Choose map: ", font);
    text2 = sf::Text("Map 1", font);
    text3 = sf::Text("Map 2", font);
    text4 = sf::Text("Map 3", font);
    sf::Text playText = sf::Text("Play", font);
    text5 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);


    setUpText(text1, 36, viewCenter.x - 40 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 20 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 20 * 3, viewCenter.y, sf::Color::White);
    setUpText(text4, 36, viewCenter.x - 20 * 3, viewCenter.y + 20 * 3, sf::Color::White);
    setUpText(playText, 36, viewCenter.x - 20 * 3, viewCenter.y + 40 * 3, sf::Color::White);
    setUpText(text5, 36, viewCenter.x - 20 * 3, viewCenter.y + 60 * 3, sf::Color::White);

    if (Mouse::cursorCollidesWithItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            map_chosen = 1;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            map_chosen = 2;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            map_chosen = 3;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, playText.getGlobalBounds())) {
        playText.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //map->init_map_textures();
            map->init_walls(map_chosen);
            map->players[map->main_player_id] = map->init_new_player(client->id, client->player_object.pos_x, client->player_object.pos_y, client->player_object.team);
            menuState = MenuState::START;
            *map->gameState = GameState::IN_GAME;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::MAIN_MENU;
        }
    }

    if(map_chosen == 1){
        text2.setFillColor(sf::Color::Yellow);
    } else if (map_chosen == 2){
        text3.setFillColor(sf::Color::Yellow);
    } else if (map_chosen == 3){
        text4.setFillColor(sf::Color::Yellow);
    }


    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
    window.draw(playText);
    window.draw(text5);
}

void MainMenu::drawMultiplayerLobby(sf::RenderWindow &window) {
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();


    // table of players
    std::unordered_map<uint64, sf::Text> team_1_text;
    std::unordered_map<uint64, sf::Text> team_2_text;

    float team_1_text_offset = -40 * 3;
    float team_2_text_offset = -40 * 3;


    for (auto &player: client->player_objects) {
        if (player.team == TEAM_T) {
            sf::Text text(player.nickname, font);
            setUpText(text, 24, viewCenter.x - 60 * 3, viewCenter.y + team_1_text_offset, sf::Color::White);
            team_1_text_offset += 20 * 3;
            team_1_text[player.id] = text;
        } else {
            sf::Text text(player.nickname, font);
            setUpText(text, 24, viewCenter.x + 45 * 3, viewCenter.y + team_2_text_offset, sf::Color::White);
            team_2_text_offset += 20 * 3;
            team_1_text[player.id] = text;
        }
    }


    sf::Text chooseTeam("Choose team", font);

    text1 = sf::Text("team_t", font);
    text2 = sf::Text("team_ct", font);
    if(client->host){
        text4 = sf::Text("Start", font);
    } else {
        text4 = sf::Text("Ready", font);
    }
    text5 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setSize(sf::Vector2f(300 * 3 * 2, 200 * 3 * 2));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    hostRadioBox.setFillColor(sf::Color(240, 240, 240));
    hostRadioBox.setOutlineThickness(3);
    hostRadioBox.setOutlineColor(sf::Color(61, 61, 61));
    hostRadioBox.setPosition(viewCenter.x, viewCenter.y - 18 * 3);

    setUpText(chooseTeam, 36, viewCenter.x - 20 * 3, viewCenter.y - 80 * 3, sf::Color::White);
    setUpText(text1, 36, viewCenter.x - 60 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x + 45 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text4, 36, viewCenter.x, viewCenter.y + 60 * 3, sf::Color::White);
    setUpText(text5, 36, viewCenter.x, viewCenter.y + 80 * 3, sf::Color::White);

    // updating values
    bool everyone_ready = true;


    for (auto& obj : client->player_objects){
        if(!obj.main_menu_event.ready_to_play){
            everyone_ready = false;
            //std::cout << "EVERYONE READY FALSE\n";
            break;
        }
    }
    if(!client->player_object.main_menu_event.ready_to_play){
        everyone_ready = false;
        //std::cout << "EVERYONE READY FALSE\n";
    }

    if(everyone_ready){
        //std::cout << "EVERYONE READY TRUE\n";
    }


    // changing teams
    if (Mouse::cursorCollidesWithItem(mousePos, text1.getGlobalBounds())) {
        text1.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            client->player_event.change_team_to_t_button_pressed = true;
            if (team_2_text.find(client->player_object.id) != team_2_text.end()) {
                team_1_text[client->player_object.id] = team_2_text[client->player_object.id];
                team_2_text.erase(client->player_object.id);
            }
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            client->player_event.change_team_to_ct_button_pressed = true;
            if (team_1_text.find(client->player_object.id) != team_1_text.end()) {
                team_2_text[client->player_object.id] = team_1_text[client->player_object.id];
                team_1_text.erase(client->player_object.id);
            }
        }
    }else if (Mouse::cursorCollidesWithItem(mousePos, text4.getGlobalBounds())) {
        //if(host){
            text4.setFillColor(sf::Color::Yellow);
            if (Mouse::clicked()) {
                client->player_event.ready_button_pressed = true;
            }
      //  }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::IS_HOST;
            client->player_event = {0};
        }
    }

    if(!client->host){
        if(client->player_object.main_menu_event.ready_to_play){
            text4.setFillColor(sf::Color::Green);
        }
    } else {
        if(everyone_ready){
            text4.setFillColor(sf::Color::Green);
        } else if(client->player_object.main_menu_event.ready_to_play) {

            text4.setFillColor(sf::Color::Yellow);
        }
    }
    //std::cout << "CAN START: " << can_start << "\n";
    if(everyone_ready){
        short m = obj::which_map_is_chosen(client->player_object);
        short game_mode = obj::which_game_mode_is_chosen(client->player_object);

        if(m == 0){
            std::cerr << "MAP IS ZERO AT MAIN MENU\n";
            exit (-1);
        }
        map->init_walls(m);
        map->main_player_id = client->id;
        map->players[map->main_player_id] = map->init_new_player(client->id, client->player_object.pos_x, client->player_object.pos_y, client->player_object.team);
        menuState = MenuState::START;
        *map->gameState = GameState::IN_GAME;
        if(game_mode == 1){
            *gameMode = GameMode::DEATH_MATCH;
        } else if (game_mode == 2){
            *gameMode = GameMode::TAKEOVER;
        }
    }

    window.draw(menuRect);
    window.draw(chooseTeam);
    window.draw(text1);
    window.draw(text2);
    window.draw(text4);
    window.draw(text5);
    for (auto &team1: team_1_text) {
        window.draw(team1.second);
    }
    for (auto &team2: team_2_text) {
        window.draw(team2.second);
    }
}

void MainMenu::drawIsHostMenu(sf::RenderWindow &window) {
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();
    text1 = sf::Text("Are you host?", font);
    text2 = sf::Text("Host", font);
    text3 = sf::Text("Enter nickname:", font);
    text4 = sf::Text("Continue", font);
    text5 = sf::Text("Back", font);


    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    hostRadioBox.setFillColor(sf::Color(240, 240, 240));
    hostRadioBox.setOutlineThickness(1);
    hostRadioBox.setOutlineColor(sf::Color(61, 61, 61));

    setUpText(text1, 36, viewCenter.x - 40 * 3, viewCenter.y - 80 * 3, sf::Color::White);

    setUpText(text2, 36, viewCenter.x - 40 * 3, viewCenter.y - 50 * 3, sf::Color::White);
    hostRadioBox.setPosition(viewCenter.x, viewCenter.y - 48 * 3);

    setUpText(text3, 36, viewCenter.x - 50 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    nicknameInput.setPosition(viewCenter.x - 70 * 3, viewCenter.y + 10 * 3, 140 * 3, 20 * 3);

    setUpText(text4, 36, viewCenter.x - 30 * 3, viewCenter.y + 50 * 3, sf::Color::White);
    setUpText(text5, 36, viewCenter.x - 20 * 3, viewCenter.y + 80 * 3, sf::Color::White);


    if (Mouse::cursorCollidesWithItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            if (client->host) {
                //object::set_host(client->object);
                *this->multiplayerAction = MultiplayerAction::START_SERVER_AND_CLIENT;
                menuState = MenuState::HOST_OPTIONS;
            } else {
                menuState = MenuState::CLIENT;
            }
            obj::copy_string_to_nickname(nicknameInput.inputString, this->client->player_object);
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, hostRadioBox.getGlobalBounds())) {
        hostRadioBox.setOutlineColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            if(client->host){
                client->host = false;
            } else {
                client->host = true;
            }
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::CHOOSING_GAME_STATE;
            nicknameInput.clearInput();
        }
    }
    nicknameInput.update(window);

    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);

    window.draw(text3);
    nicknameInput.draw(window);

    window.draw(text4);
    window.draw(text5);

    if (client->host) {
        hostRadioBox.setFillColor(sf::Color(197, 255, 202));
    }
    window.draw(hostRadioBox);
}

void MainMenu::drawHostOptionsMenu(sf::RenderWindow &window)  {

    static short map_chosen = 1;
    static short game_mode_chosen = 1;

    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    sf::Text settings_text("Settings", font);

    text1 = sf::Text("Choose map: ", font);         sf::Text game_mode_text("game mode:", font);
    text2 = sf::Text("empty_large(40x40)", font);   sf::Text death_match_text("deathmatch", font);
    text3 = sf::Text("small(15x15)", font);         sf::Text takeover_text("takeover", font);
    text4 = sf::Text("dust_3(50x50)", font);
    sf::Text lobby_text = sf::Text("go to lobby", font);
    text5 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setSize(sf::Vector2f(300 * 3 * 2, 200 * 3 * 2));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    setUpText(settings_text, 36, viewCenter.x - 20 * 3, viewCenter.y - 80 * 3, sf::Color::White);
    setUpText(text1, 36, viewCenter.x - 110 * 3, viewCenter.y - 60 * 3, sf::Color::White);           setUpText(game_mode_text, 36, viewCenter.x + 60 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 110 * 3, viewCenter.y - 20 * 3, sf::Color::White);           setUpText(death_match_text, 36, viewCenter.x + 60 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 110 * 3, viewCenter.y, sf::Color::White);                    setUpText(takeover_text, 36, viewCenter.x + 60 * 3, viewCenter.y, sf::Color::White);
    setUpText(text4, 36, viewCenter.x - 110 * 3, viewCenter.y + 20 * 3, sf::Color::White);
    setUpText(lobby_text, 36, viewCenter.x - 40 * 3, viewCenter.y + 60 * 3, sf::Color::White);
    setUpText(text5, 36, viewCenter.x - 20 * 3, viewCenter.y + 80 * 3, sf::Color::White);

    if (Mouse::cursorCollidesWithItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            map_chosen = 1;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            map_chosen = 2;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            map_chosen = 3;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, death_match_text.getGlobalBounds())) {
        death_match_text.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            game_mode_chosen = 1;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, takeover_text.getGlobalBounds())) {
        takeover_text.setFillColor(sf::Color::Yellow);
        if(Mouse::clicked()){
            game_mode_chosen = 2;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, lobby_text.getGlobalBounds())) {
        lobby_text.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            menuState = MenuState::MULTIPLAYER_LOBBY;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            client->player_object.main_menu_event = {0};
            menuState = MenuState::MAIN_MENU;
        }
    }

    if(map_chosen == 1){
        text2.setFillColor(sf::Color::Yellow);
    } else if (map_chosen == 2){
        text3.setFillColor(sf::Color::Yellow);
    } else if (map_chosen == 3){
        text4.setFillColor(sf::Color::Yellow);
    }

    if(game_mode_chosen == 1){
        death_match_text.setFillColor(sf::Color::Yellow);
    } else if (game_mode_chosen == 2){
        takeover_text.setFillColor(sf::Color::Yellow);
    }

    client->player_event.chose_map_1_button_pressed = (map_chosen == 1);
    client->player_event.chose_map_2_button_pressed = (map_chosen == 2);
    client->player_event.chose_map_3_button_pressed = (map_chosen == 3);

    client->player_event.chose_deathmatch_button_pressed = (game_mode_chosen == 1);
    client->player_event.chose_takeover_button_pressed = (game_mode_chosen == 2);


    window.draw(menuRect);
                    window.draw(settings_text);
    window.draw(text1);     window.draw(game_mode_text);
    window.draw(text2);     window.draw(death_match_text);
    window.draw(text3);     window.draw(takeover_text);
    window.draw(text4);
                window.draw(lobby_text);
                window.draw(text5);
}

void MainMenu::drawClientMenu(sf::RenderWindow &window) {
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1 = sf::Text("Enter Server IP", font);
    text2 = sf::Text("Enter Port", font);
    text3 = sf::Text("Connect", font);
    text4 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    setUpText(text1, 36, viewCenter.x - 45 * 3, viewCenter.y - 80 * 3, sf::Color::White);
    ipInput.setPosition(viewCenter.x - 70 * 3, viewCenter.y - 50 * 3, 140 * 3, 20 * 3);

    setUpText(text2, 36, viewCenter.x - 35 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    portInput.setPosition(viewCenter.x - 70 * 3, viewCenter.y + 10 * 3, 140 * 3, 20 * 3);

    setUpText(text3, 36, viewCenter.x - 30 * 3, viewCenter.y + 40 * 3, sf::Color::White);
    setUpText(text4, 36, viewCenter.x - 20 * 3, viewCenter.y + 70 * 3, sf::Color::White);

    if (Mouse::cursorCollidesWithItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            *this->multiplayerAction = MultiplayerAction::START_CLIENT;
            menuState = MenuState::MULTIPLAYER_LOBBY;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            ipInput.clearInput();
            portInput.clearInput();
            menuState = MenuState::CHOOSING_GAME_STATE;
        }
    }
    ipInput.update(window);
    portInput.update(window);
    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
    ipInput.draw(window);
    portInput.draw(window);
}

void MainMenu::drawOptionsMenu(sf::RenderWindow &window) {
    //   setMainMenuItems(window);
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1 = sf::Text("Screen Resolution:", font);
    text2 = sf::Text("Fullscreen", font);
    text3 = sf::Text("1600x800", font);
    text4 = sf::Text("1280x720", font);
    text5 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_origin(menuRect);

    setUpText(text1, 12 * 3, viewCenter.x - 50 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text2, 12 * 3, viewCenter.x - 30 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text3, 12 * 3, viewCenter.x - 30 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text4, 12 * 3, viewCenter.x - 30 * 3, viewCenter.y, sf::Color::White);
    setUpText(text5, 12 * 3, viewCenter.x - 20 * 3, viewCenter.y + 20 * 3, sf::Color::White);


    if (Mouse::cursorCollidesWithItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //change to fullscreen
            *gameVideoMode = VideoMode::FULLSCREEN;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //change 1600x800
            *gameVideoMode = VideoMode::_1600x800;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //change to 1280x720
            *gameVideoMode = VideoMode::_1280x720;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            if (menuState == MenuState::OPTIONS) {
                menuState = MenuState::MAIN_MENU;
            }
        }
    }
    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
    window.draw(text5);
}

void MainMenu::draw(sf::RenderWindow &window) {
    if (menuState == MenuState::MAIN_MENU) {
        drawMainMenu(window);
    } else if (menuState == MenuState::CHOOSING_GAME_STATE) {
        drawChoosingGameStateMenu(window);
    } else if (menuState == MenuState::SINGLE_PLAYER) {
        drawSinglePlayerMenu(window);
    } else if (menuState == MenuState::IS_HOST) {
        drawIsHostMenu(window);
    } else if (menuState == MenuState::HOST_OPTIONS) {
        drawHostOptionsMenu(window);
    } else if (menuState == MenuState::CLIENT) {
        drawClientMenu(window);
    } else if (menuState == MenuState::MULTIPLAYER_LOBBY) {
        drawMultiplayerLobby(window);
    } else if (menuState == MenuState::OPTIONS) {
        drawOptionsMenu(window);
    }
}