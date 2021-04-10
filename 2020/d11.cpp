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

using namespace std;

string program[] =
{
    "LLLLL.LLLLLLL.LLLLLL.L.LLLL..LLLL.LLLLLLLLL.LLLLLLLL.LLLLLLLLLLLLL.L.LLLLLLLLLLLLLL.LLLLLL"
    // input the rest
};

string program_test[]=
{
    "L.LL.LL.LL",
    "LLLLLLL.LL",
    "L.L.L..L..",
    "LLLL.LL.LL",
    "L.LL.LL.LL",
    "L.LLLLL.LL",
    "..L.L.....",
    "LLLLLLLLLL",
    "L.LLLLLL.L",
    "L.LLLLL.LL"
};

string program_test1[]=
{
    ".......#.",
    "...#.....",
    ".#.......",
    ".........",
    "..#L....#",
    "....#....",
    ".........",
    "#........",
    "...#....."
};

string program_test2[]=
{
    ".............",
    ".L.L.#.#.#.#.",
    "............."
};

string program_test3[]
{
    ".##.##.",
    "#.#.#.#",
    "##...##",
    "...L...",
    "##...##",
    "#.#.#.#",
    ".##.##."
};

struct Point
{
    int x, y;
};

Point getPoint(Point p, string dir)
{
    Point P;
    P.x = p.x;
    P.y = p.y;
    
    if(dir[0] == 'N')
    {
        P.y = p.y-1;
    }
    else if(dir[0] == 'S')
    {
        P.y = p.y+1;
    }
    
    if(dir[0] == 'E' || dir[1] == 'E') // if dir in (E ,SE , NE)
    {
        P.x = p.x+1;
    }
    else if(dir[0] == 'W' || dir[1] == 'W') // if dir in (W ,SW , NW)
    {
        P.x = p.x-1;
     }
    
    return P;
}

bool PointExists(Point p, string dir, unsigned long nRows, unsigned long nCols)
{
    if(dir=="N")
    {
        return (p.y==0?false:true);
    }
    else if(dir =="S")
    {
        return (p.y==nRows-1?false:true);
    }
    else if(dir == "E")
    {
        return (p.x==nCols-1?false:true);
    }
    else if(dir == "W")
    {
        return (p.x==0?false:true);
    }
    else if(dir == "NW")
    {
        return (p.y==0||p.x==0?false:true);
    }
    else if(dir == "NE")
    {
        return(p.y==0||p.x==nCols-1?false:true);
    }
    else if(dir == "SE")
    {
        return (p.y==nRows-1||p.x==nCols-1?false:true);
    }
    else // SW
        return (p.y==nRows-1||p.x==0?false:true);
}

bool isOccupied(char c)
{
    return(c=='#');
}

bool isEmpty(char c)
{
    return(c=='L');
}

bool isFloor(char c)
{
    return(c=='.');
}

void PrintPoint(Point p)
{
    cout << "(" << p.x << "," << p.y << ")" << endl;
    return;
}

vector <Point> getAdjacentPoints(Point pt, unsigned long nCols, unsigned long nRows)
{
    string directions[] = {"N", "S", "E", "W", "NE", "NW", "SE", "SW"};
    int nDirections = sizeof(directions)/sizeof(directions[0]);
    
    vector <Point> adjacentPts;
    
    for(int i=0; i<nDirections; i++)
    {
        string dir = directions[i];
        if(PointExists(pt, dir, nRows, nCols))
        {
            adjacentPts.push_back(getPoint(pt, dir));
        }
    }
    return adjacentPts;
}

void getFirstSeatInDir(Point pt, unsigned long nCols, unsigned long nRows, string curr_state[], vector <Point> *firstSeats, string dir)
// gets first available seat in direction specified and pushes it to vector firstSeats
{
    char point_value;
    
    Point p = pt;
    do
    {
        p = getPoint(p, dir);
        point_value = curr_state[p.y][p.x];
    } while(PointExists(p, dir, nRows, nCols)&&isFloor(point_value));
    if(!isFloor(point_value))
    {
        firstSeats->push_back(p);
    }
    return;
}

vector <Point> getFirstSeats(Point pt, unsigned long nCols, unsigned long nRows, string curr_state[])
//returns vector of available seats in all directions
{
    vector <Point> firstSeats;
    string directions[] = {"N", "S", "E", "W", "NE", "NW", "SE", "SW"};
    int nDirections = sizeof(directions)/sizeof(directions[0]);
    
    for(int i=0; i<nDirections; i++)
    {
        string dir = directions[i];
        if(PointExists(pt, dir, nRows, nCols))
        {
            getFirstSeatInDir(pt, nCols, nRows, curr_state, &firstSeats,dir);
        }
    }
    return firstSeats;
}

void PrintPointVec(vector<Point> pvec)
{
    cout << "Printing point vector: " << endl;
    for(vector<Point>::const_iterator i = pvec.begin(); i != pvec.end(); ++i)
        PrintPoint(*i);
    return;
}

unsigned long NumOccupiedSeats(Point p, string curr_state[], unsigned long nRows, unsigned long nCols, vector <Point> Pts)
{
    unsigned long num_occupied_seats = 0;
    for(vector<Point>::const_iterator i = Pts.begin(); i != Pts.end(); ++i)
    {
        Point p = *i;
        if(isOccupied(curr_state[p.y][p.x]))
            num_occupied_seats++;
    }
    return num_occupied_seats;
}

void StepForward(string curr_state[], string next_state[], unsigned long nRows, unsigned long nCols)
{
    for (int j =0; j< nRows; j++)
    {
        string row = "";
        
        for (int i =0; i<nCols; i++)
        {
            Point currPoint;
            currPoint.x = i;
            currPoint.y= j;

            char seat_state = curr_state[j][i];

            //vector <Point> Pts = getAdjacentPoints(currPoint, nCols, nRows); // part 1
            vector <Point> Pts = getFirstSeats(currPoint, nCols, nRows, curr_state);
            unsigned long num_occupied = NumOccupiedSeats(currPoint, curr_state, nRows, nCols, Pts);
           
            if(isEmpty(seat_state)&&num_occupied==0)
            {
                row+='#';
            }
            else if(isOccupied(seat_state)&&num_occupied>=5) // change value for part 1/2
            {
                row+='L';
            }
            else
            {
                row+=seat_state;
            }
        }
        next_state[j]=row;
    }
    return;
}

void PrintArray(string arr[], unsigned long nRows)
{
    for (int i =0; i<nRows; i++)
        cout << arr[i] << endl;
    cout << endl;
    return;
}

bool ArraysEqual(string arr1[], string arr2[], unsigned long nRows, unsigned long nCols)
{
    for (int i =0; i<nRows; i++)
    {
        for (int j =0; j<nCols; j++)
        {
            if(arr1[i][j]!=arr2[i][j])
                return false;
        }
    }
    return true;
}

void CountOccupied(string final_state[], unsigned long nRows, unsigned long nCols)
{
    unsigned long occupied_seats = 0;
    
    for (int i =0; i<nRows; i++)
    {
        for (int j =0; j<nCols; j++)
        {
            if(isOccupied(final_state[i][j]))
                occupied_seats++;
        }
    }
    printf("Number of seats occupied: %lu \n", occupied_seats);
}

int main()
{
    unsigned long nRows = sizeof(program)/sizeof(program[0]);
    unsigned long nCols = program[0].length();
    
    string previous_state[nRows];
    string next_state[nRows];
    copy(program, program+nRows, previous_state);
    
    bool stabilized = false;
    do
    {
        StepForward(previous_state, next_state, nRows, nCols);
        if(ArraysEqual(next_state, previous_state, nRows, nCols))
            stabilized = true;
        copy(next_state, next_state+nRows, previous_state);
    } while (!stabilized);
    CountOccupied(next_state, nRows, nCols);
    return 0;
}
