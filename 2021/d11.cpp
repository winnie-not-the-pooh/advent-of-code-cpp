#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;


struct Point
{
    int x;
    int y;
};

bool inFlash(int i, int j, vector<Point>flashed)
{
    for(int f=0;f<flashed.size();f++)
    {
        if(flashed[f].x==i && flashed[f].y==j)
        {
            return 1;
        }
    }
    return 0;
}

template <size_t rows = 10, size_t cols = 10>
void setOctopi(int(& octopi)[rows][cols], int i, int j, vector<Point> &flashed)
{
    if(!inFlash(i, j, flashed))
    {
        octopi[i][j]++;
        
        if(octopi[i][j]>9 && !inFlash(i,j,flashed))
        {
            octopi[i][j] = 0;
            flash(octopi, i, j, flashed);
            Point p;
            p.x = i;
            p.y= j;
            flashed.push_back(p);
        }
    }
    //cout << i << "," << j << "->" << octopi[i][j] << endl;
    return;
}

template <size_t rows = 10, size_t cols = 10>
void flash(int(& octopi)[rows][cols], int i, int j, vector<Point> &flashed)
{
    //cout << "Point " << i << "," << j << " flashes " << endl;
    // get the neighbours and add one. skip THEM IF ALREADY FLASHED
    if(i!=0) //N
    {
        setOctopi(octopi, i-1, j,flashed);
        
        if(j!=(cols-1)) //NE
        {
            setOctopi(octopi, i-1, j+1,flashed);
        }
        if(j!=0) // NW
        {
            setOctopi(octopi, i-1, j-1,flashed);
        }
    }
    if(i!=(rows-1)) //S
    {
        setOctopi(octopi, i+1, j,flashed);
        
        if(j!=(cols-1)) //SE
        {
            setOctopi(octopi, i+1, j+1,flashed);
        }
        if(j!=0) // SW
        {
            setOctopi(octopi, i+1, j-1,flashed);
        }
    }
    if(j!=(cols-1)) //E
    {
        setOctopi(octopi, i, j+1,flashed);
    }
    
    if(j!=0)
    {
        setOctopi(octopi, i, j-1,flashed);
    }
    return;
}

template <size_t rows = 10, size_t cols = 10>
void step(int(& octopi)[rows][cols], long & total_flashes, long & flash_size)
{
    vector<Point> flashed;
    
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            octopi[i][j]++;
            if(octopi[i][j]>9 && !inFlash(i,j,flashed))
            {
                octopi[i][j] = 0;
                flash(octopi, i, j, flashed);
                Point p;
                p.x = i;
                p.y= j;
                flashed.push_back(p);
            }
        }
    }
    
    for(int f=0;f<flashed.size();f++)
    {
        octopi[flashed[f].x][flashed[f].y] = 0;
    }
    
    total_flashes = total_flashes + flashed.size();
    flash_size = flashed.size();
    
    // print array
    /*for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout << octopi[i][j];
        }
        cout << endl;
    }*/
    
    return;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<string> lines;
    
    while(getline(file,line))
    {
        lines.push_back(line);
    }
        
    int octopi[10][10];
    
    cout << "Before any steps:\n";
    for(int i=0;i<lines.size();i++)
    {
        for(int j=0;j<lines[0].length();j++)
        {
            octopi[i][j] = stoi(string(1,lines[i][j]));
            cout << octopi[i][j];
        }
        cout << endl;
    }
    
    long total_flashes = 0;
    long flash_size = 0;
    
    for(int s=1;s<1960;s++)
    {
        cout << "\nAfter step " << s << ":\n";
        step(octopi, total_flashes, flash_size);
        if(flash_size==100)
        {
            cout << "This is when all flashed!" << endl;
            break;
        }
    }
    
    cout << "\nTotal flashes: " << total_flashes << endl;
    
    return 0;
}
