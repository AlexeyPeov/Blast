+#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Collider.h"



class Wall {
private:
	sf::Sprite sprite = sf::Sprite();
	int hp = 0;
	bool life = 0;

public:
	Wall(sf::Sprite& sprite, int hp, sf::Vector2f position) {
		this->hp = hp;
		this->life = (hp > 0);
		this->sprite = sprite;
		this->sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
		this->sprite.setPosition(position);
	}
	~Wall() {}
	//get
	sf::Sprite getSprite() {
		return this->sprite;
	}
	int getHp() {
		return this->hp;
	}
	bool getLife() {
		return this->life;
	}
	sf::Vector2f getPosition() {
		return this->sprite.getPosition();
	}
	//set
	void setSprite(sf::Sprite& sprite) {
		this->sprite = sprite;
	}
	void setTexture(sf::Texture& texture) {
		this->sprite.setTexture(texture);
	}
	void setHp(int hp) {
		this->hp = hp;
	}

	//collider
	Collider getCollider = collider();
	Collider collider() {
		return Collider(this->sprite);
	}

	//methods

	void draw(sf::RenderWindow& window) {
		window.draw(this->sprite);
	}
};