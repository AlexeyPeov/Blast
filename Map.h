+#pragma once
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "position.h"
#include "Node.h"

class Map {
private:
	std::map<Position, int> sceneMap;
	int sizeX = 0, sizeY = 0;
public:
	Map() {}
	Map(std::map<Position, int>& sceneMap, int sizeX, int sizeY) {
		if (sceneMap.size() > 800) {
			throw "invalid size, should be < 800";
		}
		else {
			this->sceneMap = sceneMap;
			this->sizeX = sizeX;
			this->sizeY = sizeY;
			//for (auto& it : this->sceneMap) {
			//	if (it.second == 1 || it.second == 2) {
			//		this->pathMap[it.first] = 0;
			//		//std::cout << "aboba\n";
			//	}
			//	else {
			//		int value = 1;
			//		this->pathMap[it.first] = value;
			//		//std::cout << "aboba2\n";
			//	}
			//}
		}
	}
	~Map() {}

	std::map<Position, int> getSceneMap() {
		return this->sceneMap;
	}

	enum state {
		WALL = 1,
		UNBREAKABLE_WALL = 2,
	};



	Position getRandomPosition() {
		int randX = ((rand() % 1600) / 40) * 40 + 20;
		int randY = ((rand() % 800) / 40) * 40 + 20;
		Position position = { randX,randY };
		//std::cout << randX << " " << randY << "\n";
		if (this->sceneMap.count(position)) {
			if (this->sceneMap.find(position)->second == 0) {
				return position;
			}
		}
		else {
			position = { -1,-1 };
		}
	}
};