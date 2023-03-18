+#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"
#include "Map.h"
#include <list>
#include "PathFinder.h"


class EnemyTank {
private:
	int health = 0;
	int ammo = 0;
	int shootTimer = 0;
	int movementSpeed = 0;
	int rotation = 0;
	int shootIndicator = 0;
	std::vector<Position> path;
	sf::Sprite sprite = sf::Sprite();

public:
	enum facing {
		w = 0,
		d = 1,
		a = 3,
		s = 2,
	};
	enum shoot {
		READY = 30,
		RELOAD_START = 0,
	};

	EnemyTank(sf::Sprite& sprite, int movementSpeed) {
		this->health = 100;
		this->ammo = 3;
		this->movementSpeed = movementSpeed;
		this->sprite = sprite;
		this->sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
		this->shootIndicator = READY;
	}
	~EnemyTank() {}

	//collider

	Collider getCollider = collider();
	Collider collider() { return Collider(this->sprite); }

	int getHealth() {
		return this->health;
	}
	int getAmmo() {
		return this->ammo;
	}
	sf::Sprite getSprite() {
		return this->sprite;
	}
	int getShootIndicator() {
		return this->shootIndicator;
	}
	int getMovementSpeed() {
		return this->movementSpeed;
	}
	int getRotation() {
		return this->rotation;
	}
	sf::Vector2f getPosition() {
		return this->sprite.getPosition();
	}


	//set
	void setHealth(int health) {
		this->health = health;
	}
	void setAmmo(int ammo) {
		this->ammo = ammo;
	}
	void setShootIndicator(int shootIndicator) {
		this->shootIndicator = shootIndicator;
	}
	void setMovementSpeed(int ms) {
		this->movementSpeed = ms;
	}
	void setRotation(int rotation) {
		this->rotation = rotation;
	}
	void setPosition(sf::Vector2f position) {
		this->sprite.setPosition(position);
	}
	void setSprite(sf::Sprite& spr) {
		this->sprite = spr;
	}
	//movementUpdate
	sf::Vector2f movedUp() {
		return sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - getMovementSpeed());
	}
	sf::Vector2f movedDown() {
		return sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + getMovementSpeed());
	}
	sf::Vector2f movedLeft() {
		return sf::Vector2f(sprite.getPosition().x - getMovementSpeed(), sprite.getPosition().y);
	}
	sf::Vector2f movedRight() {
		return sf::Vector2f(sprite.getPosition().x + getMovementSpeed(), sprite.getPosition().y);
	}
	void rotate() {
		this->sprite.setRotation(rotation * 90);
	}

	//methods
	void update() {

		if (this->health > 0) {
			//reloading
			{
				if (shootTimer < shoot::READY) { shootTimer++; }
			}
		}
	}

	void draw(sf::RenderWindow& window) {
		if (this->health > 0) {
			window.draw(this->getSprite());
		}
	}

	bool ableToShoot() {
		if (this->health > 0) {
			if (this->ammo >= 0) {
				if (this->shootTimer >= 30) {
					this->shootTimer = 0;
					return true;
				}
			}
		}
		return false;
	}

	void deployAI(EnemyTank& tank) {
		//roam randomly
		//roam to last seen pos of player
		//attack player
	}

	void roam(Map& map) {

		if (this->health > 0) {
			if (this->path.empty()) {
				Position rand = map.getRandomPosition();
				//std::cout << "xer\n";
				if (map.getSceneMap().count(rand)) {
					if (this->getPosition().x != rand.x || this->getPosition().y != rand.y) {
						PathFinder pathFinder(map);
						Position startPosition = { (int)getPosition().x , (int)getPosition().y };
						this->path = pathFinder.findPath(startPosition, rand);
						std::cout << "xer1\n";
					}
				}
				//����� ����������� ����, ���� �� ���������
				//���� ������, ����� ������ �������
			}
			move();
		}
	}

	void chase(EnemyTank& tank) {

	}

	void move() {

		if (this->path.empty()) { return; }

		Position thisPosition = { (int)this->getPosition().x, (int)this->getPosition().y };
		Position nextPosition = this->path.at(0);

		if (thisPosition != nextPosition) {

			Position whereToMove = nextPosition - thisPosition;


			//std::cout << "x: " << whereToMove.x << " y: " << whereToMove.y << " \n";


			if (whereToMove.x <= 40 && whereToMove.x > 0) {
				rotation = facing::d;
				this->sprite.setPosition(movedRight());
			}
			if (whereToMove.x >= -40 && whereToMove.x < 0) {
				rotation = facing::a;
				this->sprite.setPosition(movedLeft());

			}
			if (whereToMove.y <= 40 && whereToMove.y > 0) {
				rotation = facing::s;
				this->sprite.setPosition(movedDown());
			}
			if (whereToMove.y >= -40 && whereToMove.y < 0) {
				rotation = facing::w;
				this->sprite.setPosition(movedUp());
			}
			rotate();
			thisPosition = { (int)this->sprite.getPosition().x, (int)this->sprite.getPosition().y };
		}
		else {
			std::cout << "came\n";
			path.erase(this->path.begin());
			if (!this->path.empty()) {
				nextPosition = this->path.at(0);
			}
			else return;
		}

	}
};