#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int GRID_LENGTH = 99; //5 or 99

bool visibleTop(int trees[][GRID_LENGTH], int x, int y)
{
    int val = trees[x][y];
    for(int i=1;i<=x;i++)
    {
        if(val <= trees[x-i][y])
        {
            return false;
        }
    }
    cout <<"visible from top...\n";
    return true;
}

bool visibleBottom(int trees[][GRID_LENGTH], int x, int y)
{
    int val = trees[x][y];
    for(int i=1;i<(GRID_LENGTH-x);i++)
    {
        if(val <= trees[x+i][y])
        {
            return false;
        }
    }
    cout <<"visible from bottom\n";
    return true;
}

bool visibleRight(int trees[][GRID_LENGTH], int x, int y)
{
    int val = trees[x][y];
    for(int j=1;j<(GRID_LENGTH-y);j++)
    {
        if(val <= trees[x][y+j])
        {
            return false;
        }
    }
    cout <<"visible from right\n";
    return true;
}

bool visibleLeft(int trees[][GRID_LENGTH], int x, int y)
{
    int val = trees[x][y];
    for(int j=1;j<=x;j++)
    {
        //cout << "looking at " << x << "," << y-j << endl;
        if(val <= trees[x][y-j])
        {
            return false;
        }
    }
    cout <<"visible from left\n";
    return true;
}

int main()
{
    string line;
    
    ifstream file("input.txt");
    
    int trees[GRID_LENGTH][GRID_LENGTH];
    int visible[GRID_LENGTH][GRID_LENGTH];
    
    int rowCounter = 0;
    long numVisible = 0;
    
    while(getline(file,line))
    {
        for(int i=0;i<line.length();i++)
        {
            string s(1,line[i]);
            trees[rowCounter][i] = stoi(s);
        }
        rowCounter++;
    }
    
    for(int i=0;i<GRID_LENGTH;i++)
    {
        for(int j=0;j<GRID_LENGTH;j++)
        {
            bool isVisible = 1;
            
            cout <<"\n(" << i<<"," << j <<") value " << trees[i][j] << endl;
            if(i==0 || j==0 || (i==GRID_LENGTH-1) || (j==GRID_LENGTH-1))
            {
                numVisible++;
            }
            else if (visibleTop(trees,i,j)|| visibleBottom(trees,i,j) || visibleRight(trees,i,j) || visibleLeft(trees, i, j))
            {
                numVisible++;
            }
            else
            {
               isVisible = 0;
            }
            visible[i][j] = isVisible;
            cout << isVisible << endl;
        }
    }
    
    /*for(int i=0;i<GRID_LENGTH;i++)
    {
        for(int j=0;j<GRID_LENGTH;j++)
        {
            cout << visible[i][j] << "/";
        }
        cout << endl;
    }*/
    
    cout << "Answer part one: " << numVisible << endl; // 860 is too low (x1726, x1646 x 1790)
    return 0;
}
