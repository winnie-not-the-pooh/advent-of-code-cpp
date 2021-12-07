#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <cmath>

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

struct Line
{
    int x_begin;
    int y_begin;
    int x_end;
    int y_end;
};

void PrintLines(vector<Line>l)
{
    for(int i=0;i<l.size();i++)
     {
         cout << "Line " << i << ": " ;
         cout << "Start " << l[i].x_begin << ", " << l[i].y_begin << endl;
         cout << "End " << l[i].x_end << ", " << l[i].y_end << endl;
     }
    return;
}

void Print2DArray(int arr[][10], int r, int c) //todo
{
    cout << "Printing diagram: \n";
    for(int i=0;i<r;++i)
    {
        for(int j=0;j<c;++j)
        {
            cout<<arr[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}

bool isStraightLine(Line l)
{
    if(l.x_begin == l.x_end || l.y_begin == l.y_end)
    {
        return 1;
    }
    
    return 0;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    vector<Line> lines;
    
    while(getline(file,line))
    {
        long pos = line.find(" -> ");
        vector<string> begin = split(line.substr(0,pos), ',');
        vector<string> end = split(line.substr(pos+4,line.length()-pos-4), ',');
        Line l;
        l.x_begin = stoi(begin[0]);
        l.y_begin = stoi(begin[1]);
        l.x_end = stoi(end[0]);
        l.y_end = stoi(end[1]);
        lines.push_back(l);
    }
    
    /*int max_x = 1;
    int max_y = 1;
    
    for(int i=0;i<lines.size();i++)
    {
        if(lines[i].x_begin > max_x)
        {
            max_x = lines[i].x_begin;
        }
        if(lines[i].x_end > max_x)
        {
            max_x = lines[i].x_end;
        }
        if(lines[i].y_begin > max_y)
        {
            max_y = lines[i].y_begin;
        }
        if(lines[i].y_end > max_y)
        {
            max_y = lines[i].y_end;
        }
    }
    cout << max_x + 1<< "," << max_y+1 << endl;*/
    
    //int diagram[10][10] = {0}; //for test_input todo
    int diagram[991][990] = {0}; //for input
    
    for(int i=0;i<lines.size();i++)
    {
        cout << lines[i].x_begin << "," <<lines[i].y_begin << " : " << lines[i].x_end << "," <<lines[i].y_end;
        cout << " ("<< isStraightLine(lines[i])<<")"<< endl;
        
        int diff_x = lines[i].x_end-lines[i].x_begin;
        int diff_y = lines[i].y_end-lines[i].y_begin;
        
        if(isStraightLine(lines[i]))
        {
            if(diff_y==0)
            {
                for(int k=0;k<abs(diff_x)+1;k++)
                {
                    if(diff_x>0)
                    {
                        diagram[lines[i].y_begin][k+lines[i].x_begin] ++;
                    }
                    else
                    {
                        diagram[lines[i].y_begin][k+lines[i].x_end] ++;
                    }
                }
            }
            else // x is constant
            {
                for(int k=0;k<abs(diff_y)+1;k++)
                {
                    if(diff_y>0)
                    {
                        diagram[lines[i].y_begin+k][lines[i].x_begin] ++;
                    }
                    else
                    {
                        diagram[lines[i].y_end+k][lines[i].x_begin] ++;
                    }
                }
            }
        }
        else
        {
            for(int k=0;k<abs(diff_x)+1;k++)
            {
                if(diff_x>0)
                {
                    if(diff_y>0)
                    {
                        diagram[lines[i].y_begin+k][k+lines[i].x_begin] ++;
                    }
                    else
                    {
                        diagram[lines[i].y_begin-k][k+lines[i].x_begin] ++;
                    }
                }
                else
                {
                    if(diff_y>0)
                    {
                        diagram[lines[i].y_begin+k][lines[i].x_begin-k] ++;
                    }
                    else
                    {
                        diagram[lines[i].y_begin-k][lines[i].x_begin-k] ++;
                    }
                }
            }
        }
        //Print2DArray(diagram, 10, 10); //todo
    }
    
    cout << endl;
    //Print2DArray(diagram, 10, 10); //for test_input
    //Print2DArray(diagram, 991, 990); //for input
    
    // count overlap
    int overlap = 0;
    
    for(int i=0;i<991;i++) //todo
    {
        for(int j=0;j<990;j++)
        {
            if(diagram[i][j]>1)
            {
                overlap ++;
            }
        }
    }
    
    cout<<"Number of points where at least two lines overlap: " << overlap << endl;
    
    return 0;
}
