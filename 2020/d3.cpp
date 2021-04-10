#include <iostream>
#include<string>
#include <array>

using namespace std;

string treeMap[] =
{
    ".#..#.....#....##.............."
   // input the rest
};

void FirstHalf()
{
    int nTrees = 0;
    int nRows = sizeof(treeMap)/sizeof(treeMap[0]);
    unsigned long idxCounter = 0; // start at square 1
    unsigned long rowLength = treeMap[0].length();

    for (int i=1; i<nRows; i++) // start at 1 because go down 1 and right 3
    {
        idxCounter = idxCounter + 3;
        if (idxCounter >= rowLength)
        {
            idxCounter = idxCounter - rowLength;
        }
        if (treeMap[i][idxCounter] == '#')
        {
            nTrees++;
        }
         }
    cout << "The number of trees passed are: ";
    cout << nTrees << endl;
    return;
}

void SecondHalf()
{
    int nTrees = 0;
    int nRows = sizeof(treeMap)/sizeof(treeMap[0]);
    unsigned long idxCounter = 0; // start at square 1
    unsigned long rowLength = treeMap[0].length();

    for (int i=1; i<nRows; i++) // modify this line to change D#.
    {
        idxCounter = idxCounter + 7; // modify this line to change R#
        if (idxCounter >= rowLength)
        {
            idxCounter = idxCounter - rowLength;
        }
        if (treeMap[i][idxCounter] == '#')
        {
            nTrees++;
        }
    }
    cout << "The number of trees passed are: ";
    cout << nTrees << endl; // R1D1 = 84 R3D1 = 289 R5D1 = 89 R7D1= 71 R1D2= 36
    return;
}

int main()
{
    FirstHalf();
    SecondHalf();
    return 0;
}
