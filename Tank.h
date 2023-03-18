+#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Collider.h"
#include "Animation.h"


class Tank {
private:
	int health = 0;
	int ammo = 0;
	int movementSpeed = 0;
	sf::Sprite sprite = sf::Sprite();
	int shootIndicator = 0;
	int rotation = 0;

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



	Tank(sf::Sprite& sprite, int movementSpeed) {
		this->health = 100;
		this->ammo = 3;
		this->movementSpeed = movementSpeed;
		this->sprite = sprite;
		this->sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
		this->shootIndicator = READY;
	}
	~Tank() {}

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
		this->sprite.setRotation(rotation * 90);
	}

	//gameplay methods
	void update() {
		//basic movement
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				rotation = facing::w;
				this->sprite.setPosition(movedUp());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				rotation = facing::s;
				this->sprite.setPosition(movedDown());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				rotation = facing::a;
				this->sprite.setPosition(movedLeft());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				rotation = facing::d;
				this->sprite.setPosition(movedRight());
			}
			rotate();
		}
		//reloading
		{
			if (getShootIndicator() <= shoot::READY) { this->setShootIndicator(this->getShootIndicator() + 1); }
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