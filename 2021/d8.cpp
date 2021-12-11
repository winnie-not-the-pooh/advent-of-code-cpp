#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

vector<string> split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter))
  {
    internal.push_back(tok);
  }
  return internal;
}

void printVector(vector<string> v)
{
    for (int i =0; i<v.size(); i++)
    {
        cout << v[i] << ",";
    }
    cout << "\n";
    return;
}

bool contains(string str, string substr)
{
    for(int s=0; s<substr.size();s++)
    {
        if(str.find(substr[s])==string::npos)
        {
            return 0;
        }
    }
    
    return 1;
}

struct compare {
    inline bool operator()(const std::string& first,
            const std::string& second) const
    {
         return first.size() < second.size();
    }
};

string convert(vector<string> map_digits, string str)
{
    for(int i=0;i<map_digits.size();i++)
    {
        if(str.length() == map_digits[i].length() && contains(map_digits[i], str))
        {
            return to_string(i);
        }
    }
    
    return "";
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    int nTimes = 0;
    
    while(getline(file,line))
    {
        vector<string> v = split(line, '|');
        vector<string> v_input = split(v[0], ' ');
        vector<string> v_output = split(v[1].substr(1,v[1].length()-1), ' ');
        vector<string> v_all = v_input;
        v_all.insert(v_all.end(), v_output.begin(), v_output.end());
        
        compare c;
        sort(v_all.begin(), v_all.end(), c);
        
        vector<string> map_digits;
        for(int m=0;m<10;m++)
        {
            map_digits.push_back("None");
        }
        
        // part 1
        /*for(int i=0;i<v_output.size();i++)
        {
            long len = v_output[i].length();
            if(len==2 || len ==4 || len==3 || len==7)
            {
                nTimes++;
            }
        }*/
        
        // part 2
        for(int i=0;i<v_all.size();i++)
        {
            long len = v_all[i].length();
            //cout << "looking at " << v_all[i] << ", length = " << len << endl;
            if(len==2) // if len 2, this is 1
            {
                map_digits[1] = v_all[i];
            }
            else if (len==3) // if len 3, this is 7
            {
                map_digits[7] = v_all[i];
            }
            else if (len==4) // if len 4, this is 4
            {
                map_digits[4] = v_all[i];
            }
            else if (len==5)
            {
                if(contains(v_all[i], map_digits[1]))
                {
                    map_digits[3] = v_all[i]; // if contains 1, this is 3
                }
                else
                {
                    string left_over = map_digits[4];
                    left_over.erase(remove(left_over.begin(), left_over.end(), map_digits[1][0]), left_over.end());
                    left_over.erase(remove(left_over.begin(), left_over.end(), map_digits[1][1]), left_over.end());
                    if(contains(v_all[i], left_over))
                    {
                        map_digits[5] = v_all[i];
                    }
                    else
                    {
                        map_digits[2] = v_all[i];
                    }
                }
            }
            else if (len==6) // if len 6
            {
                if(contains(v_all[i], map_digits[7]))
                {
                    if(contains(v_all[i], map_digits[4]))
                    {
                        map_digits[9] = v_all[i];
                    }
                    else
                    {
                        map_digits[0] = v_all[i];
                    }
                }
                else // if doesn't contain 7, this is 6
                {
                    map_digits[6] = v_all[i];
                }
            }
            else if (len==7) // if len 7, this is 8
            {
                map_digits[8] = v_all[i];
            }
            else
            {
                cout << "something is wrong \n";
            }
        }
        
        //printVector(map_digits);
        
        string output = "" ;
        for(int k=0;k<v_output.size();k++)
        {
            output = output + convert(map_digits, v_output[k]);
        }
        nTimes = nTimes + stoi(output);
    }
    
    cout << "Answer: " << nTimes << endl;
    return 0;
}
