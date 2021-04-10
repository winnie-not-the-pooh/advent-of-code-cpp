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

string program[] =
{
    "E1"
    // input the rest
};

string program_test[]=
{
    "F10",
    "N3",
    "F7",
    "R90",
    "F11"
};

struct Point
{
    float x, y, orientation;
};

int wrapOrientation(int orientation)
{
    if(orientation<0)
    {
        orientation = orientation + 360;
    }
    else if(orientation>=360)
    {
        orientation = orientation - 360;
    }
    return orientation;
}

Point transformPoint(Point p, string dir) // part 1
{
    Point P;
    P.x = p.x;
    P.y = p.y;
    P.orientation = p.orientation;
    
    char direction = dir[0];
    int amount = stoi(dir.substr(1,dir.length()));
    
    if (direction == 'F')
    {
        if (p.orientation == 0)
        {
            direction = 'E';
        }
        else if (p.orientation == 90)
        {
            direction = 'N';
        }
        else if (p.orientation == 180)
        {
            direction = 'W';
        }
        else
            direction = 'S';
    }
    
    if(direction == 'N')
    {
        P.y = p.y+amount;
    }
    else if(direction == 'S')
    {
        P.y = p.y-amount;
    }
    
    else if(direction == 'E')
    {
        P.x = p.x+amount;
    }
    else if(direction == 'W')
    {
        P.x = p.x-amount;
    }
    else if(direction == 'L')
    {
        P.orientation = wrapOrientation(p.orientation+amount);
    }
    else // if(direction == 'R')
    {
        P.orientation = wrapOrientation(p.orientation-amount);
    }
    
    return P;
}

void transformPoint(Point &ship, Point &waypoint, string dir) // part 2
{
    char direction = dir[0];
    int amount = stoi(dir.substr(1,dir.length()));
    
    float x = waypoint.x;
    float y = waypoint.y;
    
    if(direction =='N'|| direction =='E' || direction =='S' || direction =='W')
    {
        waypoint = transformPoint(waypoint, dir);
    }
    else if (direction == 'R' || direction == 'L')
    {
        if (direction == 'R')
        {
            amount = 360-amount;
        }
        
        float amount_rad = amount*(M_PI/180);
        
        waypoint.x = x*cos(amount_rad) - y*sin(amount_rad);
        waypoint.y = x*sin(amount_rad) + y*cos(amount_rad);
    }
    else // F
    {
        ship.x = x*amount + ship.x;
        ship.y = y*amount + ship.y;
    }
    
    return;
}

int ManhattanDist(Point p)
{
    return(abs(p.x)+abs(p.y));
}

void PrintPoint(Point p)
{
    cout << "(" << p.x << "," << p.y << ")\n";// orient: " << p.orientation << endl;
    return;
}

void FirstPart()
{
    unsigned long nRows = sizeof(program)/sizeof(program[0]);

    Point p_start;
    p_start.x=0;
    p_start.y=0;
    p_start.orientation = 0;
    
    Point p;
    p=p_start;
    
    for(int i=0; i<nRows; i++)
    {
        p = transformPoint(p, program[i]);
    }
    
    printf("The Manhattan distance of the final point is: %i\n", ManhattanDist(p));
    
    return;
}

void SecondPart()
{
    unsigned long nRows = sizeof(program)/sizeof(program[0]);

    Point ship; // absolute coordinates
    ship.x = 0;
    ship.y = 0;
    ship.orientation = 0; // not used in part 2
    
    Point waypoint; // always WRT to ship
    waypoint.x=10;
    waypoint.y=1;
    waypoint.orientation = 0; // not used in part 2
    
    for(int i=0; i<nRows; i++)
    {
        transformPoint(ship, waypoint, program[i]);
    }
    
    printf("The Manhattan distance of the final point is: %i\n", ManhattanDist(ship));
    
    return;
}

int main()
{
    FirstPart();
    SecondPart();
    return 0;
}
