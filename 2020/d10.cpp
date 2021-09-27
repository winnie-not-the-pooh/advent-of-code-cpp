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

// split the input into two parts for faster computation. Add zero to the beginning. Multiply total possibilities together to get final answer.
/*int program[]=
{
    0, 1, 2, 3, 6, 7, 8, 9, 10, 13, 16, 17, 18, 21, 22, 25, 28, 29, 30, 33, 34, 35, 36, 37, 40, 43, 44, 45, 46, 49, 50, 51, 52, 53, 56, 57, 58, 59, 60, 63, 66, 67, 68, 69, 72, 75, 78, 79, 80, 81, 82, 85, 88, 91, 94}; // totalP = 4302592*/

int program[]=
{94, 95, 96, 97, 98, 101, 102, 103, 104, 105, 108, 109, 110, 111, 112, 115, 118, 119, 122, 123, 124, 125, 126, 129, 132, 133, 134, 135, 138, 139, 140, 141, 144, 147, 148, 149, 150, 153, 156, 157, 158, 159, 160, 163, 166, 167, 168, 169, 172, 173, 174, 177, 178, 179, 180
}; // totalP = 34420736

/*int program[]=
{
    0,16,
    10,
    15,
    5,
    1,
    11,
    7,
    19,
    6,
    12,
    4
};*/

/*int program[]=
{0,
    28,
    33,
    18,
    42,
    31,
    14,
    46,
    20,
    48,
    47,
    24,
    23,
    49,
    45,
    19,
    38,
    39,
    11,
    1,
    32,
    25,
    35,
    8,
    17,
    7,
    9,
    4,
    2,
    34,
    10,
    3
};*/

void FirstPart()
{
    int nRows = sizeof(program)/sizeof(program[0]);
    sort(program, program + nRows);

    int currJoltage = 0;
    int diffOnes = 0;
    int diffThrees = 1; // device's built-in adapter is always 3 higher than the highest adapter

    for (int i=0; i<nRows; i++)
    {
        int diff = program[i]-currJoltage;
        currJoltage = program[i];

        if(diff==1)
        {
            diffOnes++;
        }
        else if(diff==3)
        {
            diffThrees++;
        }
    }
    printf("There are %i differences of 1 and %i differences of 3 for a product of %i.\n",diffOnes,diffThrees,diffOnes*diffThrees);
    return;
}

void PrintArray(int arr[], int nRows)
{
    for (int i=0; i<nRows;i++)
        cout << arr[i] << ", ";
    cout << endl;
    return;
}

void printVec(vector<string> vec)
{
    for (int i =0 ; i<vec.size();i++ )
        cout << vec[i] << endl;
    return;
}

string getLastValue(string str)
{
    size_t found = str.find_last_of(' ');
    if (found!= string::npos)
    {
        return str.substr(found,str.length()-found);
    }
    return str;
}

void append_endings(vector<string> &totalPossibilities, int ending)
{
    vector<string> out_string;
    for (int i =0 ; i<totalPossibilities.size();i++ )
    {
        int lastVal =  stoi(getLastValue(totalPossibilities[i]));
        if(ending > lastVal and (ending-lastVal <=3))
        {
            totalPossibilities[i] = totalPossibilities[i] + " " + to_string(ending);
        }
    }
    return;
}

vector<string> append_endings(vector<string> totalPossibilities, vector<int> endings)
{
    vector<string> out_strings;
    for (int i =0 ; i<totalPossibilities.size();i++ )
    {
        bool counter = true;
        int lastVal = stoi(getLastValue(totalPossibilities[i]));
        for (int j =0 ; j<endings.size();j++ )
        {
            if(endings[j]>lastVal and (endings[j]-lastVal<=3))
            {
                counter = false;
                out_strings.push_back(totalPossibilities[i] + " " + to_string(endings[j]));
            }
        }
        if (counter)
        {
            out_strings.push_back(totalPossibilities[i]);
        }
    }
    return out_strings;
}

void SecondPart()
{
    int nRows = sizeof(program)/sizeof(program[0]);
    sort(program, program + nRows);

    PrintArray(program, nRows);
    vector<string> totalPossibilities;
    
    int currJoltage = program[0];
    totalPossibilities.push_back(to_string(currJoltage));

    for(int i=1; i<nRows-1;i++)
    {
        int diff1 = program[i]-currJoltage;
        int diff2 = program[i+1]-currJoltage;

        cout << "\nNow: " << currJoltage << endl;
        append_endings(totalPossibilities, currJoltage);
        
        if(diff1<3 && diff2<=3)
        {
            vector<int> endings;
            
            cout << "appending " << currJoltage << " " << program[i] << " " << program[i+1] ;
            endings.push_back(program[i]);
            endings.push_back(program[i+1]);
            
            int diff3 = program[i+2]-currJoltage;
            
            if (diff3==3)
            {
                endings.push_back(program[i+2]);
                cout << " " << program[i+2] << endl;;
            }
            
            totalPossibilities = append_endings(totalPossibilities, endings);
        }
     
        currJoltage = program[i];
        //printVec(totalPossibilities);
    }
    cout << "\nTotal possibilities: "  << totalPossibilities.size() << endl;
    //printVec(totalPossibilities);

    return;
}

int main()
{
    //FirstPart();
    SecondPart();
    return 0;
}
