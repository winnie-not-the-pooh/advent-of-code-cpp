#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <cstring>

using namespace std;

bool fullyContains(long long s1, long long e1, long long s2, long long e2)
{
    if(s1<=s2 && e1>=e2)
    {
        return 1;
    }
    else if (s1>=s2 && e1<=e2)
    {
        return 1;
    }
    return 0;
}

bool overlaps(long long s1, long long e1, long long s2, long long e2)
{
    if (fullyContains(s1,e1,s2,e2))
    {
        return 1;
    }
    else if(s1<e2 || s2<e1)
    {
        return 1;
    }
    return 0;
}

vector<int> findLocation(string line, char findIt)
{
    vector<int> characterLocations;
    for(int i =0; i < line.size(); i++)
        if(line[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    int numFullyContains = 0;
    int numOverlaps = 0;
    
    while(getline(file,line))
    {
        size_t comma_pos = line.find(",");
        
        vector<int> dash_pos;
        dash_pos = findLocation(line, '-');
        
        long long firstStart = stoll(line.substr(0,dash_pos[0]));
        long long firstEnd = stoll(line.substr(dash_pos[0]+1,comma_pos-dash_pos[0]-1));
        long long secondStart = stoll(line.substr(comma_pos+1,dash_pos[1]-comma_pos-1));
        long long secondEnd = stoll(line.substr(dash_pos[1]+1,line.length()-dash_pos[1]-1));
        
        if(fullyContains(firstStart, firstEnd, secondStart, secondEnd))
        {
            numFullyContains++;
        }
        if(overlaps(firstStart, firstEnd, secondStart, secondEnd))
        {
            numOverlaps++;
        }
    }
    cout << "Answer for part 1: " << numFullyContains << endl;
    cout << "Answer for part 2: " << numOverlaps << endl; // between 670 and 905 x765 x863 ??
    return 0;
}
