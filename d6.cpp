#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

int CountUniqueCharacters(string str)
{
    int count = 1;
    sort(str.begin(),str.end());

    char prevChar = str[0];

    for (int i = 1; i < str.length(); i++)
    {
        char currChar = str[i];
        if (currChar != prevChar)
        {
            count++;
            prevChar = currChar;
        }
    }

    return count;
}

int GetAgreed(string str, int pplInGroup)
{
    int count = 0;
    int agreed = 0;
    sort(str.begin(),str.end());
    char prevChar = str[0];

    if(pplInGroup==1)
    {
        agreed = CountUniqueCharacters(str);
    }
    
    else
    {
        for (int i = 0; i < str.length(); i++)
        {
            char currChar = str[i];
            
            if (currChar != prevChar)
            {
                prevChar = currChar;
                count = 1;
            }
            else
            {
                count++;
                if (pplInGroup==count)
                {agreed++;}
            }
        }
    }
    return agreed;
}

int main()
{
    ifstream file("input.txt");
    string line;
    string questions;

    int totalCounts_p1 = 0;
    int totalCounts_p2 = 0;
    int peopleInGroup = -1;

    while(getline(file,line))
    {
        questions.append(line);
        peopleInGroup++;

        if(line=="")
        {
            totalCounts_p1 = totalCounts_p1 + CountUniqueCharacters(questions);
            totalCounts_p2 = totalCounts_p2 + GetAgreed(questions,peopleInGroup);
            questions="";
            peopleInGroup = -1;
        }
    }

    printf("The total count is, p1 and p2: %i, %i\n", totalCounts_p1, totalCounts_p2); // need to add extra line to input file
    return 0;
}
