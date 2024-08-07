#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

struct Node {
    int x, y;
    float g, h;
    Node* parent;

    float f() const { return g + h; }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

std::vector<Node> aStar(Node start, Node goal, std::vector<std::vector<int>>& grid) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::unordered_map<int, Node> closedList;

    start.g = 0;
    start.h = std::abs(goal.x - start.x) + std::abs(goal.y - start.y);
    openList.push(start);

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (current.x == goal.x && current.y == goal.y) {
            std::vector<Node> path;
            Node* node = &current;
            while (node) {
                path.push_back(*node);
                node = node->parent;
            }
            return path;
        }

        closedList[current.y * grid[0].size() + current.x] = current;

        std::vector<Node> neighbors = {
            {current.x + 1, current.y, 0, 0, &current},
            {current.x - 1, current.y, 0, 0, &current},
            {current.x, current.y + 1, 0, 0, &current},
            {current.x, current.y - 1, 0, 0, &current}
        };

        for (Node& neighbor : neighbors) {
            if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= grid[0].size() || neighbor.y >= grid.size() || grid[neighbor.y][neighbor.x] == 1) {
                continue;
            }

            float tentative_g = current.g + 1;

            if (closedList.find(neighbor.y * grid[0].size() + neighbor.x) != closedList.end() && tentative_g >= closedList[neighbor.y * grid[0].size() + neighbor.x].g) {
                continue;
            }

            neighbor.g = tentative_g;
            neighbor.h = std::abs(goal.x - neighbor.x) + std::abs(goal.y - neighbor.y);
            openList.push(neighbor);
        }
    }

    return {};
}
