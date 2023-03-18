+#pragma once
#include <SFML/Graphics.hpp>
#include "position.h"
class Node {
public:
	bool walkable;
	Position position;
	int gCost = 0, hCost = 0;
	Node* parent;


	Node(bool walkable, Position position) {
		this->walkable = walkable;
		this->position = position;
	}



	Node() {
		walkable = false;
		position = { 0,0 };
		gCost = 0;
		hCost = 0;
	}
	~Node() {}

	int fCost() {
		return gCost + hCost;
	}

	static int getDistance(Node& a, Node& b) {
		int distX = abs(a.position.x - b.position.x);
		int distY = abs(a.position.y - b.position.y);

		return distX + distY;
	}

	bool operator == (const Node& other) {
		if (this->walkable == other.walkable && this->position == other.position) { return true; }
		else return false;
	}

	friend bool operator == (const Node& a, const Node& b) {
		if (a.walkable == b.walkable && a.position == b.position) { return true; }
		else return false;
	}

	/*bool operator != (Node& other) {
		return this->walkable != other.walkable || this->position != other.position;
	}*/

	friend bool operator != (Node& a, Node& other) {
		return a.walkable != other.walkable || a.position != other.position;
	}

};