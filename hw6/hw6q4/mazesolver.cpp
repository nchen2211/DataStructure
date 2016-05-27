#include "mazesolver.h"
#include "mazedisplay.h"
#include "heap.h"
#include <QMessageBox>
#include <cmath>
#include <queue>
#include <stack>
#include <assert.h>
#include <iostream>

using namespace std;


MazeSolver::MazeSolver(Maze * m, MazeDisplay * md)
    : maze(m), display(md)
{}


void MazeSolver::solveByDFSRecursive()
{
    VisitedTracker vt(maze->numRows(), maze->numCols());
    int numSquares = maze->numRows() * maze->numCols();
    std::vector<Direction> parent( numSquares );
    numExplored = 0;

    int r = maze->getStartRow();
    int c = maze->getStartCol();


    // displaying the visited (r,c) and the path
    if(DFSHelper(r,c,vt,parent))
    {
        std::vector<Direction> path;
        std::stack<Direction> st;

        while( r != maze->getStartRow() || c != maze->getStartCol())
        {
            st.push( parent[ squareNumber(r,c) ]);

            switch( st.top() )
            {
                case UP: r++; break; 
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
            }
        }
        while ( ! st.empty() )
        {
            path.push_back(st.top());
            st.pop();
        }

        display->reportSolution(path, vt, numExplored);
        return;
    }

}

bool MazeSolver::DFSHelper(int& r, int& c, VisitedTracker& vt, std::vector<Direction>& parent) 
{

    vt.setVisited(r,c);
    numExplored++;
    int oldR;
    int oldC;


    // base case
    if( r == maze->getGoalRow() && c == maze->getGoalCol() ) 
        return true;

    // to travel UP
    if (maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
    {
        oldR = r - 1;
        oldC = c;
        if (DFSHelper(--r,c,vt,parent)) {
            parent[squareNumber(oldR,oldC)] = UP;
            return true;
        }
        ++r;
    }

    // to travel DOWN
    if (maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c))
    {
        oldR = r + 1;
        oldC = c;
        if(DFSHelper(++r,c,vt,parent)) {
            parent[squareNumber(oldR,oldC)] = DOWN;
            return true;
        }
        --r;
    }

    // to travel LEFT
    if (maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1))
    {
        oldR = r;
        oldC = c - 1;
        
        if(DFSHelper(r,--c,vt,parent)) {
            parent[squareNumber(oldR,oldC)] = LEFT;
            return true;
        }
        ++c;
    }

    // to travel RIGHT
    if (maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1))
    {
        oldR = r;
        oldC = c + 1;

        if(DFSHelper(r,++c,vt,parent)) {
            parent[squareNumber(oldR,oldC)] = RIGHT;
            return true;
        }
        --c;
    }

    return false;

}

int MazeSolver::heuristic(int choice, int r, int c)
{
    if (choice == 1)
        return 0;
    else if (choice == 2)
        return (std::abs((r - maze->getGoalRow()) + (c - maze->getGoalCol())) );
    else if (choice == 3) {
        int power = 2;
        return std::sqrt( ((std::pow((r - maze->getGoalRow()),power)) + std::pow((c - maze->getGoalCol()),power)) );
    }

    return 0;
}

void MazeSolver::solveByAStar(int choice)
{
    // priority is f = g + h (lower f, lower priority)
    MinHeap<std::pair<int,int> > openList(2); // nodes that need to be evaluated
    
    numExplored = 0;
    VisitedTracker vt(maze->numRows(), maze->numCols());
    
    int numSquares = maze->numRows() * maze->numCols();
    std::vector<Direction> parent(numSquares); 

    // f_parent is to keep track of node parent's f value
    std::vector<std::pair <std::pair<int,int> , int> > f_parent (numSquares);

    int r = maze->getStartRow();
    int c = maze->getStartCol();
    f_parent[squareNumber(r,c)] = (std::make_pair(std::make_pair(r,c),0)); // storing g value for (0,0)

    int h; 
    int g = 0;
    
    // push the starting (r,c) to the heap with priority 0
    int f = 0;
    openList.add((std::make_pair(r,c)),f);
  
    
    while (!openList.isEmpty()) 
    {
        std::pair<int,int> current = openList.peek();

        openList.remove();
        r = current.first;
        c = current.second;

    
        if (! vt.isVisited(r,c))
        {
            numExplored++;
            vt.setVisited(r,c);
        } 

        // if the goal is reached, return traced path

        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);

                switch( st.top() )
                {
                    case UP: r++; break;
                    case DOWN: r--; break;
                    case LEFT: c++; break;
                    case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        // if goal hasn't been reached yet
        // North
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            int g_prev = f_parent[squareNumber(r,c)].second;
            g = 10 + g_prev;
            h = heuristic(choice,r-1,c);
            f = g + h;

            openList.add((std::make_pair(r-1,c)),f);
            f_parent[squareNumber(r-1,c)] = (std::make_pair(std::make_pair(r-1,c),f));
            parent[squareNumber(r-1,c)] = UP;
        }
        // South
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c))
        {
            int g_prev = f_parent[squareNumber(r,c)].second;
            g = 10 + g_prev;
            h = heuristic(choice,r+1,c);
            f = g + h;

            openList.add((std::make_pair(r+1,c)),f);
            f_parent[squareNumber(r+1,c)] = (std::make_pair(std::make_pair(r+1,c),f));
            parent[squareNumber(r+1,c)] = DOWN;
        }
        // West
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            int g_prev = f_parent[squareNumber(r,c)].second;
            g = 10 + g_prev;
            h = heuristic(choice,r,c-1);
            f = g + h;

            openList.add((std::make_pair(r,c-1)),f);
            f_parent[squareNumber(r,c-1)] = (std::make_pair(std::make_pair(r,c-1),f));
            parent[squareNumber(r,c-1)] = LEFT;
           
        }
        // East
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r,c+1) )
        {
            int g_prev = f_parent[squareNumber(r,c)].second;
            g = 10 + g_prev;
            h = heuristic(choice,r,c+1);
            f = g + h;

            openList.add((std::make_pair(r,c+1)),f);
            f_parent[squareNumber(r,c+1)] = (std::make_pair(std::make_pair(r,c+1),f));
            parent[squareNumber(r,c+1)] = RIGHT;
        }
    }
}


void MazeSolver::solveByDFSIterative()
{
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::stack<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while( ! q.empty() )
    {
        std::pair<int, int> v = q.top();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}

void MazeSolver::solveByBFS()
{
    /* In lecture on Tuesday March 22, we had a graph
       with vertices numbered 0 to n-1, inclusive.
       Instead, we have vertices with two numbers,
       row and col, in the range:
       [0, maze->numRows()-1], [0, maze->numCols() -1 ]
       to assign each a unique number [0, maze->numRows() * maze->numCols() -1]
       we will say that maze square (r,c) is really number
       r * maze->numCols() + c
    */
       
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while( ! q.empty() )
    {
       // std::cout << "r: " << r << "c: " << c <<std::endl;
        std::pair<int, int> v = q.front();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */

        // when arrived at the goal(r,c)
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);

                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}


int MazeSolver::squareNumber(int r, int c) const
{
    return maze->numCols() * r + c;
}