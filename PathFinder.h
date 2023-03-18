+#pragma once
#include <iostream>
#include <list>
#include <unordered_set>
#include "Map.h"

class Hash {
public:
	// position is returned as hash function
	size_t operator()(const Node& n) const
	{
		return (n.position.x + n.position.y);
	}
};

class PathFinder {
private:
	std::list<Node> grid;
public:
	PathFinder(Map& map) {
		for (auto& [position, walkable] : map.getSceneMap()) {
			bool walk;
			if (walkable) { walk = false; }
			else walk = true;
			Node node(walk, position);
			grid.push_back(node);
			//std::cout << grid.find(node).position.x << " \n";
		}
	}
	~PathFinder() {}

	std::list<Node> getNeighbours(Node& node) {
		Position d = { node.position.x + 40 ,node.position.y };
		Position a = { node.position.x - 40 , node.position.y };
		Position w = { node.position.x ,node.position.y - 40 };
		Position s = { node.position.x, node.position.y + 40 };

		auto iteratorUp = find_if(grid.begin(), grid.end(), [&](const Node& n) { return n.position == w; });
		auto iteratorDown = find_if(grid.begin(), grid.end(), [&](const Node& n) { return n.position == s; });
		auto iteratorLeft = find_if(grid.begin(), grid.end(), [&](const Node& n) { return n.position == a; });
		auto iteratorRight = find_if(grid.begin(), grid.end(), [&](const Node& n) { return n.position == d; });

		Node up, down, left, right;
		std::list<Node> neighbours;

		if (iteratorUp != grid.end()) {
			up = *iteratorUp;
			neighbours.push_back(up);
		}
		if (iteratorDown != grid.end()) {
			down = *iteratorDown;
			neighbours.push_back(down);
		}
		if (iteratorLeft != grid.end()) {
			left = *iteratorLeft;
			neighbours.push_back(left);
		}
		if (iteratorRight != grid.end()) {
			right = *iteratorRight;
			neighbours.push_back(right);
		}
		return neighbours;
	}

	std::vector<Position> findPath(Position& startPosition, Position& endPosition) {

		std::vector<Position> path;

		Position desiredPosition = endPosition;
		Position currentPosition = Position((startPosition.x / 40) * 40, (startPosition.y / 40) * 40);

		//����� Node � grid �� ��������� �������
		//����� Node � grid �� �������� �������
		Node startNode = *find_if(grid.begin(), grid.end(), [&](const Node& n) { return n.position == startPosition; });
		Node targetNode = *find_if(grid.begin(), grid.end(), [&](const Node& n) { return n.position == endPosition; });

		//��������� ��� ��� �� �����
		if (std::find(grid.begin(), grid.end(), targetNode)->walkable == false) {
			std::cout << "- DesiredPosition is a wall!\n";
			throw;

		}
		if (std::find(grid.begin(), grid.end(), startNode)->walkable == false) {
			std::cout << " - CurrentPosition is a wall!\n";
			throw;
		}


		//OpenSet, ClosedSet 
		std::list<Node> openSet; // the set of Nodes to be evaluated
		std::unordered_set <Node, Hash> closedSet; // the set of Nodes, evaluated

		//add the start Node to openSet
		openSet.push_back(startNode);


		while (openSet.size() > 0) {
			//current - node in OPEN set with LOWEST f-Cost;
			Node currentNode = openSet.front();
			for (auto& node : openSet) {
				if (node.fCost() < currentNode.fCost() ||
					node.fCost() == currentNode.fCost() &&
					node.hCost < currentNode.hCost) {
					currentNode = node;
				}
			}

			//remove CurrentNode from openSet
			openSet.remove(currentNode);
			//add to ClosedSet
			closedSet.emplace(currentNode);


			if (currentNode == targetNode) {
				path = retracePath(startNode, targetNode);
				return path;
			}

			//where can currenNode go?
			//4 positions - up, down, left, right
			//evaluate them, choose best

			//std::cout << "currentNode posX: " << currentNode.position.x << " PosY: " << currentNode.position.y << "\n";
			for (auto& neighbourNode : getNeighbours(currentNode)) {

				//std::cout << "neighborNode posX: " << neighbourNode.position.x << " PosY: " << neighbourNode.position.y << "\n";
				//count() ~= contains()
				if (!neighbourNode.walkable || closedSet.find(neighbourNode) != closedSet.end()) {
					continue;
				}
				int newMovementCost = currentNode.gCost + Node::getDistance(currentNode, neighbourNode);

				if (newMovementCost < neighbourNode.gCost || std::find(openSet.begin(), openSet.end(), neighbourNode) == openSet.end()) {
					neighbourNode.gCost = newMovementCost;
					neighbourNode.hCost = Node::getDistance(neighbourNode, targetNode);

					//� ������ Node ���� ���� Node parent
					// class Node {
					// int a;
					// Node parent; - ������ �� ������ Node
					// }
					// � C# ���� �� � ����� ������� ��� neighbourNode.parent = currentNode, � �� ������� ���:
					//neighborNode.parent = currentNode
					// � ���������� ������ ���:
					std::find(grid.begin(), grid.end(), neighbourNode)->parent = &*std::find(grid.begin(), grid.end(), currentNode);

					if (std::find(openSet.begin(), openSet.end(), neighbourNode) == openSet.end()) {
						openSet.push_back(neighbourNode);
					}
				}
			}
		}
	}

	std::vector<Position> retracePath(Node& startNode, Node& endNode) {
		std::vector<Position> path;
		Node currentNode = *std::find(grid.begin(), grid.end(), endNode);
		Node frontNode = *std::find(grid.begin(), grid.end(), startNode);


		while (currentNode != frontNode) {
			path.push_back(currentNode.position);
			currentNode = *currentNode.parent;
			//std::cout << "CurrentNode posX: " << currentNode.position.x << " PosY: " << currentNode.position.y << "\n";
		}
		std::reverse(path.begin(), path.end());
		return path;
	}
};