+#include "EnemyTank.h"


/*
void EnemyTank::update() {

	if (this->health > 0) {


		//reloading
		{
			if (shootTimer < 30) { shootTimer++; }
		}
	}
}

void EnemyTank::draw(sf::RenderWindow& window) {
	if (this->health > 0) {
		window.draw(this->textureSprite);
	}
}

void EnemyTank::rotate() {
	this->textureSprite.setRotation(currently * 90);
}


bool EnemyTank::ableToShoot() {
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

void EnemyTank::deployAI(Tank &tank) {
	//roam randomly
	//roam to last seen pos of player
	//attack player
}

void EnemyTank::roam(Map& map) {
	if (this->health > 0) {
		if (this->path.empty()) {
			Position rand = map.getRandomPosition();
			//std::cout << "xer\n";
			if (map.getSceneMap().count(rand)) {
				if (this->position.x != rand.x || this->position.y != rand.y) {
					this->path = findPath(rand, map);
					//std::cout << "xer1\n";
				}
			}
			//����� ����������� ����, ���� �� ���������
			//���� ������, ����� ������ �������
		}
		move();
	}
}

void EnemyTank::chase(Tank &tank) {

}

void EnemyTank::move() {

	if (this->path.empty()) { return; }

	Position thisPosition = { (int)this->position.x, (int)this->position.y};
	Position nextPosition = this->path.at(0);

		if (thisPosition != nextPosition) {

			Position whereToMove = nextPosition - thisPosition;

			int w = -20, s = 20, a = -20, d = 20;

			if(whereToMove.x <= 40 && whereToMove.x > 0) {
				currently = facing::d;
				this->position.x += d;
				this->textureSprite.setPosition(this->position.x, this->position.y);
			}
			if (whereToMove.x >= -40 && whereToMove.x < 0) {
				currently = facing::a;
				this->position.x += a;
				this->textureSprite.setPosition(this->position.x, this->position.y);

			}
			if (whereToMove.y <= 40 && whereToMove.y > 0) {
				currently = facing::s;
				this->position.y += s;
				this->textureSprite.setPosition(this->position.x, this->position.y);
			}
			if (whereToMove.y >= -40 && whereToMove.y < 0) {
				currently = facing::w;
				this->position.y += w;
				this->textureSprite.setPosition(this->position.x, this->position.y );
			}
			rotate();
			thisPosition = { (int)this->textureSprite.getPosition().x, (int)this->textureSprite.getPosition().y };
		}
		else {
			std::cout << "came\n";
			path.erase(this->path.begin());
			if(!this->path.empty()) {
				nextPosition = this->path.at(0);
			}
			else return;
		}

}

std::vector<Position> EnemyTank::findPath(Position& endPosition, Map& map) {

	std::vector<Position> path;

	Position desiredPosition = endPosition;
	Position currentPosition = { (int)this->position.x, (int)this->position.y};

	if (map.getSceneMap().find(desiredPosition)->second > 0) {
		std::cout << "- DesiredPosition is a wall!\n";
		throw;

	}
	if (map.getSceneMap().find(currentPosition)->second > 0) {
		std::cout << " - CurrentPosition is a wall!\n";
		throw;
	}


	Node startNode(true, currentPosition);
	Node targetNode(true, desiredPosition);

	std::map<Position, Node> openSet;
	std::map<Position, Node> closedSet;


	//map.first == map.key
	//map.second == map.value

	openSet[currentPosition] = startNode;

	while (openSet.size() > 0) {
		Node currentNode = openSet[currentPosition];
		for (auto& pos : openSet) {
			if (pos.second.fCost() < currentNode.fCost() ||
				pos.second.fCost() == currentNode.fCost() &&
				pos.second.hCost < currentNode.hCost) {
				currentNode = pos.second;
			}
		}

		openSet.erase(currentNode.position);
		closedSet[currentNode.position] = currentNode;


		if (currentNode == targetNode) {
			path = Node::retracePath(startNode,closedSet.find(targetNode.position)->second, closedSet);
			return path;
		}

		for (auto& neighbour : map.getNeighbours(currentNode)) {
			//count() ~= contains()
			if (!neighbour.second.walkable || closedSet.count(neighbour.first)) {
				continue;
			}
			int newMovementCost = currentNode.gCost + Node::getDistance(currentNode, neighbour.second);

			if (newMovementCost < neighbour.second.gCost || !openSet.count(neighbour.first)) {
				neighbour.second.gCost = newMovementCost;
				neighbour.second.hCost = Node::getDistance(neighbour.second, targetNode);
				neighbour.second.parent = currentNode.position;

				if (!openSet.count(neighbour.first)) {
					openSet[neighbour.first] = neighbour.second;
				}
			}
		}
	}
}
*/