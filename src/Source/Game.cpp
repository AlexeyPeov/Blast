#include "../Headers/Game.h"


Game::Game() : desktop(sf::VideoMode::getDesktopMode()),
               window(sf::VideoMode(700, 500), "Blast", sf::Style::Titlebar | sf::Style::Close){
    //sf::VideoMode(1600, 800), "Blast", sf::Style::Titlebar | sf::Style::Close
    //window(desktop, "Blast", sf::Style::Fullscreen),
    view = sf::View(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
    view.setCenter((sf::Vector2f)window.getPosition());
    //window.setView(view);
    window.setVerticalSyncEnabled(true);
    // Load the font and create the label
    font.loadFromFile(working_dir() + "/textures/DejaVuSans.ttf");
    map.gameState = &gameState;
    map.init_map_textures();
    mainMenu = MainMenu(font, videoMode, client, multiplayerAction, map, gameMode);
    map.init_map_sounds();
    takeover = Takeover(map);

    if (!shader.loadFromFile(working_dir() + "/shaders/invert_colors.frag", sf::Shader::Fragment)) {
        std::cerr << "Failed to load shader\n";
    }

}

Game::~Game(){
    server_thread.join();
}

void Game::run() {
    auto frame_duration = std::chrono::milliseconds(1000 / 60);

    while (is_running) {

        if (mainMenu.menuState == MenuState::QUIT) {
            is_running = false;
        }
        if (gameState == GameState::MAIN_MENU) {
            if (view.getSize().x < window.getSize().x) {
                view.setSize(window.getSize().x, window.getSize().y);
                window.setView(view);
            }
        }
        if (gameState == GameState::IN_GAME) {
            if (view.getSize().x >= window.getSize().x) {
                view.setSize(viewSize.x, viewSize.y);
                window.setView(view);
            }
        }

        if (videoMode != VideoMode::UNCHANGED) {

            if (videoMode == VideoMode::FULLSCREEN) {
                window.create(desktop, "Blast", sf::Style::Fullscreen);
            } else if (videoMode == VideoMode::_1600x800) {
                window.create(sf::VideoMode(1600, 800), "Blast",
                              sf::Style::Titlebar | sf::Style::Close);
            } else if (videoMode == VideoMode::_1280x720) {
                window.create(sf::VideoMode(1280, 720), "Blast",
                              sf::Style::Titlebar | sf::Style::Close);
            }
            window.setVerticalSyncEnabled(true);
//                if(gameState == GameState::MAIN_MENU){
//                    view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
//                } else {
//                    view = sf::View(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
//                }
            if (gameState == GameState::MAIN_MENU) {
                if (view.getSize().x < window.getSize().x) {
                    view.setSize(window.getSize().x, window.getSize().y);
                }
            }
            if (gameState == GameState::IN_GAME || gameState == GameState::IN_GAME_PAUSE) {
                view.setSize(viewSize.x, viewSize.y);
            }
            window.setView(view);
            videoMode = VideoMode::UNCHANGED;
        }
        if (multiplayerAction != MultiplayerAction::NOTHING) {
            handleMultiplayerAction();
        }

        auto frame_start = std::chrono::steady_clock::now();
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if(client.active){
                    client.disconnect();
                    server.disconnect(server_thread);
                }
                if(server.active){
                    server.active = false;
                }
                is_running = false;
            }
            if (event.type == sf::Event::GainedFocus) {
                this->gained_focus = true;
            } else if (event.type == sf::Event::LostFocus) {
                this->gained_focus = false;
            }


            if (gameState == GameState::MAIN_MENU) {
                mainMenu.ipInput.handleEvent(event);
                mainMenu.portInput.handleEvent(event);
                mainMenu.nicknameInput.handleEvent(event);
            } else if (gameState == GameState::IN_GAME) {
                //handle ingame events
                handleEvents(event);
            }
            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Key::Home) {
//                    if (!client.active) {
//                        //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
//                        client.connect(client.getServerIp(), client.getServerPort());
//                    }
//                }
                if (event.key.code == sf::Keyboard::Key::RBracket) {
                    if (server.active) {
                        server.active = false;
                        server.disconnect(server_thread);
                        std::cout << "Stopping server..\n";
                    }
                    if (client.active) {
                        client.active = false;
                        client.disconnect();
                    }
                }
            }

        }

        window.clear();

//        if (server.active) {
//            server.receive_data();
//            server.play_tick();
//        }

        if (client.active) {
            client.receive_data();
            map.update_online(client.player_objects, client.missile_objects, client.bomb_object);
        }


        if (gameState == GameState::MAIN_MENU) {
            mainMenu.draw(window);
            if(mainMenu.menuState == MenuState::MAIN_MENU){
                if(server.active){
                    server.disconnect(server_thread);
                }
                if(client.active){
                    client.disconnect();
                }
            }
          //  std::cout << client.objects.size() << " " << map.players.size() << "\n";
        }
        else  {


            if (gameMode == GameMode::DEATH_MATCH) {
                death_match();
            } else if(gameMode == GameMode::TAKEOVER){
                takeover_game_mode(false);
                if(client.active){
                    takeover.sync_takeover(client.player_object.sync);
                }
            }

            map.play_tick_and_draw(window, window.mapPixelToCoords(sf::Mouse::getPosition(window)), gained_focus);
            map.draw_dropped_ammo(window);

            if(map.players[map.main_player_id].team == TEAM_CT) { map.draw_bomb(window); } // to make ct see bomb only when directly looking at it


            map.shadowCastTexture.clear(sf::Color::Transparent);
            RayCaster::castRays(map.shadowCastTexture, map.players[map.main_player_id].sprite.getPosition(),
                                map.walls_for_collision_map, map.players[map.main_player_id].sprite.getRotation() - 157.5);


            sf::Sprite visibleAreaSprite;
            visibleAreaSprite.setTexture(map.shadowCastTexture.getTexture());
            visibleAreaSprite.setScale(1.f, -1.f);
            visibleAreaSprite.setPosition(0.f, map.shadowCastTexture.getSize().y);

            shader.setUniform("texture", sf::Shader::CurrentTexture);
            window.draw(visibleAreaSprite, &shader);
            map.draw_floors(window);

            if(map.players[map.main_player_id].team == TEAM_T) { map.draw_bomb(window); }

            map.draw_walls(window);

            if (map.players[map.main_player_id].hp > 0) {
                window.draw(map.players[map.main_player_id].sprite);
            }
            map.draw_explosions(window);
            map.draw_plant_defuse_animations(window);


            //map.draw_missiles(window);
            //map.draw_explosions(window);

            //map.main_player.transfer_data_to(client.object);
            handleKeyBindings();

            handle_camera_movement(map.players[map.main_player_id].sprite.getPosition(), sf::Mouse::getPosition(window));


            if (gameState == GameState::IN_GAME_PAUSE) {
               // mainMenu.draw_in_pause(window, gameState);
            }
            draw_user_interface();

        }

        if (client.active) {
            map.players[map.main_player_id].transfer_data_to(client.player_event, gained_focus);
            client.send_data();
        }
//        if (server.active) {
//            server.send_data();
//        }


        window.display();

        auto frame_end = std::chrono::steady_clock::now();
        auto elapsed_time = frame_end - frame_start;
        if (elapsed_time < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed_time);
        }
    }
}

void Game::handleMultiplayerAction() {
    if (multiplayerAction == MultiplayerAction::NOTHING) return;


    if (multiplayerAction == MultiplayerAction::START_SERVER_AND_CLIENT) {
        if (!server.active) {
            server.set_listener();
            server_thread = std::thread(&Server::run, &server);
            //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
            client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toUint16());
        }
    }

    if (multiplayerAction == MultiplayerAction::START_CLIENT) {
        if (!client.active) {
            client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toUint16());
            //client.connect("127.0.0.1", 53000);
        }
    }

    if (multiplayerAction == MultiplayerAction::STOP_SERVER_AND_CLIENT) {
        if (server.active) {
            server.active = false;
            server.disconnect(server_thread);
            std::cout << "Stopping server..\n";
        }
        if (client.active) {
            client.active = false;
            client.disconnect();
        }
    }
    multiplayerAction = MultiplayerAction::NOTHING;
}

void Game::death_match() {

    static bool has_round_started = false;

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    static std::chrono::system_clock::time_point end;

    if (!has_round_started) {
        end = std::chrono::system_clock::now() + std::chrono::minutes(15);
        has_round_started = true;
    } else {

        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - end);

        if (elapsed.count() >= 15) {
            gameMode = GameMode::NONE;
        } else {


           /* if (map.main_player.hp <= 0) { // todo death match
                map.main_player.sprite.setPosition(map.random_non_wall_position());
                client.object.pos_x = map.main_player.sprite.getPosition().x;
                client.object.pos_y = map.main_player.sprite.getPosition().y;

                map.main_player.hp = 100;
                map.main_player.mag_ammo = MAG_CAPACITY;
                map.main_player.leftover_ammo = MAX_AMMO;
                client.object.hp = 100;
            }*/
        }

    }




    // 10 minutes

    // if player dies - respawns with full health on a random non - wall square, in 2 seconds

    // if player.hp < 0
    //      player.hp = 100
    //      player.position = random



    // each player has a score - how many times has he killed.
    //  if missile.died
    //      if hit player
    //          if player.hp < 0
    //              missile.player.score ++
    //      handled at void check_collision_missiles_walls_players();



    // if 10 minutes over - show leaderboard.
    // return
}

void Game::takeover_game_mode(bool online) {

    // todo: DONT FORGET TO SET CLIENT OBJECT TEAM TO OTHER TEAM IN MIDDLE GAME

    // t & ct
    // one of t has bomb
    // plant bomb at pos
    // bomb has 45 sec to blow up
    // ct has 6 sec to defuse
    // if t.all dead => ct win
    // if ct.all dead => t win

    // if time_out => ct.win

    // if bomb planted & ct.all dead => t.win
    // if bomb planted & t.all dead && bomb.blw => t.win
    // if bomb planted & t.all dead && bomb.defused => ct.win

    if(!takeover.game_over){
        takeover.update();
    }
}


void Game::handleEvents(sf::Event &e){
    if (e.type == sf::Event::MouseWheelScrolled)
    {
        if (e.mouseWheelScroll.delta < 0)
        {
            // onMouseScrollUp
            viewSize.x += 16 * 5;
            viewSize.y += 9 * 5;
        }
        else if (e.mouseWheelScroll.delta > 0)
        {
            // onMouseScrollDown
            viewSize.x -= 16 * 5;
            viewSize.y -= 9 * 5;
        }

        view.setSize(viewSize.x, viewSize.y);
        window.setView(view);
    }
}

void Game::handleKeyBindings() {
    // if main menu

    // if in game
    //tab

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        draw_score_menu();
    } else {

        // esc (pause)
        if(KeyBoard::keyClicked(sf::Keyboard::Escape)){
            if(gameState == GameState::IN_GAME || gameState == GameState::IN_GAME_OPTIONS){
                gameState = GameState::IN_GAME_PAUSE;
            }
            else if (gameState == GameState::IN_GAME_PAUSE){
                gameState = GameState::IN_GAME;
            }
        }

        if(gameState == GameState::IN_GAME_PAUSE){

            draw_in_game_pause_menu();

        } else if (gameState == GameState::IN_GAME_OPTIONS){

            draw_in_game_options_menu();

        }


    }
}

void Game::draw_team_won(int team){
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    sf::Text team_won_text;
    if(team == 0){
        team_won_text = sf::Text("Game draw", font);
    } else if(team == 1){
        team_won_text = sf::Text("Terrorists win", font);
    } else if(team == 2){
        team_won_text = sf::Text("Counter-terrorists win", font);
    }

    sf::Text replay_text = sf::Text("Replay", font);
    sf::Text exit_text = sf::Text("Exit to main menu", font);

    team_won_text.setScale(0.3, 0.3);
    replay_text.setScale(0.3, 0.3);
    exit_text.setScale(0.3, 0.3);

    sf::RectangleShape menu_rect_in_game = sf::RectangleShape(sf::Vector2f(300, 200));

    menu_rect_in_game.setFillColor(sf::Color(128, 128, 128, 200));
    menu_rect_in_game.setPosition(viewCenter);
    center_rect_origin(menu_rect_in_game);
    MainMenu::setUpText(team_won_text, 36, viewCenter.x - 50, viewCenter.y - 40, sf::Color::White);
    MainMenu::setUpText(replay_text, 36, viewCenter.x - 25, viewCenter.y - 20, sf::Color::White);
    MainMenu::setUpText(exit_text, 36, viewCenter.x - 50, viewCenter.y, sf::Color::White);

    if (Mouse::cursorCollidesWithItem(mousePos, replay_text.getGlobalBounds())) {
        replay_text.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            gameState = GameState::MAIN_MENU;
            client.player_event.ready_button_pressed = true;
            if(server.active){
                mainMenu.menuState = MenuState::HOST_OPTIONS;
            } else {
                mainMenu.menuState = MenuState::MULTIPLAYER_LOBBY;
            }

        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, exit_text.getGlobalBounds())) {
        exit_text.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            gameState = GameState::MAIN_MENU;
            mainMenu.menuState = MenuState::MAIN_MENU;
        }
    }
    window.draw(menu_rect_in_game);
    window.draw(team_won_text);
    window.draw(replay_text);
    window.draw(exit_text);
}

void Game::draw_score_menu(){
    sf::Vector2f viewCenter = window.getView().getCenter();

    std::map<int, sf::Text> team_1_text;
    std::map<int, sf::Text> team_2_text;

    float team_1_text_offset = -40;
    float team_2_text_offset = -40;


    for (auto &player: client.player_objects) {
        if (player.team == TEAM_T) {
            sf::Text text(std::string(player.nickname) + " " + std::to_string(player.kills) + " " + std::to_string(player.deaths) + " ", font);
            MainMenu::setUpText(text, 24, viewCenter.x - 120+ 50, viewCenter.y + team_1_text_offset, sf::Color::White);
            text.setScale(0.3, 0.3);
            team_1_text_offset += 20;
            team_1_text[player.id] = text;
        } else {
            sf::Text text(std::string(player.nickname) + " " + std::to_string(player.kills) + " " + std::to_string(player.deaths) + " ", font);
            MainMenu::setUpText(text, 24, viewCenter.x - 15+ 50, viewCenter.y + team_2_text_offset, sf::Color::White);
            text.setScale(0.3, 0.3);
            team_2_text_offset += 20;
            team_1_text[player.id] = text;
        }
    }

    sf::Text text1 = sf::Text("team_t", font);
    sf::Text text2 = sf::Text("team_ct", font);

    text1.setScale(0.3, 0.3);
    text2.setScale(0.3, 0.3);

    MainMenu::setUpText(text1, 36, viewCenter.x - 120 + 50, viewCenter.y - 60, sf::Color::White);
    MainMenu::setUpText(text2, 36, viewCenter.x - 15 + 50, viewCenter.y - 60, sf::Color::White);

    sf::RectangleShape score_rect = sf::RectangleShape(sf::Vector2f(300, 200));
    score_rect.setFillColor(sf::Color(128, 128, 128, 50));
    score_rect.setPosition(viewCenter);
    center_rect_origin(score_rect);

    window.draw(score_rect);
    window.draw(text1);
    window.draw(text2);

    for (auto &team1: team_1_text) {
        window.draw(team1.second);
    }
    for (auto &team2: team_2_text) {
        window.draw(team2.second);
    }
}

void Game::draw_user_interface(){
//    sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
//    sf::Vector2f viewCenter = (sf::Vector2f){window.getSize().x / 2.f, window.getSize().y / 2.f};
    sf::Vector2f viewCenter = window.getView().getCenter();

    sf::Vector2f low_left_corner = {viewCenter.x - (viewSize.x / 2) + 150,viewCenter.y + (viewSize.y / 2) - 50 };
    sf::Vector2f low_right_corner = {viewCenter.x + (viewSize.x / 2) - 150,viewCenter.y + (viewSize.y / 2) - 50 };
    sf::Vector2f middle_up_corner = {viewCenter.x - 30 ,viewCenter.y - (viewSize.y / 2) + 50 };

    // black half transparent low left corner half white text bold - hp
    // black half transparent low right corner half white text bold - ammo

    // circle radar?


    sf::RectangleShape hp_rect = sf::RectangleShape(sf::Vector2f(120, 50));
    hp_rect.setFillColor(sf::Color(5, 5, 5, 100));
    hp_rect.setPosition(low_left_corner);
    center_rect_origin(hp_rect);


    sf::RectangleShape ammo_rect = sf::RectangleShape(sf::Vector2f(120, 50));
    ammo_rect.setFillColor(sf::Color(5, 5, 5, 100));
    ammo_rect.setPosition(low_right_corner);
    center_rect_origin(ammo_rect);

    sf::Text hp_text( "+  " + std::to_string(map.players[map.main_player_id].hp), font);
    hp_text.setScale(0.3, 0.3);
    MainMenu::setUpText(hp_text, 60, low_left_corner.x - 20, low_left_corner.y - 12, sf::Color::White);

    sf::Text ammo_text( std::to_string(map.players[map.main_player_id].mag_ammo) + " /" + std::to_string(map.players[map.main_player_id].leftover_ammo), font);
    ammo_text.setScale(0.3, 0.3);
    MainMenu::setUpText(ammo_text, 60, low_right_corner.x - 20, low_right_corner.y - 12, sf::Color::White);


    if(gameMode == GameMode::TAKEOVER){

        sf::RectangleShape rounds_won_rect = sf::RectangleShape(sf::Vector2f(100, 60));
        sf::Text rounds_won_text( std::to_string(takeover.score_t) + " | " + std::to_string(takeover.score_ct), font);

        std::string minutes = std::to_string(takeover.round_seconds_left / 60);
        std::string seconds;
        if((takeover.round_seconds_left % 60) < 10) {seconds = "0"; }
        seconds += std::to_string(takeover.round_seconds_left % 60);

        sf::Text time_left_text( minutes + " : " + seconds, font);


        rounds_won_rect.setFillColor(sf::Color(5, 5, 5, 100));
        rounds_won_rect.setPosition(middle_up_corner);
        center_rect_origin(rounds_won_rect);

        rounds_won_text.setScale(0.3, 0.3);
        MainMenu::setUpText(rounds_won_text, 60, middle_up_corner.x - 25, middle_up_corner.y - 25, sf::Color::White);

        time_left_text.setScale(0.3, 0.3);
        MainMenu::setUpText(time_left_text, 60, middle_up_corner.x - 25, middle_up_corner.y, sf::Color::White);

        if(takeover.game_over){
            draw_team_won(takeover.team_won);
        }

        window.draw(rounds_won_rect);
        window.draw(rounds_won_text);
        window.draw(time_left_text);
    }

    window.draw(hp_rect);
    window.draw(ammo_rect);

    window.draw(hp_text);
    window.draw(ammo_text);
}

void Game::draw_in_game_pause_menu() {

    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    sf::Text text1_in_game = sf::Text("Continue", font);
    sf::Text text2_in_game = sf::Text("Options", font);
    sf::Text text3_in_game = sf::Text("Exit to main menu", font);

    text1_in_game.setScale(0.3, 0.3);
    text2_in_game.setScale(0.3, 0.3);
    text3_in_game.setScale(0.3, 0.3);

    sf::RectangleShape menu_rect_in_game = sf::RectangleShape(sf::Vector2f(150, 200));

    menu_rect_in_game.setFillColor(sf::Color(128, 128, 128, 120));
    menu_rect_in_game.setPosition(viewCenter);
    center_rect_origin(menu_rect_in_game);

    MainMenu::setUpText(text1_in_game, 36, viewCenter.x - 27, viewCenter.y - 40, sf::Color::White);
    MainMenu::setUpText(text2_in_game, 36, viewCenter.x - 25, viewCenter.y - 20, sf::Color::White);
    MainMenu::setUpText(text3_in_game, 36, viewCenter.x - 50, viewCenter.y, sf::Color::White);

    if (Mouse::cursorCollidesWithItem(mousePos, text1_in_game.getGlobalBounds())) {
        text1_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            gameState = GameState::IN_GAME;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text2_in_game.getGlobalBounds())) {
        text2_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            gameState = GameState::IN_GAME_OPTIONS;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3_in_game.getGlobalBounds())) {
        text3_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            multiplayerAction = MultiplayerAction::STOP_SERVER_AND_CLIENT;
            client.player_object = PlayerObject();
            client.disconnect();
            server.disconnect(server_thread);
            gameState = GameState::MAIN_MENU;
            mainMenu.menuState = MenuState::MAIN_MENU;
            takeover.reset();
        }
    }
    window.draw(menu_rect_in_game);
    window.draw(text1_in_game);
    window.draw(text2_in_game);
    window.draw(text3_in_game);
}

void Game::draw_in_game_options_menu() {
    //   setMainMenuItems(window);
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    sf::Text text1_in_game = sf::Text("Screen Resolution:", font);
    sf::Text text2_in_game = sf::Text("Fullscreen", font);
    sf::Text text3_in_game = sf::Text("1600x800", font);
    sf::Text text4_in_game = sf::Text("1280x720", font);
    sf::Text text5_in_game = sf::Text("Back", font);

    text1_in_game.setScale(0.3, 0.3);
    text2_in_game.setScale(0.3, 0.3);
    text3_in_game.setScale(0.3, 0.3);
    text4_in_game.setScale(0.3, 0.3);
    text5_in_game.setScale(0.3, 0.3);


    sf::RectangleShape menu_rect_in_game = sf::RectangleShape(sf::Vector2f(150, 200));
    menu_rect_in_game.setFillColor(sf::Color(128, 128, 128, 120));
    menu_rect_in_game.setPosition(viewCenter);
    center_rect_origin(menu_rect_in_game);

    MainMenu::setUpText(text1_in_game, 12 * 3, viewCenter.x - 50, viewCenter.y - 60, sf::Color::White);
    MainMenu::setUpText(text2_in_game, 12 * 3, viewCenter.x - 30, viewCenter.y - 40, sf::Color::White);
    MainMenu::setUpText(text3_in_game, 12 * 3, viewCenter.x - 30, viewCenter.y - 20, sf::Color::White);
    MainMenu::setUpText(text4_in_game, 12 * 3, viewCenter.x - 30, viewCenter.y, sf::Color::White);
    MainMenu::setUpText(text5_in_game, 12 * 3, viewCenter.x - 20, viewCenter.y + 20, sf::Color::White);


    if (Mouse::cursorCollidesWithItem(mousePos, text2_in_game.getGlobalBounds())) {
        text2_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //change to fullscreen
            videoMode = VideoMode::FULLSCREEN;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text3_in_game.getGlobalBounds())) {
        text3_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //change 1600x800
            videoMode = VideoMode::_1600x800;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text4_in_game.getGlobalBounds())) {
        text4_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            //change to 1280x720
            videoMode = VideoMode::_1280x720;
        }
    } else if (Mouse::cursorCollidesWithItem(mousePos, text5_in_game.getGlobalBounds())) {
        text5_in_game.setFillColor(sf::Color::Yellow);
        if (Mouse::clicked()) {
            gameState = GameState::IN_GAME_PAUSE;
        }
    }
    window.draw(menu_rect_in_game);
    window.draw(text1_in_game);
    window.draw(text2_in_game);
    window.draw(text3_in_game);
    window.draw(text4_in_game);
    window.draw(text5_in_game);
}

void Game::handle_camera_movement(sf::Vector2f player_position, sf::Vector2i mouse_position){


    // Update the view gradually if the mouse is on the full top/bottom/left/right of the screen

    if (gained_focus && gameState == GameState::IN_GAME) {

        static bool camera_centered = true; // todo : remake
        //check if player wants to center camera on self
        if(KeyBoard::keyClicked(sf::Keyboard::Key::F2)){
            if(camera_centered){
                camera_centered = false;
            } else {
                camera_centered = true;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || camera_centered) {
            view.setCenter(player_position);
            window.setView(view);
        } else {


            if (mouse_position.x <= 5) {
                view.move(-3.0f * CAMERA_SMOOTHNESS, 0);
                window.setView(view);
            } else if (mouse_position.x >= (window.getSize().x - 5)) {
                view.move(3.0f * CAMERA_SMOOTHNESS, 0);
                window.setView(view);
            } else if (mouse_position.y <= 5) {
                view.move(0, -3.0f * CAMERA_SMOOTHNESS);
                window.setView(view);
            } else if (mouse_position.y >= (window.getSize().y - 5)) {
                view.move(0, 3.0f * CAMERA_SMOOTHNESS);
                window.setView(view);
            }

        }
    }
}