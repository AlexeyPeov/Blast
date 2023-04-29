#include "../Headers/Game.h"


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
            }


//            if (mainMenu.menuState == MenuState::START) {
//                gameState = GameState::IN_GAME;
//              //  mainMenu.menuState = MenuState::IN_GAME;
//            }

            // Handle window fullscreen
            if (event.type == sf::Event::KeyPressed) {

//                if (event.key.code == sf::Keyboard::Escape) {
//                    if (gameState == GameState::IN_GAME) {
//                        gameState = GameState::IN_GAME_PAUSE;
//                      //  mainMenu.menuState = MenuState::IN_GAME_PAUSE;
//                    } else if (gameState == GameState::IN_GAME_PAUSE) {
//                        gameState = GameState::IN_GAME;
//                    }
//                }

                /*if (event.key.code == sf::Keyboard::Key::H) {
                    if(!server.active){
                        server.set_listener();
                        //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
                        client.connect("127.0.0.1", 53000);
                    }
                }

                if (event.key.code == sf::Keyboard::Key::G) {
                    //if (gameState == GameState::MAIN_MENU) {
                    gameState = GameState::IN_GAME;
                    gameMode = GameMode::DEATH_MATCH;
                    //}
                }
                if (event.key.code == sf::Keyboard::Key::C) {
                    if (!client.active) {
                        //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
                        client.connect("127.0.0.1", 53000);
                    }
                }
                if (event.key.code == sf::Keyboard::Key::Q) {
                    if (server.active) {
                        server.active = false;
                        std::cout << "Stopping server..\n";
                    }
                    if (client.active) {
                        client.active = false;
                        client.disconnect();
                    }
                }*/
                if (event.key.code == sf::Keyboard::Key::C) {
                    if (!client.active) {
                        //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
                        client.connect("127.0.0.1", 53000);
                    }
                }
                if (event.key.code == sf::Keyboard::Key::Q) {
                    if (server.active) {
                        server.active = false;
                        std::cout << "Stopping server..\n";
                    }
                    if (client.active) {
                        client.active = false;
                        client.disconnect();
                    }
                }
            }

            // Handle window resize
            /*               if (event.type == sf::Event::Resized) {

                               sf::Vector2u newWindowSize = window.getSize();

                               float scaleX = static_cast<float>(newWindowSize.x) / windowSize.x;
                               float scaleY = static_cast<float>(newWindowSize.y) / windowSize.y;

                               float sc_x = static_cast<float>(newWindowSize.x) / resolution.x;
                               float sc_y = static_cast<float>(newWindowSize.y) / resolution.y;


                               for (auto &wall: map.walls) {
                                   float newX = wall.sprite.getPosition().x * scaleX;
                                   float newY = wall.sprite.getPosition().y * scaleY;

                                   wall.sprite.setScale(sc_x, sc_y);
                                   wall.sprite.setPosition(newX, newY);
                               }
                               for (auto &floor: map.floors) {

                                   float newX = floor.getPosition().x * scaleX;
                                   float newY = floor.getPosition().y * scaleY;
                                   floor.setScale(sc_x, sc_y);
                                   floor.setPosition(newX, newY);
                               }

                               for (auto &[id, player]: map.players) {

                                   float newX = player.sprite.getPosition().x * scaleX;
                                   float newY = player.sprite.getPosition().y * scaleY;

                                   player.sprite.setScale(sc_x, sc_y);
                                   player.sprite.setPosition(newX, newY);
                               }
                               {
                                   float newX = map.main_player.sprite.getPosition().x * scaleX;
                                   float newY = map.main_player.sprite.getPosition().y * scaleY;
                                   map.main_player.sprite.setScale(sc_x, sc_y);
                                   map.main_player.sprite.setPosition(newX, newY);
                                   view.setCenter(map.main_player.sprite.getPosition());
                                   window.setView(view);
                               }
                               for (auto &missile: map.missiles) {

                                   float newX = missile.sprite.getPosition().x * scaleX;
                                   float newY = missile.sprite.getPosition().y * scaleY;

                                   missile.sprite.setScale(sc_x, sc_y);
                                   missile.sprite.setPosition(newX, newY);
                               }

                               windowSize = newWindowSize;
                           }*/

        }

        window.clear();
        if (server.active) {
            server.send_data();
        }
        if (client.active) {
            client.receive_data();
        }


        if (gameState == GameState::MAIN_MENU) {
            mainMenu.draw(window);
        }
        else  {

            if (gameMode == GameMode::DEATH_MATCH) {
                death_match();
            }
            map.update_player(client);
            object::dont_shoot(client.object);

            //update values
            map.update_players(client);
            map.update_missiles();
            map.update_explosions();

            //collision
            map.check_collision_walls_players();
            map.check_collision_missiles_walls_players();
            map.check_collision_player_players();
            map.check_collision_players_ammo();


            //drawing


            map.draw_players(window);
            // todo raycast
            sf::RenderTexture renderTexture;
            renderTexture.create(map.width * 40, map.height * 40);
            renderTexture.clear(sf::Color::Transparent);
            RayCaster::castRays(renderTexture, map.main_player.sprite.getPosition(), map.walls_for_collision_map, map.main_player.sprite.getRotation() - 157.5);


            sf::Sprite visibleAreaSprite(renderTexture.getTexture());
            visibleAreaSprite.setScale(1.f, -1.f);
            visibleAreaSprite.setPosition(0.f, renderTexture.getSize().y);

            sf::Shader shader;
            if (!shader.loadFromFile(current_dir() + "/shaders/invert_colors.frag", sf::Shader::Fragment)) {
                std::cerr << "Failed to load shader\n";
            }
            shader.setUniform("texture", sf::Shader::CurrentTexture);
            window.draw(visibleAreaSprite, &shader);
            map.draw_floors(window);

            if (map.main_player.hp > 0) {
                window.draw(map.main_player.sprite);
            }

            map.draw_walls(window);
            map.draw_missiles(window);
            map.draw_explosions(window);
            map.draw_dropped_ammo(window);


//            sf::RenderTexture black_overlay;
//            black_overlay.create(map.width * 40, map.height * 40);
//            black_overlay.clear(sf::Color(0,0,0,25));
//            sf::Sprite visibleAreaSprite(black_overlay.getTexture());
//            visibleAreaSprite.setScale(1.f, -1.f);
//            visibleAreaSprite.setPosition(0.f, black_overlay.getSize().y);
//            window.draw(visibleAreaSprite);



            map.main_player_move(view, window, client, gained_focus);
            handleKeyBindings();


            if (gameState == GameState::IN_GAME_PAUSE) {
               // mainMenu.draw_in_pause(window, gameState);
            }


        }

        if (client.active) {
            client.send_data();
        }
        if (server.active) {
            server.receive_data();
        }
/*
        // Define the fragment shader source code
        const char* fragmentShaderCode = R"(
    uniform vec2 center;
    uniform float radius;

    void main() {
        // Calculate the distance from the current pixel to the center of the circle
        float distance = length(gl_FragCoord.xy - center);

        // Calculate the color based on the distance
        float alpha = smoothstep(radius, 0.0, distance);
        gl_FragColor = vec4(0.0, 0.0, 0.0, alpha);
    }
)";

    // Load the shader from the source code
            sf::Shader shader;
            if (!shader.loadFromMemory(fragmentShaderCode, sf::Shader::Fragment)) {
                // Handle error
            }

        sf::RenderTexture renderTexture;
        renderTexture.create(window.getSize().x, window.getSize().y);

// Clear the render texture with a transparent color
        renderTexture.clear(sf::Color::Transparent);

// Draw the visible area onto the render texture
        RayCaster::castRays(renderTexture, map.main_player.sprite.getPosition(), map.walls);

// Display the contents of the render texture
        //renderTexture.display();

// Create a new sprite using the render texture as its texture
        sf::Sprite visibleAreaSprite(renderTexture.getTexture());
        //visibleAreaSprite.setPosition(map.main_player.sprite.getPosition());
        visibleAreaSprite.setScale(1.f, -1.f);
        visibleAreaSprite.setPosition(0.f, renderTexture.getSize().y);
// Apply the shader to the sprite
        window.draw(visibleAreaSprite);//, &shader);

//    // Create a new circle shape with the desired radius
//            sf::CircleShape shape(50);
//
//    // Set the position of the shape
//            shape.setPosition(150, 150);
//
//    // Set the shader parameters
//            shader.setUniform("center", shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius()));
//            shader.setUniform("radius", shape.getRadius());
//
//    // Draw the shape using the shader
//            window.draw(shape, &shader);*/


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
            //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
            client.connect("127.0.0.1", 53000);
        }
    }

    if (multiplayerAction == MultiplayerAction::START_CLIENT) {
        if (!client.active) {
            client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
            //client.connect("127.0.0.1", 53000);
        }
    }

    if (multiplayerAction == MultiplayerAction::STOP_SERVER_AND_CLIENT) {
        if (server.active) {
            server.active = false;
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


            if (map.main_player.hp <= 0) {
                map.main_player.sprite.setPosition(map.random_non_wall_position());
                client.object.pos_x = map.main_player.sprite.getPosition().x;
                client.object.pos_y = map.main_player.sprite.getPosition().y;

                map.main_player.hp = 100;
                map.main_player.bullets = 120;

                client.object.hp = 100;
                client.object.bullets = 120;
            }


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

void Game::takeover() {}

void Game::next_round() {}

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

void Game::draw_score_menu(){
    sf::Vector2f viewCenter = window.getView().getCenter();

    std::map<int, sf::Text> team_1_text;
    std::map<int, sf::Text> team_2_text;

    float team_1_text_offset = -40;
    float team_2_text_offset = -40;

    if (client.object.team == 1) {
        sf::Text text(std::string(client.object.nickname) + " " + std::to_string(client.object.kills) + " " + std::to_string(client.object.deaths) + " ", font);
        text.setScale(0.3, 0.3);
        MainMenu::setUpText(text, 24, viewCenter.x - 120 + 50, viewCenter.y + team_1_text_offset, sf::Color::White);
        team_1_text_offset += 20;
        team_1_text[client.object.id] = text;
    } else {
        sf::Text text(std::string(client.object.nickname) + " " + std::to_string(client.object.kills) + " " + std::to_string(client.object.deaths) + " ", font);
        text.setScale(0.3, 0.3);
        MainMenu::setUpText(text, 24, viewCenter.x - 15 + 50, viewCenter.y + team_2_text_offset, sf::Color::White);
        team_2_text_offset += 20;
        team_2_text[client.object.id] = text;
    }

    for (auto &player: client.objects) {
        if (player.team == 1) {
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

    sf::Text text1 = sf::Text("Amogusi", font);
    sf::Text text2 = sf::Text("Abobusi", font);

    text1.setScale(0.3, 0.3);
    text2.setScale(0.3, 0.3);

    MainMenu::setUpText(text1, 36, viewCenter.x - 120 + 50, viewCenter.y - 60, sf::Color::White);
    MainMenu::setUpText(text2, 36, viewCenter.x - 15 + 50, viewCenter.y - 60, sf::Color::White);

    sf::RectangleShape score_rect = sf::RectangleShape(sf::Vector2f(300, 200));
    score_rect.setFillColor(sf::Color(128, 128, 128, 50));
    score_rect.setPosition(viewCenter);
    center_rect_shape(score_rect);

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
    center_rect_shape(menu_rect_in_game);

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
            gameState = GameState::MAIN_MENU;
            mainMenu.menuState = MenuState::MAIN_MENU;
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
    center_rect_shape(menu_rect_in_game);

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