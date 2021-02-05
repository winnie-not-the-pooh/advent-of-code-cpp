#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <iterator>

using namespace std;

int program[] = {0,1,5,10,3,12,19};

//int program[] = {3,1,2};

int main()
{
    int max_turns = 30000000;
    static int counter[30000000][2];
    
    memset(counter, -1, sizeof(counter));
    
    int program_size = sizeof(program)/sizeof(program[0]);
    for (int i =0; i<program_size; i++)
    {
        int value = program[i];
        counter[value][0] = i+1;
    }
    
    int turn = program_size+1;
    int curVal = program[program_size-1];

    do
    {
        // update curVal
        if (counter[curVal][1] == -1)
            curVal = 0;
        else
            curVal = counter[curVal][0]-counter[curVal][1];
        
        cout << "turn " << turn << " value " << curVal <<endl;
        
        // update counter
        counter[curVal][1] =  counter[curVal][0];
        counter[curVal][0] = turn;
        
        turn++;
    } while (turn<=max_turns);
    
    printf("%ith value: %i.\n",max_turns, curVal);
    
    return 0;
}
