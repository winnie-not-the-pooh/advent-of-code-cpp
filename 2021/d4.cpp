#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

void PrintVec(vector<string>v)
{
    for(int k=0;k<v.size();k++)
    {
        cout << v[k] << "/" << endl;
    }
    return;
}

void PrintBoard(vector<vector<string>>bb)
{
    for(int i=0;i<bb.size();i++)
     {
         for(int j=0;j<bb[i].size();j++)
         {
             cout<<bb[i][j] << "/";
         }
         cout << endl;
     }
    return;
}

void removeWeirdSpaces(string &str)
{
    if(str[0]==' ')
    {
        str.erase(0,1);
    }
    
    long loc;
    while((loc = str.find("  ")) != string::npos) //Two spaces here
    {
        str.replace(loc,2," "); //Single space in quotes
    }
    
    return;
}

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

bool isBingo(vector<vector<string>> board)
{
    for(int i=0;i<board.size();i++)
    {
         int rowCount = 0;
         for(int j=0;j<board[i].size();j++)
         {
             if(board[i][j].compare("x")==0)
             {
                 rowCount++;
             }
         }
         if(rowCount == 5)
         {
             return 1;
         }
     }
    
    for(int p = 0; p<board[0].size();p++)
    {
        int colCount = 0;
        
        for(int b=0; b<board.size(); b++)
        {
            //cout << board[b][p] << "," << endl;
            if(board[b][p].compare("x")==0)
            {
                colCount++;
            }
        }
        if(colCount == 5)
        {
            return 1;
        }
    }
    
    return 0;
}

void markDrawn(string drawNo,  vector<vector<string>> & board)
{
    for(int i=0;i<board.size();i++)
     {
         for(int j=0;j<board[i].size();j++)
         {
             if(board[i][j].compare(drawNo)==0)
             {
                 board[i][j] = "x";
             }
         }
     }
    return;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    vector<string> lines;
    
    while(getline(file,line))
    {
        if (line=="")
        {
            continue;
        }
        else
        {
            lines.push_back(line);
        }
    }

    vector<string> drawNos = split(lines[0], ',');
    lines.erase(lines.begin());
    
    vector<vector<string>> board;
    vector <vector<vector<string>>> boards;
    
    int counter = 0;
    
    for(int i=0;i<lines.size();i++)
    {
        removeWeirdSpaces(lines[i]);
        vector<string> line = split(lines[i], ' ');
        board.push_back(line);
        counter ++;
        
        if(counter == 5)
        {
            counter = 0;
            boards.push_back(board);
            board.clear();
        }
    }
    
    for(int d = 0; d<drawNos.size();d++)
    {
        string drawNo = drawNos[d];
        cout << "draw = " << drawNo << endl;
        
        for(int b=0;b<boards.size();b++)
        {
            finishDraw:
            markDrawn(drawNo,  boards[b]);
            PrintBoard(boards[b]);
            cout << endl;
            if(isBingo(boards[b]))
            {
                cout << "this is a bingo " << endl;
                // part 2
                if(boards.size()!=1)
                {
                    boards.erase(boards.begin()+b);
                    if(b<boards.size())
                    {
                        goto finishDraw;
                    }
                    continue;
                }
                // part 2 end
                else
                {
                    int sum = 0;
                    vector<vector<string>>bb = boards[b];
                    for(int i=0;i<bb.size();i++)
                     {
                         for(int j=0;j<bb[i].size();j++)
                         {
                             if(bb[i][j].compare("x")!=0)
                             {
                                 sum = sum + stoi(bb[i][j]);
                             }
                         }
                     }
                    
                    cout << "Answer: " << sum * stoi(drawNo) << endl;
                    goto endloop;
                }
            }
        }
    }

    endloop:
    return 0;
}
