#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

struct Point
{
    int x;
    int y;
};

void printPoint(Point p)
{
    cout << "(" << p.x << "," << p.y << ")" << endl;
    return;
}

void printPath(vector<Point> path)
{
    
    for(int i=0;i<path.size();i++)
    {
        printPoint(path[i]);
    }
    cout << endl;
    return;
}
void addPoints(vector <Point> & path, string direction)
{
    char dir = direction[0];
    int amt = stoi(direction.substr(1,direction.length()));
    //cout << "dir : " << dir << endl;
    //cout << "amt: " << amt << endl;
    
    if(dir=='R')
    {
        for(int i=0;i<amt;i++)
        {
            Point p;
            p.x = path.back().x+1;
            p.y = path.back().y;
            path.push_back(p);
        }
    }
    else if (dir=='L')
    {
        for(int i=0;i<amt;i++)
        {
            Point p;
            p.x = path.back().x-1;
            p.y = path.back().y;
            path.push_back(p);
        }
    }
    else if (dir=='U')
    {
        for(int i=0;i<amt;i++)
        {
            Point p;
            p.x = path.back().x;
            p.y = path.back().y+1;
            path.push_back(p);
        }
    }
    else
    {
        for(int i=0;i<amt;i++)
        {
            Point p;
            p.x = path.back().x;
            p.y = path.back().y-1;
            path.push_back(p);
        }
    }
    return;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<long> calories;
    long sumCal = 0;
    
    while(getline(file,line))
    {
        if(line=="")
        {
            calories.push_back(sumCal);
            sumCal = 0;
        }
        else
        {
            sumCal = sumCal + stoi(line);
        }
        
    }
    
    sort(calories.begin(), calories.end(), greater <>());
    
    cout << "The most calories carried is: " << calories[0] << endl;
    cout << "The sum of the top three calories is " << calories[0] + calories[1] + calories[2] << endl;
    return 0;
}
