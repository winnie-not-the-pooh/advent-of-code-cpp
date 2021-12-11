#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <numeric>
#include <functional>

using namespace std;

vector<string> split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter))
  {
    internal.push_back(tok);
  }
  return internal;
}

void printVector(vector<string> v)
{
    for (int i =0; i<v.size(); i++)
    {
        cout << v[i] << ",";
    }
    cout << "\n";
    return;
}

vector<string> getAdjacent(vector<string> heightMap, int l, int x)
{
    vector<string> adjacent;
    
    if(l!=0) // N
    {
        adjacent.push_back(string(1,heightMap[l-1][x]));
    }
    if(x!=(heightMap[0].length()-1)) // E
    {
        adjacent.push_back(string(1,heightMap[l][x+1]));
    }
    if(l!=(heightMap.size()-1)) // S
    {
        adjacent.push_back(string(1,heightMap[l+1][x]));
    }
    if(x!=0) // W
    {
        adjacent.push_back(string(1,heightMap[l][x-1]));
    }
    return adjacent;
}

struct Point
{
    int l;
    int x;
    int value;
    int curValue;
};

vector<Point> getAdjacentPoints(vector<string> heightMap, int l, int x, int curVal)
{
    vector<Point> adjacent;
    
    if(l!=0) // N
    {
        Point p;
        p.l=l-1;
        p.x = x;
        p.value = stoi(string(1,heightMap[l-1][x]));
        p.curValue = curVal;
        adjacent.push_back(p);
    }
    if(x!=(heightMap[0].length()-1)) // E
    {
        Point p;
        p.l=l;
        p.x = x+1;
        p.value = stoi(string(1,heightMap[l][x+1]));
        p.curValue = curVal;
        adjacent.push_back(p);
    }
    if(l!=(heightMap.size()-1)) // S
    {
        Point p;
        p.l=l+1;
        p.x = x;
        p.value = stoi(string(1,heightMap[l+1][x]));
        p.curValue = curVal;
        adjacent.push_back(p);
    }
    if(x!=0) // W
    {
        Point p;
        p.l=l;
        p.x = x-1;
        p.value = stoi(string(1,heightMap[l][x-1]));
        p.curValue = curVal;
        adjacent.push_back(p);
    }
    return adjacent;
}

bool isDone(vector<Point> done, Point p)
{
    for(int i=0;i<done.size();i++)
    {
        if(done[i].l==p.l && done[i].x==p.x)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<string> heightMap;
    
    
    while(getline(file,line))
    {
        heightMap.push_back(line);
    }
        
    unsigned long riskLevel = 0;
    vector<long> basinSizes;
    
    for(int l=0;l<heightMap.size();l++)
    {
        for(int x=0;x<heightMap[0].length();x++)
        {
            vector<string> adjacent = getAdjacent(heightMap, l, x);
            cout << "looking at (" <<l<<","<<x<<") = "<< heightMap[l][x] << endl;
            int min = 100;
            
            for(int a=0;a<adjacent.size();a++)
            {
                int val = stoi(adjacent[a]);
                if(val<min)
                {
                    min = val;
                }
            }
            
            int curVal = stoi(string(1,heightMap[l][x]));
            if(curVal < min)
            {
                riskLevel = riskLevel + 1 + curVal;
                
                // this is a low point
                cout << "This is a low point\n";
                long basin_size = 1;
                
                vector<Point> adjacentPts = getAdjacentPoints(heightMap, l, x, curVal);
                vector<Point> done;
                
                for(int a=0;a<adjacentPts.size();a++)
                {
                    if(adjacentPts[a].value!=9 && adjacentPts[a].value > adjacentPts[a].curValue && !isDone(done, adjacentPts[a]))
                    {
                        basin_size++;
                        done.push_back(adjacentPts[a]);
                        vector<Point> adjacentPts2 = getAdjacentPoints(heightMap, adjacentPts[a].l, adjacentPts[a].x, adjacentPts[a].value);
                        adjacentPts.insert(adjacentPts.end(),adjacentPts2.begin(),adjacentPts2.end());
                    }
                }
                basinSizes.push_back(basin_size);
            }
        }
    }
        
    cout << "Risk Level: " << riskLevel << endl;
    
    sort (basinSizes.begin(), basinSizes.end());
    cout << "Basin Product: " << basinSizes[basinSizes.size()-1] *  basinSizes[basinSizes.size()-2] * basinSizes[basinSizes.size()-3] << endl;
    
    return 0;
}
