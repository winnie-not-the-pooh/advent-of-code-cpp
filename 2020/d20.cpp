#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

void printVector(vector<string> vec)
{
    for (int i =0; i<vec.size(); i++)
    {
        cout << vec[i] << endl;
    }
    cout << "\n";
    return;
}

vector<string> flipX( vector <string> tiles)
// flip along x axis
{
    vector<string> flipped;
    
    for(int i =0;i<tiles.size();i++)
    {
        flipped.insert(flipped.begin(), tiles[i]);
    }
    
    return flipped;
}

vector<string> flipY( vector <string> tiles)
// flip along y axis
{
    vector<string> flipped;
    
    for(int i =0;i<tiles.size();i++)
    {
        string flipped_str;
        for(int j=9;j>=0;j--)
        {
            flipped_str = flipped_str +tiles[i][j];
        }
        flipped.push_back(flipped_str);
    }
    
    return flipped;
}

vector<string> rotate90( vector <string> tiles)
//rotates CCW 90 degrees
{
    vector<string> rotated;
    
    for(int j=10;j>=0;j--)
    {
        string rotated_str;
        for(int i =0;i<tiles.size();i++)
        {
            rotated_str = rotated_str +tiles[i][j];
        }
        rotated.push_back(rotated_str);
    }
    return rotated;
}

string edge(char location, vector <string> vec)
{
    if(location=='N')
    {
        return vec[0];
    }
    else if (location=='S')
    {
        return vec[9];
    }
    else if(location=='E')
    {
        string str;
        for (int i=0;i<10;i++)
        {
            str.push_back(vec[i][9]);
        }
        return str;
    }
    else
    {
        string str;
        for (int i=0;i<10;i++)
        {
            str.push_back(vec[i][0]);
        }
        return str;
    }
}

bool isMatchEdge(string edgeA, string edgeB)
{
    if(edgeA.compare(edgeB)==0)
    {
        return 1;
    }
    return 0;
}

struct tile
{
    int ID;
    vector<string> image;
    int Ematch = -1 ;
    int Nmatch = -1 ;
    int Smatch = -1 ;
    int Wmatch = -1 ;
    
    int TotalMatches = 0;
};

void setMatch(char direction, vector<tile> &tiles, int matchIdx, int idx)
{
    switch(direction)
    {
        case 'N':
            tiles[matchIdx].Nmatch = tiles[idx].ID;
            break;
        case 'E':
            tiles[matchIdx].Ematch = tiles[idx].ID;
            break;
        case 'S':
            tiles[matchIdx].Smatch = tiles[idx].ID;
            break;
        case 'W':
            tiles[matchIdx].Wmatch = tiles[idx].ID;
            break;
    }
    return;
}

void getSolution(vector<tile> tiles)
{
    int nMatches = 0;
    unsigned long product = 1;
    
    for (int i=0; i<tiles.size();i++)
    {
        nMatches = 0;
        if(tiles[i].Ematch != -1)
        {
            nMatches++;
        }
        if(tiles[i].Nmatch != -1)
        {
            nMatches++;
        }
        if(tiles[i].Smatch != -1)
        {
            nMatches++;
        }
        if(tiles[i].Wmatch != -1)
        {
            nMatches++;
        }
        if(nMatches <=2)
        {
            cout << tiles[i].ID << " has only " << nMatches << " matches.\n";
            product = product * tiles[i].ID;
        }
    }
    
    cout << "The result of the four IDs multiplied : " << product << endl;
    
    return;
}

int isThereAMatch(string match, vector <string> vec)
{
    if (isMatchEdge(match, edge('N', vec)) || isMatchEdge(match, edge('S', vec)) || isMatchEdge(match, edge('E', vec)) || isMatchEdge(match, edge('W', vec)))
    {
        return 1; // non transformed
    }
    vector<string>vecX = flipX(vec);
    if (isMatchEdge(match, edge('N', vecX)) || isMatchEdge(match, edge('S', vecX)) || isMatchEdge(match, edge('E', vecX)) || isMatchEdge(match, edge('W', vecX)))
    {
        return 2;
    }
 
    if (isMatchEdge(match, edge('N', flipY(vec))) || isMatchEdge(match, edge('S', flipY(vec))) || isMatchEdge(match, edge('E', flipY(vec))) || isMatchEdge(match, edge('W', flipY(vec))))
    {
        return 3;
    }
    return 0; // no match
}

void lookForMatch(int matchIdx, char direction, vector<tile> &tiles)
{
    string match = edge(direction, tiles[matchIdx].image);
    cout << "looking " << tiles[matchIdx].ID << "," << direction << endl;
    
    for (int i=0; i<tiles.size();i++)
    {
        if(matchIdx==i)
        {
            continue;
        }
       
        int matchType = isThereAMatch(match,tiles[i].image);
        if(matchType>0)
        {
            vector<string>vec = tiles[i].image;
            setMatch(direction, tiles, matchIdx, i);
            cout << tiles[i].ID << " matches on ";
        
            if(matchType==2)
            {
                cout << " flipped X ";
                vec = flipX(vec);
            }
            else if (matchType==3)
            {
                cout << "flipped Y ";
                vec = flipY(vec);
            }
            
            if(isMatchEdge(match, edge('N', vec)))
            {
                setMatch('N', tiles, i, matchIdx);
                cout << "N \n";
            }
            else if (isMatchEdge(match, edge('E', vec)))
            {
                setMatch('E', tiles, i, matchIdx);
                cout << "E \n";
            }
            else if (isMatchEdge(match, edge('S', vec)))
            {
                setMatch('S', tiles, i, matchIdx);
                cout << "S \n";
            }
            else
            {
                setMatch('W', tiles, i, matchIdx);
                cout << "W \n";
            }
            return;
        }
    }
    return;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<tile> tiles;

    vector<string> image;
    vector<string> full_image;
    int tileNo = 0;
    
    while(getline(file,line))
    {
        if (line.find("Tile") != string::npos)
        {
            tileNo = stoi(line.substr(line.find(' ')+1,line.length()-1));
            image.clear();
            continue;
        }
        else if(line=="")
        {
            tile t;
            t.ID = tileNo;
            t.image = image;
            tiles.push_back(t);
        }
        else
        {
            image.push_back(line);
        }
    }
    
    for(int matchIdx = 0; matchIdx<tiles.size();matchIdx++)
    {
        lookForMatch(matchIdx, 'N', tiles);
        lookForMatch(matchIdx, 'S', tiles);
        lookForMatch(matchIdx, 'E', tiles);
        lookForMatch(matchIdx, 'W', tiles);
    }
    
    cout << "\n\nPrinting Results...\n";
    for (int i=0; i<tiles.size();i++)
    {
        cout << tiles[i].ID << ": " << endl;
        cout << tiles[i].Nmatch << "," << tiles[i].Ematch << "," <<  tiles[i].Smatch << "," << tiles[i].Wmatch << endl;
    }
    
    getSolution(tiles);
    return 0;
}
