#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <cmath>
#include <algorithm>

using namespace std;

bool inTarget(int x, int y, int min_x, int max_x, int min_y, int max_y)
{
    if(x>=min_x && x<=max_x && y>=min_y && y<=max_y)
    {
        return 1;
    }
    return 0;
}

void step(int &x, int &y, int &vx, int &vy)
{
    x = x + vx;
    y = y + vy;
    if(vx>0)
    {
        vx = vx - 1;
    }
    else if (vx<0)
    {
        vx = vx + 1;
    }
    vy = vy - 1;
    
    return;
}

int main()
{
    /*int min_x = 20;
    int max_x = 30;
    int min_y = -10;
    int max_y = -5;*/
    
    int min_x = 117;
    int max_x = 164;
    int min_y = -140;
    int max_y = -89;
    
    long nDistinct = 0;
    int max_height = 0;
    
    for(int xx = 1; xx< 400; xx++)
    {
        for(float yy=-400; yy<400; yy++)
        {
            int x = 0;
            int y = 0;
            int vx = xx;
            int vy = yy;
            
            cout << "v=" << vx << "," << vy << endl;
            int max_h = 0;
            for(int i=0;i<400;i++)
            {
                step(x, y, vx, vy);
                if(y>max_h)
                {
                    max_h = y;
                }
                if(inTarget(x, y, min_x, max_x, min_y, max_y))
                {
                    nDistinct++;
                    if(max_h>max_height)
                    {
                        max_height = max_h;
                    }
                    break;
                }
                
                if(vx==0 && (y<min_y|| x>max_x))
                {
                    break;
                }
            }
        }
    }
    
    cout << "Max height is " << max_height << endl;
    cout << "Number of distinct initial velocities is " << nDistinct << endl;
    return 0;
}
