#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Levels.h"
#include "RayCaster.h"
#include "Server.h"
#include "MainMenu.h"
#include <chrono>
#include <thread>

class Game {
private:
    struct Resolution {
//        uint x = 1600;
//        uint y = 800;

        uint x = 1280;
        uint y = 720;
    };


    Map map;
    Resolution resolution;
    sf::VideoMode desktop;
    sf::RenderWindow window;
    sf::RectangleShape button;
    sf::Font font;
    sf::Text label;
    bool fullscreen = false;
    sf::Vector2u windowSize;
    sf::View view;
    Server server;
    Client client;
    bool gained_focus = false;
    bool is_running = true;
    GameState gameState = GameState::MAIN_MENU;

    sf::Event game_event;

    MainMenu mainMenu;

public:
    Game() : desktop(sf::VideoMode::getDesktopMode()),
             window(sf::VideoMode(resolution.x, resolution.y), "BLAST", sf::Style::Titlebar | sf::Style::Close),
             button(sf::Vector2f(100, 50)) {

        view = sf::View(sf::FloatRect(0, 0, resolution.x / 3, resolution.y / 3));
        view.setCenter((sf::Vector2f)window.getPosition());
        window.setView(view);

        // Set the button color
        button.setFillColor(sf::Color(128, 128, 128));

        // Load the font and create the label
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        label.setFont(font);
        label.setString("Fullscreen");
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::Black);


        map.init_map_textures();
        map.init_main_player();
        map.init_walls(2);
        windowSize = window.getSize();

        mainMenu = MainMenu(font);

    }

    void run() {
        auto frame_duration = std::chrono::milliseconds(1000 / 30);
        while (is_running) {

            if (mainMenu.menuState == MenuState::QUIT) {
                is_running = false;
            }
            auto frame_start = std::chrono::steady_clock::now();
            sf::Event event{};
            mainMenu.setMainMenuItems(window);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    is_running = false;
                }
                if (event.type == sf::Event::GainedFocus) {
                    this->gained_focus = true;
                } else if (event.type == sf::Event::LostFocus) {
                    this->gained_focus = false;
                }


                if(gameState == GameState::MAIN_MENU){
                    mainMenu.ipInput.handleEvent(event);
                    mainMenu.portInput.handleEvent(event);
                } else if (gameState == GameState::IN_GAME){
                    //handle ingame events
                }


                if (mainMenu.menuState == MenuState::START) {
                    gameState = GameState::IN_GAME;
                    mainMenu.menuState = MenuState::CLOSED;
                }

                // Handle window fullscreen
                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        if (gameState == GameState::IN_GAME) {
                            gameState = GameState::IN_GAME_PAUSE;
                            mainMenu.menuState = MenuState::IN_PAUSE;
                        } else if(gameState == GameState::IN_GAME_PAUSE) {
                            gameState = GameState::IN_GAME;
                        }
                    }

                    if (event.key.code == sf::Keyboard::G) {
                        if (mainMenu.menuState != MenuState::CLOSED) {
                            gameState = GameState::IN_GAME;
                        }
                    }

                    if (event.key.code == sf::Keyboard::Key::Space) {
                        // Toggle fullscreen mode
                        fullscreen = !fullscreen;
                        if (fullscreen) {
                            window.create(desktop, "BLAST", sf::Style::Fullscreen);
                            view = sf::View(sf::FloatRect(0, 0, window.getSize().x / 3, window.getSize().y / 3));
                        } else {
                            window.create(sf::VideoMode(resolution.x, resolution.y), "BLAST",
                                          sf::Style::Titlebar | sf::Style::Close);
                            view = sf::View(sf::FloatRect(0, 0, resolution.x / 3, resolution.y / 3));
                        }

                    }

                    if (event.key.code == sf::Keyboard::Key::H) {
                        if(!server.active){
                            server.set_listener();
                            client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
                        }
                    }

                    if (event.key.code == sf::Keyboard::Key::C) {
                        if(!client.active){
                            client.connect(mainMenu.ipInput.inputString, mainMenu.portInput.toInt());
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
                if (event.type == sf::Event::Resized) {
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
                }
                this->game_event = event;
            }

            window.clear();

            if (gameState == GameState::MAIN_MENU) {
                mainMenu.draw(window);
               // mainMenu.drawRectangle(window, font);
            } else if (gameState == GameState::IN_GAME_PAUSE) {
                mainMenu.draw_in_pause(window, gameState);
               // mainMenu.drawRectangle(window, font);
            } else if (gameState == GameState::IN_GAME) {
                if (server.active) {
                    server.send_data();
                }
                if (client.active){
                    client.receive_data();
                }
                if (gained_focus) {
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


                if(client.active){
                    client.send_data();
                }
                if(server.active){
                    server.receive_data();
                }
            }
            window.display();

            auto frame_end = std::chrono::steady_clock::now();
            auto elapsed_time = frame_end - frame_start;
            if (elapsed_time < frame_duration) {
                std::this_thread::sleep_for(frame_duration - elapsed_time);
            }
        }
    }
};