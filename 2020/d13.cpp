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
#include <cmath>
#include <math.h>

using namespace std;

unsigned long earliestTime = 1002632;

string strBusInput  = "23,x,x,x,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,829,x,x,x,x,x,x,x,x,x,x,x,x,13,17,x,x,x,x,x,x,x,x,x,x,x,x,x,x,29,x,677,x,x,x,x,x,37,x,x,x,x,x,x,x,x,x,x,x,x,19,"; // ; //"7,13,x,x,59,x,31,19,";

void ReadInput(string input, vector<unsigned long long> &busInput, vector<unsigned long long> &offset)
{
    string busStr="";
    int counter = 0;
    
    for (int i =0; i<input.length(); i++)
    {
        if (input[i]==',')
        {
            if(busStr!="x")
            {
                busInput.push_back(stoi(busStr));
                offset.push_back(counter);
            }
           
            busStr="";
            counter ++;
            continue;
        }
        busStr+=input[i];
    }
    return;
}

unsigned long closestTime(unsigned long long bus, unsigned long earliestTime)
{
    return bus*(earliestTime/bus+1);
}

void VecToArray(vector<unsigned long long> busInputVec, unsigned long long *busInput)
{
    for (int i =0; i<busInputVec.size();i++ )
    {
        busInput[i] = busInputVec[i];
    }
    return;
}

void FirstPart()
{
    vector<unsigned long long> busInputVec;
    vector<unsigned long long> offset;
    
    ReadInput(strBusInput, busInputVec, offset);
    unsigned long long busInput[busInputVec.size()];
    VecToArray(busInputVec, busInput);
    
    unsigned long nRows = sizeof(busInput)/sizeof(busInput[0]);

    unsigned long long earliestBusID = 0;
    unsigned long minBusTime = 1000000;
    unsigned long BusTime;
    
    for(int i=0; i<nRows; i++)
    {
        printf("Bus: %llu\tTime: %lu\n", busInput[i], closestTime(busInput[i], earliestTime));
        BusTime = closestTime(busInput[i], earliestTime) - earliestTime;
        if(BusTime < minBusTime)
        {
            minBusTime = BusTime;
            earliestBusID = busInput[i];
        }
    }
    printf("The ID of earliest bus ID, %llu, times # of minutes you'll need to wait, %lu, is: %llu\n", earliestBusID,minBusTime,earliestBusID*minBusTime);
    
    return;
}

bool FulfillsRequirements(vector<unsigned long long> busInput, vector<unsigned long long> offset, unsigned long long X)
{
    bool fulfills = X%busInput[0]==0;
    
    for (int i=1;i<busInput.size();i++)
    {
        fulfills = (fulfills && ((X+offset[i])%busInput[i]==0));
    }
    
    return fulfills;
} // put the raw equations in Wolfram Alpha and solve.

int main()
{
    FirstPart();
    return 0;
}
