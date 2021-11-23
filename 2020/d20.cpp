#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>
#include <math.h>

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

vector<string> flipX( vector <string> tiles) // flip along x axis
{
    vector<string> flipped;
    
    for(int i =0;i<tiles.size();i++)
    {
        flipped.insert(flipped.begin(), tiles[i]);
    }
    return flipped;
}

vector<string> flipY( vector <string> tiles) // flip along y axis
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

struct tile
{
    int ID;
    vector<string> image;
    int Ematch = -1 ;
    int Nmatch = -1 ;
    int Smatch = -1 ;
    int Wmatch = -1 ;
};

void setMatch(char direction, vector<tile> &tiles, int matchIdx, int idx)
{
    switch(direction)
    {
        case 'N':
            tiles[matchIdx].Nmatch = tiles[idx].ID;
            tiles[idx].Smatch = tiles[matchIdx].ID;
            break;
        case 'E':
            tiles[matchIdx].Ematch = tiles[idx].ID;
            tiles[idx].Wmatch = tiles[matchIdx].ID;
            break;
        case 'S':
            tiles[matchIdx].Smatch = tiles[idx].ID;
            tiles[idx].Nmatch = tiles[matchIdx].ID;
            break;
        case 'W':
            tiles[matchIdx].Wmatch = tiles[idx].ID;
            tiles[idx].Ematch = tiles[matchIdx].ID;
            break;
    }
    return;
}

char oppositeDir(char dir)
{
    if(dir=='E')
    {
        return 'W';
    }
    else if (dir == 'W')
    {
        return 'E';
    }
    else if (dir == 'S')
    {
        return 'N';
    }
    else
    {
        return 'S';
    }
}

vector<string> rotate90( vector <string> tile) //rotates CCW 90 degrees
{
    vector<string> rotated;
    
    for(int j=tile.size()-1;j>=0;j--)
    {
        string rotated_str;
        for(int i =0;i<tile.size();i++)
        {
            rotated_str = rotated_str + tile[i][j];
        }
        rotated.push_back(rotated_str);
    }
    return rotated;
}

void lookForMatch(int matchIdx, char direction, vector<tile> &tiles)
{
    string match = edge(direction, tiles[matchIdx].image);
    
    for (int i=0; i<tiles.size();i++)
    {
        if(matchIdx==i)
        {
            continue;
        }
        
        vector<string> img = tiles[i].image;
    
        for(int j=0;j<3;j++)
        {
            for(int r = 0; r<4; r++)
            {
                if(match.compare(edge(oppositeDir(direction), img))==0)
                {
                    setMatch(direction, tiles, matchIdx, i);
                    cout << tiles[i].ID << " matches in " << direction << endl;
                    tiles[i].image = img;
                    //printVector(img);
                    return;
                }
                
                img = rotate90(img);
            }
            if(j==0)
            {img = flipX(img);}
            if(j==1)
            {img = flipX(flipY(img));}
        }
    }
    return;
}

int getIndex(vector<tile> tiles, int tileID)
{
    for(int i =0; i<tiles.size(); i++)
    {
        if(tiles[i].ID == tileID)
        {return i;}
    }
    return -1;
}

vector<string> removeBorders(vector<string> image)
{
    image.erase(image.begin());
    image.pop_back();
    for(int s=0;s<image.size();s++)
    {
        image[s] = image[s].substr(1,image[s].size()-2);
    }
    return image;
}

void append(char direction, vector<string> image, vector<string> &full_image)
{
    if(full_image.empty())
    {
        full_image = image;
        return;
    }
    
    if(direction=='N')
    {
        for(long i = image.size(); i>0; i--)
        {
            full_image.insert(full_image.begin(), image[i]);
        }
    }
    else if(direction == 'S')
    {
        for(long i = 0; i<image.size(); i++)
        {
            full_image.push_back(image[i]);
        }
    }
    else if(direction == 'E')
    {
        for (int i=0;i<10;i++)
        {
            full_image[i] = full_image[i];
            full_image[i] = full_image[i].append(image[i]);
        }
    }
    else
    {
        for (int i=0;i<10;i++)
        {
            full_image[i] = image[i].append(full_image[i]);
        }
    }
    return;
}

bool isInVec(int ID, vector<int> vec, vector<tile> tiles)
{
    for(int i=0; i<vec.size();i++)
    {
        if(vec[i]==getIndex(tiles,ID))
        {return 1;}
    }
    return 0;
}

void constructImage(int currentIdx, vector<tile> tiles, vector<string> &full_image)
{
    // input currentIdx is the ULCorner tile index
    int side_length = sqrt(tiles.size());
    int next_idx = getIndex(tiles,tiles[currentIdx].Smatch);
    vector<string> horizonal_block;
    
    for(int i=0; i<side_length;i++)
    {
        horizonal_block =  removeBorders(tiles[currentIdx].image);
        for(int j=1;j<side_length;j++)
        {
            currentIdx = getIndex(tiles, tiles[currentIdx].Ematch);
            append('E', removeBorders(tiles[currentIdx].image), horizonal_block);
        }
        append('S', horizonal_block, full_image);
        currentIdx = next_idx;
        next_idx = getIndex(tiles,tiles[currentIdx].Smatch);
    }
    return;
}

int countSeaMonsters(vector<string> full_image)
{
    int nSeaMonsters = 0;
    
    for(int i=0; i<full_image.size()-3;i++)
    {
        for(int j=0;j<full_image.size()-20;j++)
        {
            if(full_image[i][18+j]=='#')
            {
                if(full_image[i+1][17+j]=='#'&& full_image[i+1][18+j]=='#'&&full_image[i+1][19+j]=='#'
                   &&full_image[i+1][0+j]=='#'&&full_image[i+1][5+j]=='#'&&full_image[i+1][6+j]=='#'&&full_image[i+1][11+j]=='#'&&full_image[i+1][12+j]=='#')
                {
                    if(full_image[i+2][1+j]=='#'&& full_image[i+2][4+j]=='#'&&full_image[i+2][7+j]=='#'
                       &&full_image[i+2][10+j]=='#'&&full_image[i+2][13+j]=='#'&&full_image[i+2][16+j]=='#')
                    {
                        nSeaMonsters = nSeaMonsters + 1;
                    }
                }
            }
        }
    }
    return nSeaMonsters;
}

int findSeaMonsters(vector<string> full_image)
{
    for(int j=0;j<3;j++)
    {
        for(int r=0;r<4;r++)
        {
            int nSeaMonsters = countSeaMonsters(full_image);
            if(nSeaMonsters!=0)
            {
                return nSeaMonsters;
            }
            
            full_image = rotate90(full_image);
        }
        if(j==0)
        {full_image = flipX(full_image);}
        if(j==1)
        {full_image = flipX(flipY(full_image));}
    }
    return 0;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<tile> tiles;
    vector<string> image;
    
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
    
    int matchIdx;
    bool done = 0;
    vector<int> done_idx;
    vector<int> todo_idx;
    
    done_idx.push_back(-1);
    todo_idx.push_back(0);
    
    do
    {
        matchIdx = todo_idx.front();
        todo_idx.erase(todo_idx.begin());
        
        cout << "tile " << tiles[matchIdx].ID << endl;
        //printVector(tiles[matchIdx].image);
        
        if(tiles[matchIdx].Ematch==-1) // 1171 index 2 has two matches for 1489 as does 1489
        {
            lookForMatch(matchIdx, 'E', tiles);
        }
        if(tiles[matchIdx].Wmatch==-1)
        {
            lookForMatch(matchIdx, 'W', tiles);
        }
        if(tiles[matchIdx].Smatch==-1)
        {
            lookForMatch(matchIdx, 'S', tiles);
        }
        if(tiles[matchIdx].Nmatch==-1)
        {
            lookForMatch(matchIdx, 'N', tiles);
        }
        
        int matchID = tiles[matchIdx].Ematch;
        for(int k=0;k<4;k++)
        {
            if(!isInVec(matchID, done_idx, tiles) && !isInVec(matchID, todo_idx, tiles) )
            {
                todo_idx.push_back(getIndex(tiles, matchID));
            }
            
            switch(k)
            {
                case 0:
                    matchID = tiles[matchIdx].Wmatch;
                    break;
                case 1:
                    matchID = tiles[matchIdx].Smatch;
                    break;
                case 2:
                    matchID = tiles[matchIdx].Nmatch;
                    break;
            }
        }
        done_idx.push_back(matchIdx);
        if(done_idx.size()==(tiles.size()+1))
        {
            done = 1;
        }
    } while(!done);
    
    /*cout << "\n\nPrinting Results...\n";
    for (int i=0; i<tiles.size();i++)
    {
        cout << tiles[i].ID << " index " << i << " : ";
        cout << tiles[i].Nmatch << "," << tiles[i].Ematch << "," <<  tiles[i].Smatch << "," << tiles[i].Wmatch << endl;
        printVector(tiles[i].image);
    }*/
    
    int nMatches = 0;
    int currentIdx = -1;
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
        if(tiles[i].Nmatch == -1 && tiles[i].Wmatch == -1)
        {
            // top L corner
            currentIdx = i;
        }
        if(nMatches <=2)
        {
            cout << tiles[i].ID << " * " ;
            product = product * tiles[i].ID;
        }
    }
    
    cout << " = " << product << "\n\n";
    
    vector<string> full_image;
    
    constructImage(currentIdx, tiles, full_image);
    printVector(full_image);
    
    long nPoundSigns = 0;
    for(int i=0;i<full_image.size();i++)
    {
        nPoundSigns = nPoundSigns + count(full_image[i].begin(), full_image[i].end(), '#');
    }
    
    int nSeaMonsters = findSeaMonsters(full_image);
    cout << "Total # signs: " << nPoundSigns << endl;
    cout << "Number of sea monsters: " << nSeaMonsters << endl;
    
    cout << "Water roughness:  " << nPoundSigns - 15*nSeaMonsters << endl;
    return 0;
}
