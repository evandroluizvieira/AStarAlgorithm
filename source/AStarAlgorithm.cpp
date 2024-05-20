#include <algorithm>
#include <limits>
#include <list>
#include <vector>
#include "AStarAlgorithm.hpp"

using std::min;
using std::numeric_limits;
using std::size_t;
using std::vector;

Position2D::Position2D(int x, int y) :
	x(x), y(y){

}

Position2D::~Position2D(){

}

Node::Node(int x, int y) :
	Position2D(x, y), totalEstimatedCost(0.0), costFromStart(0.0), estimatedCostToGoal(0.0),
	neighborNorth(nullptr), neighborSouth(nullptr), neighborEast(nullptr), neighborWest(nullptr), parent(nullptr){

}

Node::~Node(){

}

double Node::calculateHeuristic(const Node& goal){
	return ::abs(x - goal.x) + ::abs(y - goal.y);
}

void Node::getNeighbors(const Matrix<bool>& grid){
    if (x > 0 && !grid(x - 1, y)) {
        neighborNorth = new Node(x - 1, y);
        neighborNorth->parent = this;
    }
    if (x < grid.getRows() - 1 && !grid(x + 1, y)) {
        neighborSouth = new Node(x + 1, y);
        neighborSouth->parent = this;
    }
    if (y > 0 && !grid(x, y - 1)) {
        neighborWest = new Node(x, y - 1);
        neighborWest->parent = this;
    }
    if (y < grid.getColumns() - 1 && !grid(x, y + 1)) {
        neighborEast = new Node(x, y + 1);
        neighborEast->parent = this;
    }
}

AStarAlgorithm::AStarAlgorithm(){

}

AStarAlgorithm::~AStarAlgorithm(){

}

std::vector<Position2D> AStarAlgorithm::execute(const Matrix<bool>& grid, const Node& start, const Node& goal){
	std::list<Node*> openSet;
	std::vector<Node*> closedSet;
	Matrix<Node*> allNodes(grid.getRows(), grid.getColumns(), nullptr);
	std::vector<Position2D> path;

	Node* startNode = new Node(start.x, start.y);
	startNode->costFromStart = 0;
	startNode->estimatedCostToGoal = startNode->calculateHeuristic(goal);
	startNode->totalEstimatedCost = startNode->estimatedCostToGoal;

	openSet.push_back(startNode);
	allNodes(start.x, start.y) = startNode;

	Node* goalNode = nullptr;

	while (!openSet.empty()) {
		Node* current = openSet.front();
		openSet.pop_front();

		if (current->x == goal.x && current->y == goal.y) {
			goalNode = current;
			break;
		}

		closedSet.push_back(current);

		current->getNeighbors(grid);
		std::vector<Node*> neighbors = {current->neighborNorth, current->neighborSouth, current->neighborEast, current->neighborWest};
		for (Node* neighbor : neighbors) {
			if (neighbor == nullptr || std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
				delete neighbor; // Clean up dynamically allocated neighbor node
				continue;
			}

			double tentative_gScore = current->costFromStart + 1;

			if (allNodes(neighbor->x, neighbor->y) == nullptr || tentative_gScore < neighbor->costFromStart) {
				neighbor->costFromStart = tentative_gScore;
				neighbor->estimatedCostToGoal = neighbor->calculateHeuristic(goal);
				neighbor->totalEstimatedCost = neighbor->costFromStart + neighbor->estimatedCostToGoal;

				if (allNodes(neighbor->x, neighbor->y) == nullptr) {
					auto it = openSet.begin();
					while (it != openSet.end() && (*it)->totalEstimatedCost <= neighbor->totalEstimatedCost) {
						++it;
					}
					openSet.insert(it, neighbor);
					allNodes(neighbor->x, neighbor->y) = neighbor;
				} else {
					delete neighbor; // Clean up dynamically allocated duplicate neighbor node
				}
			} else {
				delete neighbor; // Clean up dynamically allocated duplicate neighbor node
			}
		}
	}

	if (goalNode != nullptr) {
		Node* currentNode = goalNode;
		while (currentNode != nullptr) {
			path.push_back(Position2D(currentNode->x, currentNode->y));
			currentNode = currentNode->parent;
		}
		std::reverse(path.begin(), path.end());
	}

	for (std::size_t i = 0; i < allNodes.getRows(); ++i) {
		for (std::size_t j = 0; j < allNodes.getColumns(); ++j) {
			delete allNodes(i, j);
		}
	}

	return path;
}

