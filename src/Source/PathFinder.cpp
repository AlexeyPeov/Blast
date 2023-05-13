#include "../Headers/PathFinder.h"

std::vector<sf::Vector2f> find_path(std::vector<sf::Vector2f> &available_positions, sf::Vector2f start_position, sf::Vector2f end_position) {
    // Create a priority queue to keep track of the nodes that need to be explored.
    auto cmp = [](Node *n1, Node *n2) { return n1->f_score > n2->f_score; };
    std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)> open_list(cmp);

    // Create a hash table to keep track of the nodes that have already been explored.
    std::unordered_set<sf::Vector2f, Vector2fHash> closed_list;

    // Create the starting node and add it to the priority queue.
    Node start_node(start_position, 0.f, 0.f, nullptr);
    start_node.f_score = std::sqrt(
            std::pow(end_position.x - start_position.x, 2) + std::pow(end_position.y - start_position.y, 2));
    open_list.push(&start_node);

    // Loop until there are no more nodes to explore.
    while (!open_list.empty()) {
        // Get the node with the lowest f_score from the priority queue.
        Node *current_node = open_list.top();
        open_list.pop();

        // If we have reached the end position, reconstruct and return the path.
        if (current_node->position == end_position) {
            std::vector<sf::Vector2f> path;
            while (current_node != nullptr) {
                path.push_back(current_node->position);
                current_node = current_node->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Add the current node to the closed list.
        closed_list.insert(current_node->position);

        // Loop through all of the neighbors of the current node.
        for (auto &neighbor: available_positions) {
            // If we have already explored this neighbor, skip it.
            if (closed_list.find(neighbor) != closed_list.end()) {
                continue;
            }

            // Calculate the tentative g_score for this neighbor.
            float tentative_g_score = current_node->g_score + std::sqrt(
                    std::pow(neighbor.x - current_node->position.x, 2) +
                    std::pow(neighbor.y - current_node->position.y, 2));

            // Create a new node for this neighbor.
            Node neighbor_node(neighbor, tentative_g_score, 0.f, current_node);
            neighbor_node.f_score = tentative_g_score + std::sqrt(
                    std::pow(end_position.x - neighbor.x, 2) + std::pow(end_position.y - neighbor.y, 2));

            // Check if this neighbor is already in the priority queue.
            bool neighbor_is_better = false;
            auto copy_of_open_list = open_list;
            while (!copy_of_open_list.empty()) {
                auto &node = copy_of_open_list.top();
                if (node->position == neighbor) {
                    if (node->g_score > tentative_g_score) {
                        node->g_score = tentative_g_score;
                        node->parent = current_node;
                        node->f_score = tentative_g_score + std::sqrt(std::pow(end_position.x - node->position.x, 2) +
                                                                      std::pow(end_position.y - node->position.y, 2));
                    }
                    neighbor_is_better = true;
                    break;
                }
                copy_of_open_list.pop();
            }

            // If this neighbor is not already in the priority queue,
            // add it to the priority queue.
            if (!neighbor_is_better) {
                open_list.push(&neighbor_node);
            }
        }
    }

    return {};
}