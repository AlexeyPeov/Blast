#include "../Headers/MainMenu.h"


void MainMenu::setUpText(sf::Text &text, int character_size, float pos_x, float pos_y, sf::Color color) {
    text.setCharacterSize(character_size);
    text.setFillColor(color);
    text.setPosition(pos_x, pos_y);
    //sf::FloatRect text1Bounds = text1.getLocalBounds();
    //text.setOrigin(text1Bounds.left + text1Bounds.width / 2.0f, text1Bounds.top + text1Bounds.height / 2.0f);
}

bool MainMenu::mouseCursorCollidesWithMenuItem(sf::Vector2f &mousePos, sf::FloatRect menuItemBounds) {
    return (
            (float) mousePos.x >= menuItemBounds.left &&
            (float) mousePos.x <= menuItemBounds.left + menuItemBounds.width &&
            (float) mousePos.y >= menuItemBounds.top &&
            (float) mousePos.y <= menuItemBounds.top + menuItemBounds.height
    );
}

bool MainMenu::clicked() {
    static bool wasPressed = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!wasPressed) {
            wasPressed = true;
            return true;
        }
    } else {
        wasPressed = false;
    }
    return false;
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
    center_rect_shape(menuRect);

    setUpText(text1, 36, viewCenter.x - 20 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 20 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 20 * 3, viewCenter.y, sf::Color::White);


    if (mouseCursorCollidesWithMenuItem(mousePos, text1.getGlobalBounds())) {
        text1.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::CHOOSING_GAME_STATE;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::OPTIONS;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::QUIT;
        }
    }
    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
}

void MainMenu::drawPauseMenu(sf::RenderWindow &window, GameState &gameState) {
    // setMainMenuItems(window);
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1_in_game = sf::Text("Continue", font);
    text2_in_game = sf::Text("Options", font);
    text3_in_game = sf::Text("Exit to main menu", font);

    text1_in_game.setScale(0.3, 0.3);
    text2_in_game.setScale(0.3, 0.3);
    text3_in_game.setScale(0.3, 0.3);

    menu_rect_in_game.setFillColor(sf::Color(128, 128, 128));
    menu_rect_in_game.setPosition(viewCenter);
    center_rect_shape(menu_rect_in_game);

    setUpText(text1_in_game, 36, viewCenter.x - 27, viewCenter.y - 40, sf::Color::White);
    setUpText(text2_in_game, 36, viewCenter.x - 25, viewCenter.y - 20, sf::Color::White);
    setUpText(text3_in_game, 36, viewCenter.x - 50, viewCenter.y, sf::Color::White);

    if (mouseCursorCollidesWithMenuItem(mousePos, text1_in_game.getGlobalBounds())) {
        text1_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            gameState = GameState::IN_GAME;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text2_in_game.getGlobalBounds())) {
        text2_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::IN_GAME_OPTIONS;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text3_in_game.getGlobalBounds())) {
        text3_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            *this->multiplayerAction = MultiplayerAction::STOP_SERVER_AND_CLIENT;
            menuState = MenuState::MAIN_MENU;
            gameState = GameState::MAIN_MENU;
        }
    }
    window.draw(menu_rect_in_game);
    window.draw(text1_in_game);
    window.draw(text2_in_game);
    window.draw(text3_in_game);
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
    center_rect_shape(menuRect);

    setUpText(text1, 36, viewCenter.x - 40 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 35 * 3, viewCenter.y - 10 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 20 * 3, viewCenter.y + 20 * 3, sf::Color::White);


    if (mouseCursorCollidesWithMenuItem(mousePos, text1.getGlobalBounds())) {
        text1.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::SINGLE_PLAYER;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::IS_HOST;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::MAIN_MENU;
        }
    }
    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
}

void MainMenu::drawSinglePlayerMenu(sf::RenderWindow &window) {

    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1 = sf::Text("Choose map: ", font);
    text2 = sf::Text("Map 1", font);
    text3 = sf::Text("Map 2", font);
    text4 = sf::Text("Map 3", font);
    text5 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_shape(menuRect);

    setUpText(text1, 36, viewCenter.x - 40 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 20 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x - 20 * 3, viewCenter.y, sf::Color::White);
    setUpText(text4, 36, viewCenter.x - 20 * 3, viewCenter.y + 20 * 3, sf::Color::White);
    setUpText(text5, 36, viewCenter.x - 20 * 3, viewCenter.y + 40 * 3, sf::Color::White);


    if (mouseCursorCollidesWithMenuItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::MAIN_MENU;
        }
    }


    window.draw(menuRect);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
    window.draw(text5);
}

void MainMenu::drawMultiplayerLobby(sf::RenderWindow &window) {
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();


    // table of players
    std::unordered_map<int, sf::Text> team_1_text;
    std::unordered_map<int, sf::Text> team_2_text;

    float team_1_text_offset = -40 * 3;
    float team_2_text_offset = -40 * 3;

    if (client->object.team == 1) {
        sf::Text text(client->object.nickname, font);
        setUpText(text, 24, viewCenter.x - 120 * 3, viewCenter.y + team_1_text_offset, sf::Color::White);
        team_1_text_offset += 20 * 3;
        team_1_text[client->object.id] = text;
    } else {
        sf::Text text(client->object.nickname, font);
        setUpText(text, 24, viewCenter.x - 15 * 3, viewCenter.y + team_2_text_offset, sf::Color::White);
        team_2_text_offset += 20 * 3;
        team_2_text[client->object.id] = text;
    }

    for (auto &player: client->objects) {
        if (player.team == 1) {
            sf::Text text(player.nickname, font);
            setUpText(text, 24, viewCenter.x - 120 * 3, viewCenter.y + team_1_text_offset, sf::Color::White);
            team_1_text_offset += 20 * 3;
            team_1_text[player.id] = text;
        } else {
            sf::Text text(player.nickname, font);
            setUpText(text, 24, viewCenter.x - 15 * 3, viewCenter.y + team_2_text_offset, sf::Color::White);
            team_2_text_offset += 20 * 3;
            team_1_text[player.id] = text;
        }
    }


    sf::Text chooseTeam("Choose team", font);

    text1 = sf::Text("Amogusi", font);
    text2 = sf::Text("Abobusi", font);
    text3 = sf::Text("Maps:", font);
    text4 = sf::Text("Start", font);
    text5 = sf::Text("Back", font);

    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setSize(sf::Vector2f(300 * 3 * 2, 200 * 3 * 2));
    menuRect.setPosition(viewCenter);
    center_rect_shape(menuRect);

    hostRadioBox.setFillColor(sf::Color(240, 240, 240));
    hostRadioBox.setOutlineThickness(3);
    hostRadioBox.setOutlineColor(sf::Color(61, 61, 61));
    hostRadioBox.setPosition(viewCenter.x, viewCenter.y - 18 * 3);

    setUpText(chooseTeam, 36, viewCenter.x - 80 * 3, viewCenter.y - 80 * 3, sf::Color::White);
    setUpText(text1, 36, viewCenter.x - 120 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text2, 36, viewCenter.x - 15 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text3, 36, viewCenter.x + 70 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text4, 36, viewCenter.x - 20 * 3, viewCenter.y + 60 * 3, sf::Color::White);
    setUpText(text5, 36, viewCenter.x - 20 * 3, viewCenter.y + 80 * 3, sf::Color::White);

    // changing teams
    if (mouseCursorCollidesWithMenuItem(mousePos, text1.getGlobalBounds())) {
        text1.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            if (team_2_text.find(client->object.id) != team_2_text.end()) {
                client->object.team = 1;
                team_1_text[client->object.id] = team_2_text[client->object.id];
                team_2_text.erase(client->object.id);
            }
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            if (team_1_text.find(client->object.id) != team_1_text.end()) {
                client->object.team = 2;
                team_2_text[client->object.id] = team_1_text[client->object.id];
                team_1_text.erase(client->object.id);
            }
        }
    }else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getGlobalBounds())) {
        //if(host){
            text4.setFillColor(sf::Color::Yellow);
            if (clicked()) {
                //game.start();
            }
      //  }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::IS_HOST;
        }
    }


    /*if (mouseCursorCollidesWithMenuItem(mousePos, text3.getPosition())) {
        text3.setFillColor(sf::Color::Yellow);
        if(clicked()){
            if(host){
                menuState = MenuState::MULTIPLAYER_LOBBY;
            } else {
                menuState = MenuState::CLIENT;
            }

        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, hostRadioBox.getPosition())) {
        hostRadioBox.setOutlineColor(sf::Color::Yellow);
        if (clicked()) {
            host = !host;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getPosition())) {
        text4.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            menuState = MenuState::CHOOSING_GAME_STATE;
        }
    }

    if (host) {
        hostRadioBox.setFillColor(sf::Color(197, 255, 202));
    }*/
    window.draw(menuRect);
    window.draw(chooseTeam);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
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
    static bool host = false;
    text1 = sf::Text("Are you host?", font);
    text2 = sf::Text("Host", font);
    text3 = sf::Text("Enter nickname:", font);
    text4 = sf::Text("Continue", font);
    text5 = sf::Text("Back", font);


    menuRect.setFillColor(sf::Color(128, 128, 128));
    menuRect.setPosition(viewCenter);
    center_rect_shape(menuRect);

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


    if (mouseCursorCollidesWithMenuItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            if (host) {
                *this->multiplayerAction = MultiplayerAction::START_SERVER_AND_CLIENT;
                menuState = MenuState::MULTIPLAYER_LOBBY;
            } else {
                menuState = MenuState::CLIENT;
            }
            object::copy_string_to_nickname(nicknameInput.inputString, this->client->object);
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, hostRadioBox.getGlobalBounds())) {
        hostRadioBox.setOutlineColor(sf::Color::Yellow);
        if (clicked()) {
            host = !host;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (clicked()) {
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

    if (host) {
        hostRadioBox.setFillColor(sf::Color(197, 255, 202));
    }
    window.draw(hostRadioBox);
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
    center_rect_shape(menuRect);

    setUpText(text1, 36, viewCenter.x - 45 * 3, viewCenter.y - 80 * 3, sf::Color::White);
    ipInput.setPosition(viewCenter.x - 70 * 3, viewCenter.y - 50 * 3, 140 * 3, 20 * 3);

    setUpText(text2, 36, viewCenter.x - 35 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    portInput.setPosition(viewCenter.x - 70 * 3, viewCenter.y + 10 * 3, 140 * 3, 20 * 3);

    setUpText(text3, 36, viewCenter.x - 30 * 3, viewCenter.y + 40 * 3, sf::Color::White);
    setUpText(text4, 36, viewCenter.x - 20 * 3, viewCenter.y + 70 * 3, sf::Color::White);

    if (mouseCursorCollidesWithMenuItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            *this->multiplayerAction = MultiplayerAction::START_CLIENT;
            menuState = MenuState::MULTIPLAYER_LOBBY;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if (clicked()) {
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
    center_rect_shape(menuRect);

    setUpText(text1, 12 * 3, viewCenter.x - 50 * 3, viewCenter.y - 60 * 3, sf::Color::White);
    setUpText(text2, 12 * 3, viewCenter.x - 30 * 3, viewCenter.y - 40 * 3, sf::Color::White);
    setUpText(text3, 12 * 3, viewCenter.x - 30 * 3, viewCenter.y - 20 * 3, sf::Color::White);
    setUpText(text4, 12 * 3, viewCenter.x - 30 * 3, viewCenter.y, sf::Color::White);
    setUpText(text5, 12 * 3, viewCenter.x - 20 * 3, viewCenter.y + 20 * 3, sf::Color::White);


    if (mouseCursorCollidesWithMenuItem(mousePos, text2.getGlobalBounds())) {
        text2.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            //change to fullscreen
            *gameVideoMode = VideoMode::FULLSCREEN;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text3.getGlobalBounds())) {
        text3.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            //change 1600x800
            *gameVideoMode = VideoMode::_1600x800;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text4.getGlobalBounds())) {
        text4.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            //change to 1280x720
            *gameVideoMode = VideoMode::_1280x720;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text5.getGlobalBounds())) {
        text5.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            if (menuState == MenuState::IN_GAME_OPTIONS) {
                menuState = MenuState::IN_GAME_PAUSE;
            } else if (menuState == MenuState::OPTIONS) {
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

void MainMenu::drawInGameOptionsMenu(sf::RenderWindow &window) {
    //   setMainMenuItems(window);
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mp);

    sf::Vector2f viewCenter = window.getView().getCenter();

    text1_in_game = sf::Text("Screen Resolution:", font);
    text2_in_game = sf::Text("Fullscreen", font);
    text3_in_game = sf::Text("1600x800", font);
    text4_in_game = sf::Text("1280x720", font);
    text5_in_game = sf::Text("Back", font);

    text1_in_game.setScale(0.3, 0.3);
    text2_in_game.setScale(0.3, 0.3);
    text3_in_game.setScale(0.3, 0.3);
    text4_in_game.setScale(0.3, 0.3);
    text5_in_game.setScale(0.3, 0.3);

    //menu_rect_in_game.setFillColor(sf::Color(128, 128, 128));
    menu_rect_in_game.setPosition(viewCenter);
    center_rect_shape(menu_rect_in_game);

    setUpText(text1_in_game, 12 * 3, viewCenter.x - 50, viewCenter.y - 60, sf::Color::White);
    setUpText(text2_in_game, 12 * 3, viewCenter.x - 30, viewCenter.y - 40, sf::Color::White);
    setUpText(text3_in_game, 12 * 3, viewCenter.x - 30, viewCenter.y - 20, sf::Color::White);
    setUpText(text4_in_game, 12 * 3, viewCenter.x - 30, viewCenter.y, sf::Color::White);
    setUpText(text5_in_game, 12 * 3, viewCenter.x - 20, viewCenter.y + 20, sf::Color::White);


    if (mouseCursorCollidesWithMenuItem(mousePos, text2_in_game.getGlobalBounds())) {
        text2_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            //change to fullscreen
            *gameVideoMode = VideoMode::FULLSCREEN;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text3_in_game.getGlobalBounds())) {
        text3_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            //change 1600x800
            *gameVideoMode = VideoMode::_1600x800;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text4_in_game.getGlobalBounds())) {
        text4_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            //change to 1280x720
            *gameVideoMode = VideoMode::_1280x720;
        }
    } else if (mouseCursorCollidesWithMenuItem(mousePos, text5_in_game.getGlobalBounds())) {
        text5_in_game.setFillColor(sf::Color::Yellow);
        if (clicked()) {
            if (menuState == MenuState::IN_GAME_OPTIONS) {
                menuState = MenuState::IN_GAME_PAUSE;
            }
        }
    }
    window.draw(menu_rect_in_game);
    window.draw(text1_in_game);
    window.draw(text2_in_game);
    window.draw(text3_in_game);
    window.draw(text4_in_game);
    window.draw(text5_in_game);
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
    } else if (menuState == MenuState::CLIENT) {
        drawClientMenu(window);
    } else if (menuState == MenuState::MULTIPLAYER_LOBBY) {
        drawMultiplayerLobby(window);
    } else if (menuState == MenuState::OPTIONS) {
        drawOptionsMenu(window);
    }
}

void MainMenu::draw_in_pause(sf::RenderWindow &window, GameState &gameState) {
    //   setMainMenuItems(window);
    if (menuState == MenuState::IN_GAME_PAUSE) {
        drawPauseMenu(window, gameState);
    }
    if (menuState == MenuState::IN_GAME_OPTIONS) {
        drawInGameOptionsMenu(window);
    }
}
