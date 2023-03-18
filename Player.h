+#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Collider.h"
#include "Animation.h"


class Player {
private:
	int health = 0;
	int ammo = 0;
	int movementSpeed = 0;
	sf::Sprite sprite = sf::Sprite();
	int shootIndicator = 0;
	float rotation = 0;

public:

	enum shoot {
		READY = 30,
		RELOAD_START = 0,
	};


	Player(sf::Sprite& sprite, int movementSpeed) {
		this->health = 100;
		this->ammo = 3;
		this->movementSpeed = movementSpeed;
		this->sprite = sprite;
		this->sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
		this->shootIndicator = READY;
	}
	~Player() {}

	//get
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
	float getRotation() {
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
	void setRotation(float rotation) {
		this->rotation = rotation;
	}
	void setPosition(sf::Vector2f position) {
		this->sprite.setPosition(position);
	}

	//collider
	Collider getCollider = collider();
	Collider collider() { return Collider(this->sprite); }

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
		this->sprite.setRotation(this->rotation);
	}

	//gameplay methods
	void update(sf::RenderWindow& window) {
		//basic movement
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				this->sprite.setPosition(movedUp());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				this->sprite.setPosition(movedDown());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				this->sprite.setPosition(movedLeft());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				this->sprite.setPosition(movedRight());
			}

			float dx, dy;
			dx = this->getPosition().x - sf::Mouse::getPosition(window).x;
			dy = this->getPosition().y - sf::Mouse::getPosition(window).y;

			this->rotation = (atan2(dx, dy) * -180.0000) / 3.1416;
			/*if (this->rotation < 0) {
				this->rotation = 360 - abs(this->rotation);
			}*/
			//std::cout << "rt: " << rotation << "\n";
			rotate();
		}
		//reloading
		{
			if (getShootIndicator() < shoot::READY) { this->setShootIndicator(this->getShootIndicator() + 1); }
		}
	}

	void draw(sf::RenderWindow& window) {
		if (this->getHealth() > 0) {
			window.draw(getSprite());
		}
	}

	bool ableToShoot() {
		if (this->getHealth() > 0) {
			if (this->getAmmo() >= 0) {
				if (this->getShootIndicator() >= shoot::READY) {
					this->setShootIndicator(shoot::RELOAD_START);
					return true;
				}
			}
		}
		return false;
	}
};