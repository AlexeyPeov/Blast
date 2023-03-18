+#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Collider.h"
#include <math.h>

class Missile {
private:
	int movementSpeed = 0;
	sf::Sprite sprite;
	bool life;
	float rotation = 0;
	float dx, dy;


public:
	Missile(sf::Sprite& sprite, float rotation, sf::Vector2f position, int movementSpeed) {
		this->movementSpeed = movementSpeed;
		this->life = true;
		this->sprite = sprite;
		this->rotation = rotation;
		this->sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
		this->setPosition(position);
		this->sprite.setRotation(rotation);

		float xToRad = this->getRotation() * 3.14159 / 180;


		this->dx = this->movementSpeed * sin(xToRad);
		this->dy = this->movementSpeed * cos(xToRad);
	}

	~Missile() {}

	enum facing {
		w = 0,
		d = 1,
		a = 3,
		s = 2,
	};

	//get
	int getMovementSpeed() {
		return this->movementSpeed;
	}
	bool getLife() {
		return this->life;
	}
	sf::Sprite getSprite() {
		return this->sprite;
	}
	int getRotation() {
		return this->rotation;
	}
	sf::Vector2f getPosition() {
		return this->sprite.getPosition();
	}

	//set
	void setMovementSpeed(int ms) {
		this->movementSpeed = ms;
	}
	void setSprite(sf::Sprite& spr) {
		this->sprite = spr;
	}
	void setLife(bool life) {
		this->life = life;
	}
	void setRotation(int rotation) {
		this->rotation = rotation;
	}
	void setPosition(sf::Vector2f pos) {
		this->sprite.setPosition(pos);
	}



	sf::Vector2f moved() {
		return sf::Vector2f(sprite.getPosition().x + this->dx, sprite.getPosition().y - this->dy);
	}


	void update() {
		{
			this->setPosition(moved());

			if (
				this->getSprite().getPosition().x > 1600 ||
				this->getSprite().getPosition().x < 0 ||
				this->getSprite().getPosition().y > 800 ||
				this->getSprite().getPosition().y < 0
				) {
				this->life = false;
			}
		}
	}

	Collider getCollider = collider();
	Collider collider() { return Collider(this->sprite); }

	void draw(sf::RenderWindow& window) {
		window.draw(this->getSprite());
	}

	void rotate() {
		this->sprite.setRotation(rotation);
	}

};