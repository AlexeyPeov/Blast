+#pragma once
#include <SFML/Graphics.hpp>
struct Position {


	int x = 0, y = 0;

	/*friend bool operator != (Position& a, Position& b) {
		if (a.x != b.x || a.y != b.y) { return true; }
		else if (a.x != b.x && a.y != b.y) { return true; }
		return false;
	}*/
	friend bool operator < (const Position& a, const Position& b) {
		if (a.y < b.y) { return true; }
		else if (a.y > b.y) { return false; }
		else if (a.x < b.x) { return true; }
		return false;
	}
	friend bool operator > (const Position& a, const Position& b) {
		if (a.y > b.y) { return true; }
		else if (a.y > b.y) { return false; }
		else if (a.x > b.x) { return true; }
		return false;
	}
	friend bool operator == (const Position& a, const Position& b) {
		if (a.x == b.x && a.y == b.y) { return true; }
		else return false;
	}

	bool operator == (Position& b) {
		if (this->x == b.x && this->y == b.y) { return true; }
		else return false;
	}

	Position operator - (Position& other) {
		return Position(this->x - other.x, this->y - other.y);
	}

	bool operator != (Position& other) {
		if (this->x != other.x || this->y != other.y) { return true; }
		else if (this->x != other.x && this->y != other.y) { return true; }
		return false;
	}


	Position(int x, int y) {
		this->x = x, this->y = y;
	}
	Position() {}
	~Position() {}

	static sf::Vector2f toVector2f(Position pos) {
		return sf::Vector2f(pos.x, pos.y);
	}
};