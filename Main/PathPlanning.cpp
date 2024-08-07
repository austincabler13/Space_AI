#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

// RRT* Algorithm Implementation
class Node {
public:
    double x, y;
    Node* parent;
    Node(double x, double y) : x(x), y(y), parent(nullptr) {}
};

class RRTStar {
public:
    RRTStar(double startX, double startY, double goalX, double goalY) :
        startX(startX), startY(startY), goalX(goalX), goalY(goalY) {
        srand(time(nullptr));
        startNode = new Node(startX, startY);
        goalNode = new Node(goalX, goalY);
        nodes.push_back(startNode);
    }

    void run() {
        for (int i = 0; i < maxIterations; ++i) {
            Node* randomNode = getRandomNode();
            Node* nearestNode = getNearestNode(randomNode);
            Node* newNode = steer(nearestNode, randomNode);
            if (newNode) {
                nodes.push_back(newNode);
                if (distance(newNode, goalNode) < threshold) {
                    goalNode->parent = newNode;
                    nodes.push_back(goalNode);
                    break;
                }
            }
        }
    }

    void printPath() {
        Node* node = goalNode;
        while (node) {
            std::cout << "(" << node->x << ", " << node->y << ") <- ";
            node = node->parent;
        }
        std::cout << "START\n";
    }

private:
    Node* startNode;
    Node* goalNode;
    std::vector<Node*> nodes;
    double startX, startY, goalX, goalY;
    const int maxIterations = 10000;
    const double stepSize = 1.0;
    const double threshold = 1.0;

    Node* getRandomNode() {
        double x = (double)rand() / RAND_MAX * 100.0;
        double y = (double)rand() / RAND_MAX * 100.0;
        return new Node(x, y);
    }

    Node* getNearestNode(Node* randomNode) {
        Node* nearestNode = nullptr;
        double minDist = INFINITY;
        for (auto node : nodes) {
            double dist = distance(node, randomNode);
            if (dist < minDist) {
                minDist = dist;
                nearestNode = node;
            }
        }
        return nearestNode;
    }

    Node* steer(Node* nearestNode, Node* randomNode) {
        double theta = atan2(randomNode->y - nearestNode->y, randomNode->x - nearestNode->x);
        double newX = nearestNode->x + stepSize * cos(theta);
        double newY = nearestNode->y + stepSize * sin(theta);
        Node* newNode = new Node(newX, newY);
        newNode->parent = nearestNode;
        return newNode;
    }

    double distance(Node* a, Node* b) {
        return sqrt(pow(a->x, b->x) + pow(a->y, b->y));
    }
};

int main() {
    RRTStar rrtStar(0, 0, 90, 90);
    rrtStar.run();
    rrtStar.printPath();
    return 0;
}
