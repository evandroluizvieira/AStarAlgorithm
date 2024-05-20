# A* Algorithm

![Logo](https://github.com/evandroluizvieira/AStarAlgorithm/blob/main/resource/Brand.png)

[![C++](https://img.shields.io/badge/C++-004488)](https://cplusplus.com/)
[![BSL1.0 License](https://img.shields.io/badge/License-BSL-green.svg)](https://choosealicense.com/licenses/bsl-1.0/)

## Overview
The A* algorithm, also known as 'A Star Algorithm', is a widely used method for pathfinding in graphs or grids. It works by exploring nodes in a graph based on their cost and heuristic value to find the optimal path from a start node to a goal node. The algorithm iteratively evaluates nodes by considering both the cost of reaching that node from the start and an estimate of the cost to reach the goal from that node. This estimate is provided by a heuristic function. A* selects nodes with the lowest total cost (the sum of the cost from the start and the heuristic estimate to the goal) for further exploration. This process continues until the goal node is reached or no more nodes are available for expansion. A* guarantees finding the optimal path if certain conditions are met, including admissibility of the heuristic function.

## Installation
To get started, clone the repository:
```bash
git clone https://github.com/evandroluizvieira/AStarAlgorithm.git
```

## Usage
Example:
```c++
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
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
    };

    //Print the populated matrix, print 1 for obstacle, 0 for empty space
    cout << "Grid " << grid.getRows() << "x" << grid.getColumns() << endl;
    for(unsigned int i = 0; i < grid.getRows(); ++i){
        for(unsigned int j = 0; j < grid.getColumns(); ++j){
            cout << (grid(i, j) ? "1 " : "0 ");
        }
        cout << endl;
    }

    cout << endl;

    //Define start and goal nodes
    Node start(0, 0);
    Node goal(9, 9);

    //Execute the A* algorithm to find the best path
    vector<Position2D> path = AStarAlgorithm::execute(grid, start, goal);

    //Check if a path was found
    if(path.size() == 0){
        cout << "Can't reach the goal node." << endl;
        return 0;
    }

    //Print the nodes in the path
    cout << "Nodes in the path = " << path.size() << ":" << endl;
    for(const Position2D& pos : path){
        cout << "(" << pos.x << "," << pos.y << ") ";
    }
    cout << endl << endl;

    //Print the best path in the grid (visual representation)
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
```
Output:
```console
Grid 10x10
0 0 0 0 0 0 1 0 0 0 
1 0 0 0 1 0 1 0 0 0 
1 0 0 0 1 0 1 0 1 0 
0 0 0 0 1 1 1 0 1 0 
0 1 1 1 1 0 0 0 0 0 
0 0 0 0 1 0 1 0 1 0 
1 1 0 0 0 0 1 0 0 0 
0 0 0 1 0 1 1 0 1 0 
0 0 1 1 0 0 1 0 1 0 
0 0 0 0 0 1 0 0 1 0 

Nodes in the path = 25:
(0,0) (0,1) (1,1) (2,1) (3,1) (3,0) (4,0) (5,0) (5,1) (5,2) (6,2) (6,3) (6,4) (6,5) (5,5) (4,5) (4,6) (4,7) (5,7) (6,7) (6,8) (6,9) (7,9) (8,9) (9,9) 

Best path in the grid (visual):
X X - - - - - - - - 
- X - - - - - - - - 
- X - - - - - - - - 
X X - - - - - - - - 
X - - - - X X X - - 
X X X - - X - X - - 
- - X X X X - X X X 
- - - - - - - - - X 
- - - - - - - - - X 
- - - - - - - - - X 
```
