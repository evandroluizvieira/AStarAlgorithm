#ifndef ASTARALGORITHM_HPP
#define ASTARALGORITHM_HPP

#include "Matrix.hpp"

#include <cmath>
#include <vector>

/*
 * @brief A class representing a 2D position with x and y coordinates.
 */
class Position2D{
	public:
		/*
		 * @brief Constructor for creating a Position2D object with the specified x and y coordinates.
		 *
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 */
		Position2D(int x, int y);

		/*
		 * @brief Virtual Destructor.
		 */
		virtual ~Position2D();

	public:
		unsigned int x;
		unsigned int y;
};

/*
 * @brief A class representing a node in the A* algorithm.
 */
class Node : public Position2D{
	friend class AStarAlgorithm;

	public:
		/*
		 * @brief Constructor for creating a Node object with the specified x and y coordinates.
		 *
		 * @param x The x-coordinate of the node.
		 * @param y The y-coordinate of the node.
		 */
		Node(int x, int y);

		/*
		 * @brief Virtual Destructor.
		 */
		virtual ~Node();

		/*
		 * @brief Calculates the heuristic (estimated cost) from this node to the goal node.
		 *
		 * @param goal The goal node.
		 *
		 * @return The heuristic value.
		 */
		double calculateHeuristic(const Node& goal);

		/*
		 * @brief Finds and sets the neighbors of this node in the given grid.
		 *
		 * @param grid The grid representing the map with traversable (false) and non-traversable (true) cells.
		 */
		void getNeighbors(const Matrix<bool>& grid);

	private:
	    double totalEstimatedCost;
	    double costFromStart;
	    double estimatedCostToGoal;

	    Node* neighborNorth;
	    Node* neighborSouth;
	    Node* neighborEast;
	    Node* neighborWest;

	    Node* parent;
};

/*
 * @brief Class implementing the A* Algorithm for finding the shortest path.
 */
class AStarAlgorithm {
	private:
		/*
		 * @brief Private constructor to prevent instantiation.
		 */
		AStarAlgorithm();

	public:
		/*
		 * @brief Virtual Destructor.
		 */
		virtual ~AStarAlgorithm();

		/*
		 * @brief Executes the A* Algorithm on the given grid.
		 *
		 * @param grid The grid representing the map with traversable (false) and non-traversable (true) cells.
		 * @param start The starting node.
		 * @param goal The goal node.
		 *
		 * @return The shortest path from the start to the goal as a vector of positions.
		 */
		static std::vector<Position2D> execute(const Matrix<bool>& grid, const Node& start, const Node& goal);
};

#endif /* ASTARALGORITHM_HPP */
