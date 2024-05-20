#include "AStarAlgorithm.hpp"
#include "Matrix.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::vector;

/*
 * @brief Main function to demonstrate the A* algorithm on a grid.
 *        Creates a 10x10 grid with obstacles, defines start and goal nodes,
 *        executes the A* algorithm, and prints the best path found.
 */
int main(){
    // Create a 10x10 grid with obstacles
    Matrix<bool> grid = {
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
    };

    // Print the populated matrix, print 1 for obstacle, 0 for empty space
    cout << "Grid " << grid.getRows() << "x" << grid.getColumns() << endl;
    for(unsigned int i = 0; i < grid.getRows(); ++i){
        for(unsigned int j = 0; j < grid.getColumns(); ++j){
            cout << (grid(i, j) ? "1 " : "0 ");
        }
        cout << endl;
    }

    cout << endl;

    // Define start and goal nodes
    Node start(0, 0);
    Node goal(9, 9);

    // Execute the A* algorithm to find the best path
    vector<Position2D> path = AStarAlgorithm::execute(grid, start, goal);

    // Check if a path was found
    if(path.size() == 0){
        cout << "Can't reach the goal node." << endl;
        return 0;
    }

    // Print the nodes in the path
    cout << "Nodes in the path = " << path.size() << ":" << endl;
    for(const Position2D& pos : path){
        cout << "(" << pos.x << "," << pos.y << ") ";
    }
    cout << endl << endl;

    // Print the best path in the grid (visual representation)
    cout << "Best path in the grid (visual):" << endl;
    for(unsigned int i = 0; i < grid.getRows(); ++i){
        for(unsigned int j = 0; j < grid.getColumns(); ++j){
            bool isPath = false;
            for(const Position2D& pos : path){
                if(pos.x == i && pos.y == j){
                    isPath = true;
                    break;
                }
            }

            if(isPath){
                cout << "X ";
            }else{
                cout << "- ";
            }
        }
        cout << endl;
    }

    return 0;
}
