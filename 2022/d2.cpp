#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

int score_p1(string direction)
{
    char wePlay = direction[2];
    char theyPlay = direction[0];
    
    int shapeScore = 0;
    int winScore = 0;
    
    //1 for Rock, 2 for Paper, and 3 for Scissors
    //X for Rock, Y for Paper, and Z for Scissors
    //A for Rock, B for Paper, and C for Scissors
    
    // (0 if you lost, 3 if the round was a draw, and 6 if you won)
        
    if(wePlay=='X') // rock
    {
        shapeScore = 1;
        if(theyPlay=='C')
        {
            winScore = 6;
        }
        else if (theyPlay=='A')
        {
            winScore = 3;
        }
        
    }
    else if (wePlay=='Y') // paper
    {
        shapeScore = 2;
        if(theyPlay=='A')
        {
            winScore = 6;
        }
        else if (theyPlay=='B')
        {
            winScore = 3;
        }
    }
    else //if (shape=='Z') // scisssors
    {
        shapeScore = 3;
        if(theyPlay=='B')
        {
            winScore = 6;
        }
        else if (theyPlay=='C')
        {
            winScore = 3;
        }
    }
    return shapeScore + winScore;
}

int score_p2(string direction)
{
    char wePlay = direction[2];
    char theyPlay = direction[0];
    
    int shapeScore = 0;
    int winScore = 0;
    
    //1 for Rock, 2 for Paper, and 3 for Scissors
    //X means lose, Y means draw, and Z means win
    //A for Rock, B for Paper, and C for Scissors
    
    // (0 if you lost, 3 if the round was a draw, and 6 if you won)
        
    if(wePlay=='Y') // draw
    {
        winScore = 3;
        if(theyPlay=='A')
        {
             shapeScore = 1;
        }
        else if (theyPlay=='B')
        {
            shapeScore = 2;
        }
        else
        {
            shapeScore = 3;
        }
        
    }
    else if (wePlay=='Z') // win
    {
        winScore = 6;
        if(theyPlay=='A')
        {
             shapeScore = 2;
        }
        else if (theyPlay=='B')
        {
            shapeScore = 3;
        }
        else
        {
            shapeScore = 1;
        }
    }
    else //lose
    {
        if(theyPlay=='A')
        {
             shapeScore = 3;
        }
        else if (theyPlay=='B')
        {
            shapeScore = 1;
        }
        else
        {
            shapeScore = 2;
        }
    }
    return shapeScore + winScore;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    long sumScore = 0;
    
    while(getline(file,line))
    {
        sumScore = sumScore + score_p2(line);
    }
    
    cout << "The total score is: " << sumScore << endl;
    return 0;
}
