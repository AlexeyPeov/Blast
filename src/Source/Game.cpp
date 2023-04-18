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


            if (mainMenu.menuState == MenuState::START) {
                gameState = GameState::IN_GAME;
                mainMenu.menuState = MenuState::IN_GAME;
            }

            // Handle window fullscreen
            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Escape) {
                    if (gameState == GameState::IN_GAME) {
                        gameState = GameState::IN_GAME_PAUSE;
                        mainMenu.menuState = MenuState::IN_GAME_PAUSE;
                    } else if (gameState == GameState::IN_GAME_PAUSE) {
                        gameState = GameState::IN_GAME;
                    }
                }

                /*if (event.key.code == sf::Keyboard::Key::H) {
                    if(!server.active){
                        server.set_listener();
                        //client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
                        client.connect("127.0.0.1", 53000);
                    }
                }*/

                if (event.key.code == sf::Keyboard::Key::G) {
                    //if (gameState == GameState::MAIN_MENU) {
                    gameState = GameState::IN_GAME;
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
            map.main_player.hp = 100;
            // mainMenu.drawRectangle(window, font);
        } else if (gameState == GameState::IN_GAME || gameState == GameState::IN_GAME_PAUSE) {

            object::dont_shoot(client.object);
            if (gained_focus && gameState != GameState::IN_GAME_PAUSE) {
                map.main_player_move(view, window, client);
            }

            //update values
            map.update_walls();
            map.update_players(client);
            map.update_missiles();
            map.update_explosions();
            map.update_player();

            //collision
            map.check_collision_walls_players();
            map.check_collision_missiles_walls_players();
            map.check_collision_player_players();




            //drawing
            map.draw_walls(window);
            map.draw_floors(window);
            map.draw_missiles(window);
            map.draw_players(window);
            map.draw_explosions(window);


            if (gameState == GameState::IN_GAME_PAUSE) {
                mainMenu.draw_in_pause(window, gameState);
            }

        }
        if (client.active) {
            client.send_data();
        }
        if (server.active) {
            server.receive_data();
        }

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
