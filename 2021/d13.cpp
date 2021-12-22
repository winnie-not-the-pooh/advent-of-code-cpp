#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

using namespace std;

vector<int> split(string str, char delimiter)
{
  vector<int> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter))
  {
    internal.push_back(stoi(tok));
  }
  return internal;
}

vector<string> splitStr(string str, char delimiter)
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

vector<string> initVec(long x, long y)
{
    vector<string> v;
    for(int i=0;i<=y;i++)
    {
        string str = "";
        str.insert(0, x+1, '.');
        v.push_back(str);
    }
    return v;
}

struct Point
{
    int x;
    int y;
};

void initPaper(int size)
{
    return;
}

vector<string> fold(vector<string> paper, string axis, int val)
{
    long xLen;
    long yLen;
    vector<string> folded;
    
    if(axis.compare("y")==0)
    {
        xLen = paper[0].length()-1;
        yLen = val - 1;
        folded = initVec(xLen, yLen);
        for(int i=0;i<val;i++)
        {
            for(int j=0;j<paper[0].length();j++)
            {
                if(paper[i][j]=='#' || paper[paper.size()-1-i][j]=='#')
                {
                    folded[i][j]='#';
                }
            }
        }
    }
    else
    {
        xLen = val - 1;
        yLen = paper.size()-1;
        folded = initVec(xLen, yLen);
        for(int i=0;i<paper.size();i++)
        {
            for(int j=0;j<val;j++)
            {
                if(paper[i][j]=='#' || paper[i][paper[0].length()-1-j]=='#')
                {
                    folded[i][j]='#';
                }
            }
        }
    }
    return folded;
}

void PrintPaper(vector<string> v)
{
    for(int j=0;j<v.size();j++)
    {
        cout << v[j] << endl;
    }
    return;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<Point> points;
    vector<string> instructions;
    bool getInstructions = 0;
    int maxValX = 0;
    int maxValY = 0;
    
    while(getline(file,line))
    {
        if(line.compare("")==0)
        {
            getInstructions = 1;
            continue;
        }
        
        if(!getInstructions)
        {
            vector<int> vals = split(line, ',');
            Point p;
            p.x = vals[0];
            p.y = vals[1];
            if(p.x>maxValX)
            {
                maxValX = p.x;
            }
            if(p.y>maxValY)
            {
                maxValY = p.y;
            }
            points.push_back(p);
        }
        else
        {
            instructions.push_back(line);
        }
    }
    
    vector<string> paper = initVec(maxValX, maxValY);
    
    for(int i=0; i<points.size();i++)
    {
        paper[points[i].y][points[i].x] = '#';
    }
    
    //cout << "initial configuration: \n";
    //PrintPaper(paper);
    
    cout << "instructions: \n" ;
    for(int i=0;i<instructions.size();i++)
    {
        string instruction = instructions[i];
        cout << instruction << endl;
        size_t found = instruction.find("along ");
        if (found!=string::npos)
        {
            vector<string> instr = splitStr(instruction.substr(found+6, instruction.length()-found), '=');
            string axis = instr[0];
            int val = stoi(instr[1]);
            paper = fold(paper, axis, val);
            long nDots = 0;
            for(int i=0;i<paper.size();i++)
            {
                for(int j=0;j<paper[0].length();j++)
                {
                    if(paper[i][j]=='#')
                    {
                        nDots++;
                    }
                }
            }
            cout << "Number of dots visible: "  << nDots << endl;
        }
    }
    
    PrintPaper(paper);
    
    return 0;
}
