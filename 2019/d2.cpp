#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

void printResults(vector<long long> results)
{
    for(int i=0;i<results.size();i++)
    {
        cout << results[i] << "," ;
    }
    return;
}

void modifyResults(vector<long long> &results, long long opcode, long long pos1, long long pos2, long long pos3, bool &done)
{
    if(opcode==1)
    {
        //cout << "addition \n";
        //cout << "setting index" << pos3 << " to " <<  results[pos1]  << " + " << results[pos2] << "\n";
        results[pos3]= results[pos1] + results[pos2];
        //printResults(results);
    }
    else if (opcode==2)
    {
        //cout << "multiplication \n";
        results[pos3]= results[pos1] * results[pos2];
    }
    else if (opcode==99)
    {
        done = 1;
    }
    else
    {
        cout << "error reading opcode " << opcode << endl;
    }
    
    return ;
}

int main()
{
    stringstream ss("1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,6,1,19,1,5,19,23,2,6,23,27,1,27,5,31,2,9,31,35,1,5,35,39,2,6,39,43,2,6,43,47,1,5,47,51,2,9,51,55,1,5,55,59,1,10,59,63,1,63,6,67,1,9,67,71,1,71,6,75,1,75,13,79,2,79,13,83,2,9,83,87,1,87,5,91,1,9,91,95,2,10,95,99,1,5,99,103,1,103,9,107,1,13,107,111,2,111,10,115,1,115,5,119,2,13,119,123,1,9,123,127,1,5,127,131,2,131,6,135,1,135,5,139,1,139,6,143,1,143,6,147,1,2,147,151,1,151,5,0,99,2,14,0,0");
    vector<long long> results;
    while(ss.good())
    {
        string substr;
        getline( ss, substr, ',' );
        results.push_back( stoi(substr ));
    }
    
    //Part 1
    /*
    long noun = 12;
    long verb = 2;
    
    results[1] = noun;
    results[2] = verb;
    
    bool done = 0;
    for(int curPos = 0;curPos<results.size();curPos=curPos+4)
    {
        //cout << "\nvalue " << results[curPos] << " at value " << curPos << endl;
        modifyResults(results, results[curPos], results[curPos+1], results[curPos+2], results[curPos+3], done);
        if(done)
        {
            break;
        }
    }*/
    
    // Part 2
    long output = 19690720;
    
    for(int noun=0;noun<=99;noun++)
    {
        for(int verb=0;verb<=99;verb++)
        {
            //cout << "Noun/verb: " << noun << "/" << verb << endl;
            vector<long long> Newresults = results;
            Newresults[1] = noun;
            Newresults[2] = verb;
            bool done = 0;
            
            for(int curPos = 0;curPos<Newresults.size();curPos=curPos+4)
            {
                modifyResults(Newresults, Newresults[curPos], Newresults[curPos+1], Newresults[curPos+2], Newresults[curPos+3], done);
                if(done)
                {
                    //cout << "Value at position 0: " << results[0] << endl;
                    if(Newresults[0]==output)
                    {
                        cout << "100 * noun + verb = " << 100*noun + verb << endl;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}
