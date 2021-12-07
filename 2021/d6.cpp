#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> split(string str, char delimiter)
{
  vector<int> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter))
  {
    internal.push_back(stoi(tok));
  }
  return internal;
}

void PrintVec(vector<int>v)
{
    for(int i=0;i<v.size();i++)
    {
        cout << v[i];
        if(i<v.size()-1)
        {
            cout << ",";
        }
    }
    cout << endl;
    return;
}

void PrintMap(map<int, unsigned long> bank)
{
    for(map<int, unsigned long>::iterator it = bank.begin(); it != bank.end(); it++)
    {
        cout << it->first << ":" << it->second << ", " ;
    }
    cout << endl;
    return;
}
void StepDay(vector<int> &v)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i]==0)
        {
            v[i] = 6;
            v.push_back(9);
        }
        else
        {
            v[i]--;
        }
    }
    return;
}

void StepDayMap(map<int, unsigned long> &bank)
{
    map<int,unsigned long> new_map;
    
    for(int i=0;i<9;i++)
    {
        new_map.insert(pair <int,unsigned long> (i,0));
    }
    
    for(map<int, unsigned long>::iterator it = bank.begin(); it != bank.end(); it++)
    {
        if(it->first==0 && it->second > 0)
        {
            new_map.find(0)->second = 0;
            new_map.find(6)->second = it->second;
            new_map.find(8)->second = it->second;
        }
        else if(it->second > 0 && it->first != 0)
        {
            new_map.find(it->first-1)->second += it->second;
        }
    }
    bank = new_map;
    //PrintMap(bank);
    return;
}

int main()
{
    //string input = "3,4,3,1,2"; // test
    string input = "2,1,1,4,4,1,3,4,2,4,2,1,1,4,3,5,1,1,5,1,1,5,4,5,4,1,5,1,3,1,4,2,3,2,1,2,5,5,2,3,1,2,3,3,1,4,3,1,1,1,1,5,2,1,1,1,5,3,3,2,1,4,1,1,1,3,1,1,5,5,1,4,4,4,4,5,1,5,1,1,5,5,2,2,5,4,1,5,4,1,4,1,1,1,1,5,3,2,4,1,1,1,4,4,1,2,1,1,5,2,1,1,1,4,4,4,4,3,3,1,1,5,1,5,2,1,4,1,2,4,4,4,4,2,2,2,4,4,4,2,1,5,5,2,1,1,1,4,4,1,4,2,3,3,3,3,3,5,4,1,5,1,4,5,5,1,1,1,4,1,2,4,4,1,2,3,3,3,3,5,1,4,2,5,5,2,1,1,1,1,3,3,1,1,2,3,2,5,4,2,1,1,2,2,2,1,3,1,5,4,1,1,5,3,3,2,2,3,1,1,1,1,2,4,2,2,5,1,2,4,2,1,1,3,2,5,5,3,1,3,3,1,4,1,1,5,5,1,5,4,1,1,1,1,2,3,3,1,2,3,1,5,1,3,1,1,3,1,1,1,1,1,1,5,1,1,5,5,2,1,1,5,2,4,5,5,1,1,5,1,5,5,1,1,3,3,1,1,3,1"; // full input
    
    vector<int> vec_input = split(input, ',');
    cout << "Initial state: ";
    PrintVec(vec_input);
    
    map<int, unsigned long> bank;
    
    for(int i=0;i<9;i++)
    {
        bank.insert(pair <int,unsigned long> (i,0));
    }
    
    for(int i=0;i<vec_input.size();i++)
    {
        bank.find(vec_input[i])->second ++;
    }
    
    PrintMap(bank);
    for(int d = 1; d<257; d++)
    {
        cout << "After " << d << " days: \n";
        StepDayMap(bank);
    }
    //cout << "Number of fish left: " << vec_input.size() << endl;
    unsigned long sum = 0;
    for(map<int, unsigned long>::iterator it = bank.begin(); it != bank.end(); it++)
    {
        sum = sum + it->second;
    }
    cout << "Number of fish left: " << sum << endl;
    return 0;
}
