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
#include <bitset> // for converting to binary
#include<numeric>

using namespace std;

string applyBitMaskToVal(string val, string mask) // part 1
{
    string newVal ="";
    
    for(int i=0;i<mask.length();i++)
    {
        if(mask[i]=='X')
        {
            newVal = newVal + val[i];
        }
        else
        {
            newVal = newVal + mask[i];
        }
    }
    return newVal;
}

string applyBitMaskToAdd(string address, string mask) // part 2
{
    string newAdd ="";
    
    for(int i=0;i<mask.length();i++)
    {
        if(mask[i]=='0')
        {
            newAdd = newAdd + address[i];
        }
        else // if(mask[i]=='1') or X
        {
            newAdd = newAdd + mask[i];
        }
    }
    return newAdd;
}

int main()
{
    ifstream file("input.txt");
    string line;
    
    string mask;
    map<unsigned long long, unsigned long long> allValuesPart1;
    map<unsigned long long, unsigned long long> allValuesPart2;
  
    while(getline(file,line))
    {
        if (line.find("mask = ")!=string::npos)
        {
            mask = line.substr(line.find("mask = ")+7,line.length()-7);
        }
        else
        {
            unsigned int address = stoi(line.substr(line.find("mem[")+4,line.find("]")-line.find("mem[")-4));
            string address_binary = bitset<36>(address).to_string();
            
            unsigned long long val = stoll(line.substr(line.find(" = ")+3,line.length()-line.find(" = ")));
            string val_binary = bitset<36>(val).to_string();
            
            map<unsigned long long, unsigned long long>::iterator it = allValuesPart1.find(address);
            if (it != allValuesPart1.end())
            {
                it->second = bitset<36>(applyBitMaskToVal(val_binary, mask)).to_ullong();
            }
            else
            {
                allValuesPart1.insert(pair<unsigned long long, unsigned long long>(address, bitset<36>(applyBitMaskToVal(val_binary, mask)).to_ullong()));
            }
            
            string newAdd = applyBitMaskToAdd(address_binary, mask);
            vector<string>allAddresses;
            allAddresses.push_back(newAdd);
            bool exit_loop = 0;
            
            do
            {
                string str_address = allAddresses.front();
                long x_pos = str_address.find('X');
                if(x_pos<=str_address.length())
                {
                    string one = str_address;
                    one[x_pos]='1';
                    string two = str_address;
                    two[x_pos]='0';
                    allAddresses.erase(allAddresses.begin());
                    allAddresses.push_back(one);
                    allAddresses.push_back(two);
                }
                else
                    exit_loop = 1;
            } while (!exit_loop);
            
            for (int i =0 ; i< allAddresses.size();i++)
            {
                bitset<36> bits(allAddresses[i]);
                
                map<unsigned long long, unsigned long long>::iterator it = allValuesPart2.find(bits.to_ullong());
                if (it != allValuesPart2.end())
                {
                    it->second = val;
                }
                else
                {
                    allValuesPart2.insert(pair<unsigned long long, unsigned long long>(bits.to_ullong(),val));
                }
            }
        }
    }
    
    unsigned long long totalSum1 = 0;
    unsigned long long totalSum2 = 0;
    
    for (map<unsigned long long, unsigned long long>::iterator itr = allValuesPart1.begin(); itr != allValuesPart1.end(); ++itr)
    {
        totalSum1 = totalSum1 + itr->second;
    }
    
    for (map<unsigned long long, unsigned long long>::iterator itr = allValuesPart2.begin(); itr != allValuesPart2.end(); ++itr)
    {
        totalSum2 = totalSum2 + itr->second;
    }
    
    cout << "total sum for part 1 is: " << totalSum1 << endl;
    cout << "total sum for part 2 is: " << totalSum2 << endl;
    return 0;
}
