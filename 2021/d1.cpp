#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>

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

void printVector(vector<int> v)
{
    for (int i =0; i<v.size(); i++)
    {
        cout << v[i] << ",";
    }
    cout << "\n";
    return;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<int> readings;
    
    while(getline(file,line))
    {
        readings.push_back(stoi(line));
    }
    
    int curVal = readings[0];
    int nIncreases = 0;
   
    for(int i=0;i<readings.size();i++)
    {
        if(readings[i]>curVal)
        {
            nIncreases++;
        }
        curVal = readings[i];
    }
    
    cout << "Part 1 answer: " << nIncreases << endl;
    
    int nSlidingIncreases = 0;
    for(int i=3;i<readings.size();i++)
    {
        if(readings[i]-readings[i-3]>0)
        {
            nSlidingIncreases++;
        }
    }
    
    cout << "Part 2 answer: " << nSlidingIncreases << endl;
    
    return 0;
}
