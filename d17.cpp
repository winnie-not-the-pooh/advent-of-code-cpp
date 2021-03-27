#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <iterator>
#include <cmath>
#include <math.h>

using namespace std;

/*string program[]=
{
    ".#.",
    "..#",
    "###"
};*/

string program[]=
{
    "..#....#",
    "##.#..##",
    ".###....",
    "#....#.#",
    "#.######",
    "##.#....",
    "#.......",
    ".#......",
};

struct Point
{
    int x, y, z,w;
    bool bActive = 0;
};

struct comparePoints
{
    bool operator()(const Point & l, const Point & r)
    // https://stackoverflow.com/questions/11181760/implementing-operator-for-x-y-z-coordinate/11181770
    {
        if (l.w != r.w)
            return l.w < r.w;
        else if (l.z != r.z)
            return l.z < r.z;
        else if (l.x != r.x)
            return l.x < r.x;
        else
            return l.y < r.y;
    }
};

void PrintPoint(Point p)
{
    cout << p.x << "," << p.y << "," << p.z << "," << p.w << ": "<< p.bActive <<"\n";
    return;
}

void readInput(int nRows,  unsigned long nLength, vector<Point> &state)
{
    for(int i =0;i<nRows;i++)
    {
        for (int j=0;j<nLength;j++)
        {
            Point p;
            p.x=j;
            p.y=i;
            p.z=0;
            p.w=0;
            
            p.bActive = (program[i][j]=='#'?1:0);
            state.push_back(p);
        }
    }
    return;
}

void printVec(vector<Point> vec)
{
    for (int i =0 ; i<vec.size();i++ )
        PrintPoint(vec[i]);
    return;
}

bool getActiveStatus(Point p, vector<Point> state)
{
    for(int i =0; i<state.size();i++)
    {
        Point pp = state[i];
        if(pp.x==p.x && pp.y==p.y && pp.z==p.z && pp.w==p.w)
        {
            return pp.bActive;
        }
    }
    return 0;
}

void getNeighbours(Point p, vector <Point> &neighbours, vector<Point> state)
{
    int x = p.x;
    int y = p.y;
    int z = p.z;
    int w = p.w;
    
    for (int h = -1; h<2; h++)
    {
        for (int i = -1; i<2; i++)
        {
            for (int j = -1; j<2; j++)
            {
                for (int k = -1; k<2; k++)
                {
                    if(i==0 && j==0 && k==0 && h==0)
                        continue;
                    Point newPoint;
                    newPoint.x = x+i;
                    newPoint.y = y+j;
                    newPoint.z = z+k;
                    newPoint.w = w+h;
                    newPoint.bActive = getActiveStatus(newPoint, state);
                    neighbours.push_back(newPoint);
                }
            }
        }
    }
    
    return;
}

void transformPoint(Point p, vector <Point> neighbours, vector <Point> &nextState)
{
    unsigned long nActive = 0;
    for (int i =0; i< neighbours.size(); i++)
    {
        if(neighbours[i].bActive==1)
        {
            nActive++;
        }
    }
    
    Point transformedPt = p;
    
    if(p.bActive==1)
    {
        if (nActive!=2 && nActive!=3)
        {
            transformedPt.bActive=0;
        }
    }
    else
    {
        if (nActive==3)
        {
            transformedPt.bActive=1;
        }
    }

    nextState.push_back(transformedPt);
    return;
}

unsigned int nActiveCells(vector<Point> state)
{
    unsigned int nActive = 0;
    for(int i =0; i< state.size(); i++)
    {
        Point p = state[i];
        if(p.bActive==1)
            nActive++;
    }
    
    return nActive;
}

int main()
{
    int nRows =  sizeof(program)/sizeof(program[0]);
    unsigned long nLength = program[0].length();
    
    vector<Point> state;
    
    readInput(nRows, nLength, state);
    
    for(int c=1; c<7; c++)
    {
        cout << "starting cycle " << c << "...\n";
        
        vector<Point> nextState;
        
        // get all possible affected points
        set<Point,comparePoints> affectedPts;
        for(int s=0; s<state.size(); s++)
        {
            Point p = state[s];
            
            for (int h=-1; h<2; h++)
            {
                for (int i = -1; i<2; i++)
                {
                    for (int j = -1; j<2; j++)
                    {
                        for (int k = -1; k<2; k++)
                        {
                            Point np;
                            np.x = p.x+i;
                            np.y = p.y+j;
                            np.z = p.z+k;
                            np.w = p.w+h;
                            affectedPts.insert(np);
                        }
                    }
                }
            }
        }
        
        set<Point>::iterator setIt = affectedPts.begin();
        while(setIt!=affectedPts.end()) // for each affected pt,
        {
            Point p = *setIt;
            p.bActive = getActiveStatus(p, state);
            
            vector <Point> neighbours;
            getNeighbours(p, neighbours, state);
            transformPoint(p, neighbours, nextState); // get new transformed pt, save in vector nextState
            setIt++;
        }
        
        state = nextState; // save next state into state
        printf("Number of active cubes: %i\n",nActiveCells(state));
    }
    return 0;
}
