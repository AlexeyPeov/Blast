+#pragma once
#include "SFML/Graphics.hpp"
#include <time.h>
#include <iostream>
#include <list>
#include <unordered_map>

#include "Button.hpp"
#include "Missile.h"
#include "Wall.h"
#include "Tank.h"
#include "Animation.h"
#include "Collider.h"
#include "EnemyTank.h"
#include "Map.h"
#include "MapsConfig.h"
#include "PathFinder.h"
#include "Player.h"

class Game {
private:
    const int w = 40;
    const int h = 40;

    const int dw = 40;
    const int dh = 20;

    int resx = w * dw;
    int resy = h * dh;

    bool running = true;
    bool isFullscreen = false;

    Map map;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(this->resx, this->resy), "tanki", sf::Style::Default);
    sf::View* view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(this->resx, this->resy));

    sf::Font font;

    sf::Event e;

    sf::Texture friendlyTankTexture, enemyTankTexture, missileTexture, unbreakableBorder;
    sf::Texture floor, personStationary;

    //states of wall
    sf::Texture wallTexture5, wallTexture4, wallTexture3, wallTexture2, wallTexture1;

    sf::Texture explosion;

    sf::Sprite missileSpr;
    sf::Sprite wallSpr;
    sf::Sprite unbreakableBorderSpr;
    sf::Sprite floorSpr;
    sf::Sprite friendlyTankSpr;
    sf::Sprite enemyTankSpr;
    sf::Sprite playerSpr;

    //����� ������
    std::list<Missile*> missiles;
    std::list<Wall*> walls;
    std::list<Player*> players;
    std::list<EnemyTank*> enemyTanks;
    std::list<Animation*> explosions;

public:
    Game() {

        std::map<Position, int> sceneMap;
        for (int i = 0; i < 800; i++) {
            if (map_CROSS[i] == 0) {
                if (rand() % 15 == 0) {
                    map_CROSS[i] = 1;
                }
            }
        }
        for (int i = 0; i < 800; i++) {
            int x = ((i % 40) * 40) + 20;
            int y = ((i / 40) * 40) + 20;
            Position pos = { x , y };
            sceneMap[pos] = map_CROSS[i];
        }


        this->map = Map(sceneMap, resx, resy);

        this->window->setFramerateLimit(60);
        this->view->setCenter(this->resx / 2, this->resy / 2);

        if (!this->font.loadFromFile("C:/Windows/Fonts/Calibri.ttf"))
        {
            std::cout << "can't load font" << std::endl;
        }

        //buttons
        /*{gui::button yeah("Yeah!", font, sf::Vector2f(100.f, 100.f), gui::style::save);
        gui::button nope("Nope", font, sf::Vector2f(100.f, 200.f), gui::style::cancel);
        gui::button nice("Nice...", font, sf::Vector2f(300.f, 100.f), gui::style::clean);
        gui::button custom("Sweet", font, sf::Vector2f(300.f, 200.f), gui::style::none);

        yeah.setBehavior();
        nope.setBehavior();
        nice.setBehavior();
        custom.setBehavior();

        custom.setBorderThickness(2.f);
        custom.setBorderRadius(20.f);
        custom.setBorderColor(sf::Color(255, 255, 255, 255));
        custom.setColorNormal(sf::Color(200, 0, 200, 255));
        custom.setColorHover(sf::Color(255, 0, 255, 100));
        custom.setColorClicked(sf::Color(150, 0, 150, 255));
        custom.setColorTextNormal(sf::Color(255, 255, 255, 255));
        custom.setColorTextHover(sf::Color(255, 255, 0, 255));
        custom.setColorTextClicked(sf::Color(255, 0, 0, 255)); }*/




        this->friendlyTankTexture.loadFromFile("textures/tank.png");
        this->enemyTankTexture.loadFromFile("textures/enemyTank.png");
        this->missileTexture.loadFromFile("textures/missle.png");
        this->unbreakableBorder.loadFromFile("textures/unbreakableBorder.png");
        this->floor.loadFromFile("textures/floor.png");
        this->personStationary.loadFromFile("textures/personStationary.png");


        this->wallTexture5.loadFromFile("textures/border5.png");
        this->wallTexture4.loadFromFile("textures/border4.png");
        this->wallTexture3.loadFromFile("textures/border3.png");
        this->wallTexture2.loadFromFile("textures/border2.png");
        this->wallTexture1.loadFromFile("textures/border1.png");
        this->explosion.loadFromFile("textures/explosion.png");


        this->missileSpr = sf::Sprite(missileTexture);
        this->wallSpr = sf::Sprite(wallTexture5);
        this->unbreakableBorderSpr = sf::Sprite(unbreakableBorder);
        this->floorSpr = sf::Sprite(floor);
        this->friendlyTankSpr = sf::Sprite(friendlyTankTexture);
        this->enemyTankSpr = sf::Sprite(enemyTankTexture);
        this->playerSpr = sf::Sprite(personStationary);

        Player* player = new Player(playerSpr, 2);
        player->setPosition(sf::Vector2f(620, 620));
        players.push_back(player);


        //��������� �����

        for (int i = 0; i < 5; i++) {
            EnemyTank* tank = new EnemyTank(enemyTankSpr, 1);
            tank->setPosition(sf::Vector2f(60, 60));
            enemyTanks.push_back(tank);
        }


        //��������� �����

        for (auto& it : map.getSceneMap()) {
            if (it.second == 1 || it.second == 2) {
                if (it.second == 1) {
                    Wall* wall = new Wall(wallSpr, 5, sf::Vector2f((float)it.first.x, (float)it.first.y));
                    walls.push_back(wall);
                }
                else {
                    Wall* wall = new Wall(unbreakableBorderSpr, 999999999, sf::Vector2f((float)it.first.x, (float)it.first.y));
                    walls.push_back(wall);
                }

            }
        }
    }
    ~Game() {
        delete window;
        delete view;
    }

    void run() {
        while (running)
        {
            while (window->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                {
                    running = false;
                    window->close();
                }
                if (e.type == e.KeyReleased) {
                    if (e.key.code == sf::Keyboard::Escape) {
                        if (isFullscreen == false) {
                            window->create(sf::VideoMode(1920, 1080), "tanki", sf::Style::Fullscreen);
                            window->setFramerateLimit(60);
                            //this->view->setCenter(1920.0/2, 1080.0/2);
                            isFullscreen = true;
                        }
                        else {
                            window->create(sf::VideoMode(this->resx, this->resy), "tanki", sf::Style::Default);
                            window->setFramerateLimit(60);
                            //this->view->setCenter(this->resx/2,this->resy/2);
                            isFullscreen = false;
                        }
                    }
                }
            }
            //������(�����)
            /*if (yeah.update(e, window) && !buttonClicked ) {

                buttonClicked = true;
                std::cout << "Clicked\n";
            }
            */



            //collision , then update
            //wall - tank - player - missiles
            //tank - player, missiles
            //player -missiles
            for (auto wall : walls) {
                for (auto missile : missiles) {
                    if (wall->getCollider.checkCollision(missile->getCollider, 1.0f)) {
                        missile->setLife(false);
                        wall->setHp(wall->getHp() - 1);
                        Animation* a = new Animation(explosion, 40, 0, 40, 40, 19, 1);
                        a->sprite.setPosition(missile->getSprite().getPosition());
                        explosions.push_back(a);
                        for (auto player : players) {
                            float explosionDamageDistance = sqrt(
                                pow(abs(missile->getSprite().getPosition().x - player->getSprite().getPosition().x), 2) +
                                pow(abs(missile->getSprite().getPosition().y - player->getSprite().getPosition().y), 2));

                            if (explosionDamageDistance < 50) {
                                player->setHealth(player->getHealth() - 20);
                            }
                        }

                    }

                }
                for (auto player : players) {
                    player->getCollider.checkCollision(wall->getCollider, 0.0f);
                    //this->view->setCenter(player->getPosition());
                }

                for (auto tank : enemyTanks) {
                    tank->getCollider.checkCollision(wall->getCollider, 0.0f);
                }

            }

            for (auto player : players) {
                for (auto tank : enemyTanks) {
                    tank->getCollider.checkCollision(player->getCollider, 0.0f);
                    for (auto missile : missiles) {
                        if (missile->getCollider.checkCollision(tank->getCollider, 0.0f)) {
                            missile->setLife(false);
                            Animation* a = new Animation(explosion, 40, 0, 40, 40, 19, 1);
                            a->sprite.setPosition(missile->getSprite().getPosition());
                            explosions.push_back(a);
                            tank->setHealth(tank->getHealth() - 20);

                        }
                    }
                    for (auto missile : missiles) {
                        if (player->getCollider.checkCollision(missile->getCollider, 0.0f)) {
                            missile->setLife(false);
                            Animation* a = new Animation(explosion, 40, 0, 40, 40, 19, 1);
                            a->sprite.setPosition(missile->getSprite().getPosition());
                            explosions.push_back(a);
                            player->setHealth(player->getHealth() - 20);
                        }
                    }
                }
            }

            //���� ����� �� ���
            for (auto player : players) {
                if (e.type == sf::Event::MouseButtonPressed) {
                    if (e.key.code == sf::Mouse::Left && player->ableToShoot()) {
                        Missile* mis = new Missile(missileSpr, player->getRotation(), player->getPosition(), 30);
                        missiles.push_back(mis);
                    }
                }
            }


            //��������� �������� � ����
            for (auto i = missiles.begin(); i != missiles.end(); ) {
                Missile* m = *i;
                m->update();

                if (m->getLife() == false) {
                    i = missiles.erase(i);
                    delete m;
                    std::cout << "deleted - m\n";
                }
                else i++;
            }

            for (auto i = enemyTanks.begin(); i != enemyTanks.end(); ) {
                EnemyTank* e = *i;
                e->update();

                if (e->getHealth() <= 0) {
                    i = enemyTanks.erase(i);
                    delete e;
                    std::cout << "deleted - enemytank\n";
                }
                else i++;
            }

            //��� ������ � ��������� �������
            for (auto i = walls.begin(); i != walls.end(); ) {
                Wall* w = *i;
                if (!(w->getHp() >= 5))
                    if (w->getHp() == 4) { w->setTexture(wallTexture4); }
                    else if (w->getHp() == 3) { w->setTexture(wallTexture3); }
                    else if (w->getHp() == 2) { w->setTexture(wallTexture2); }
                    else if (w->getHp() == 1) { w->setTexture(wallTexture1); }
                if (w->getHp() <= 0) {
                    i = walls.erase(i);
                    delete w;
                    std::cout << "deleted -Wall\n";
                }
                else i++;
            }

            //������
            for (auto it = explosions.begin(); it != explosions.end();) {
                Animation* a = *it;
                a->update();
                if (a->played) {
                    it = explosions.erase(it);
                    delete a;
                    std::cout << "deleted -a\n";
                }
                else {
                    it++;
                }

            }


            for (auto& enemyTank : enemyTanks) {
                enemyTank->roam(map);
            }
            for (auto player : players) {
                player->update(*window);
            }

            /*if (tank.health <= 0 && tank.health > -50) {
                std::cout << "aboba suka\n";
                Animation* a = new Animation(explosion, 40, 0, 40, 40, 19, 1);
                a->sprite.setPosition(tank.position.x, tank.position.y);
                explosions.push_back(a);
                tank.health = -151;
            }*/


            window->clear();


            // ���� ��������





            //������ ���������� �����
            for (int i = 0; i < 800; i++) {
                int x = i % 40;
                int y = i / 40;
                floorSpr.setPosition(sf::Vector2f(x * 40, y * 40));
                window->draw(floorSpr);
            }


            //������ �� ���������
            for (auto i : missiles) { i->draw(*window); }
            for (auto b : walls) { b->draw(*window); }
            for (auto c : explosions) { window->draw(c->sprite); }
            for (auto enemyTank : enemyTanks) { enemyTank->draw(*window); }

            for (auto player : players) {
                player->draw(*window);
            }
            //window->setView(*view);
            window->display();
        }
    }
};