#ifndef PATH_FINDER
#define PATH_FINDER

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>

#include <SFML/Graphics.hpp>


struct Node {
    sf::Vector2f position;
    float g_score;
    float f_score;
    Node* parent;

    Node(sf::Vector2f position, float g_score, float f_score, Node* parent){
        this->position = position;
        this->g_score = g_score;
        this->f_score = f_score;
        this->parent = parent;
    }

    ~Node()= default;
};

// This struct is used to hash sf::Vector2f objects.
struct Vector2fHash {
    std::size_t operator()(const sf::Vector2f& v) const {
        std::size_t h1 = std::hash<float>{}(v.x);
        std::size_t h2 = std::hash<float>{}(v.y);
        return h1 ^ (h2 << 1);
    }
};

// This function takes in a vector of available positions, a start position,
// and an end position. It returns a vector of positions that represent the
// shortest path between the start and end positions.
std::vector<sf::Vector2f> find_path(std::vector<sf::Vector2f> &available_positions, sf::Vector2f start_position, sf::Vector2f end_position);

#endif