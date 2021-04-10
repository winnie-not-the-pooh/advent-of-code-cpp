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

string program[]={
    "nop +0",
    "acc +1",
    "jmp +4",
    "acc +3",
    "jmp -3",
    "acc -99",
    "acc +1",
    "jmp -4",
    "acc +6"
};

string getAction(string s)
{
    return s.substr(0,3);;
}

int getVal(string s)
{
    return stoi(s.substr(4,s.length()));;
}

void FirstPart()
{
    int accumulator = 0;
    int nRows = sizeof(program)/sizeof(program[0]);

    int i = 0;

    int runTimes[nRows];
    memset(runTimes, 0, sizeof(runTimes));

    do
    {
        string action = getAction(program[i]);
        int val = getVal(program[i]);
        
        cout<< "On line " << i ;
        printf (". Acc = %i.\n", accumulator);

        runTimes[i] ++;
        
        if(action=="acc")
        {
            accumulator = accumulator + val;
            i++;
        }
        else if (action=="jmp")
        {
            i=i+val;
        }
        else
        {
            i++;
        }
        
    } while(runTimes[i]<1); //3720 too high
  
    return;
}

void SecondPart()
{
    int nRows = sizeof(program)/sizeof(program[0]);
    
    int j = 0;
    do
    {
        int i = 0; // iterator
        
        int accumulator = 0;
        int counter = 0;
        bool isLoop = false;
        
        string modified_program[nRows];
    
        for (int p = 0; p < nRows; p++)
        {
            modified_program[p] = program[p];
        }
     
        if (getAction(program[j])!="acc")
        {
            string action = getAction(program[j]);
            int val = getVal(program[j]);
            
            if (action == "nop")
            {
                modified_program[j] = "jmp " + to_string(val);
            }
            else
            {modified_program[j] = "nop " + to_string(val);}
            cout << "modifying row " << j <<" " << modified_program[j] << endl;
        }
            
        else
        {
            cout << "skipping row " << j << endl;
            isLoop = true;
        }
            
        do
        {
            if(i>=nRows)
            {
                cout << "finished" << endl;
                abort();
            }
            
            string action = getAction(modified_program[i]);
            int val = getVal(modified_program[i]);
            
            cout<< "On line " << i ;
            printf (". Acc = %i.\n", accumulator);
            counter ++ ;
            //cout<< " with action " << action << " " << val << endl;
            
            if(action=="acc")
            {
                accumulator = accumulator + val;
                i++;
            }
            else if (action=="jmp")
            {
                i=i+val;
            }
            else
            {
                i++;
            }
            if (counter > nRows)
            {
                isLoop = true;
            }
        } while(!isLoop||i==nRows);
        
        j++;
    } while(j<nRows);
    
    return;
}

int main()
{
    FirstPart();
    cout << "\n#########################\n";
    SecondPart();
    return 0;
}
