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

long calculatePriority(vector <string> item_intersection)
{
    long sumScore = 0;
    
    for(int i=0;i<item_intersection.size();i++)
    {
        //cout << item_intersection[i] << ",";
        const char *cstr = item_intersection[i].c_str();
        if(isupper(*cstr))
        {
            sumScore = sumScore + int(*cstr) - 38;
        }
        else
        {
            sumScore = sumScore + int(*cstr) - 96;
        }
    }
    
    return sumScore;
}

string find_intersection2(string s1, string s2)
{
    string s3="";

    for (int i=0;i<s1.length();i++)
    {
        for(int j=0;j<s2.length();j++)
        {
            if(s1[i]==s2[j])
            {
                if (s3.find(s1[i]) != string::npos)
                {
                    
                }
                else
                {
                    s3 = s3 + s1[i];
                }
            }
        }
    }
    return s3;
}

string find_intersection3(string s1, string s2, string s3)
{
    string s4="";

    string s_intersection2 = find_intersection2(s1, s2);
    
    for (int i=0;i<s3.length();i++)
    {
        for(int j=0;j<s_intersection2.length();j++)
        {
            if(s3[i]==s_intersection2[j])
            {
                if (s4.find(s3[i]) != string::npos)
                {
                    
                }
                else
                {
                    s4 = s4 + s3[i];
                }
            }
        }
    }

    return s4;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector <string> item_intersection;
    vector<string> lines;
    
    while(getline(file,line))
    {
        /* part 1 */
        /*long compartment_size = line.length()/2;
        string c1 = line.substr(0,compartment_size);
        string c2 = line.substr(compartment_size,compartment_size);
        item_intersection.push_back(find_intersection2(c1, c2));*/
        
        lines.push_back(line);
    }
    
    for(int i=0; i<lines.size();i = i+3)
    {
        item_intersection.push_back(find_intersection3(lines[i], lines[i+1], lines[i+2]));
    }
    cout << "The total score is: " << calculatePriority(item_intersection) << endl;
    return 0;
}
