#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void PrintCounts(vector<pair<string,unsigned long long>> p)
{
    for(int i=0; i<p.size();i++)
    {
        if(p[i].second>0)
        {
            cout << p[i].first << ":" << p[i].second << endl;
        }
    }
    return;
}

void add(vector<pair<string,unsigned long long>> &newCounts, string substr, unsigned long val)
{
    for(int i=0; i<newCounts.size();i++)
    {
        if(newCounts[i].first==substr)
        {
            newCounts[i].second = newCounts[i].second + val;
        }
    }
    return;
}

vector<pair<string,unsigned long long>> initialize(map<string,char> m_instructions)
{
    vector<pair<string,unsigned long long>> counts;
    map<string, char>::iterator it;
    for(it=m_instructions.begin(); it!=m_instructions.end(); ++it)
    {
        pair <string,unsigned long long> p (it->first,0);
        counts.push_back(p);
    }
    return counts;
}

void step(map<string,char> m_instructions,  vector<pair<string,unsigned long long>> &counts)
{
    vector<pair<string,unsigned long long>> newCounts = initialize(m_instructions);
    for(int i=0; i<counts.size();i++)
    {
        if(counts[i].second > 0)
        {
            map<string, char>::iterator it;
            for(it=m_instructions.begin(); it!=m_instructions.end(); ++it)
            {
                if(it->first==counts[i].first)
                {
                    string substr1 = it->first[0] + string(1,it->second);
                    string substr2 = string(1,it->second) + it->first[1];
                    
                    //cout << " changes to : "<< substr1 << " and " << substr2 << endl;
                    add(newCounts, substr1, counts[i].second);
                    add(newCounts, substr2, counts[i].second);
                }
            }
        }
    }
    counts = newCounts;
    return;
}

int main()
{
    ifstream file("input_test.txt");
    
    string line;
    
    string rule;
    map<string,char> m_instructions;
    
    set<char> letters;
    bool getInstructions = 0;
    
    while(getline(file,line))
    {
        if(line.compare("")==0)
        {
            getInstructions = 1;
            continue;
        }
        
        if(getInstructions)
        {
            size_t pos = line.find(" -> ");
            letters.insert(line.substr(pos+4,line.length()-pos-4)[0]);
            m_instructions[line.substr(0,pos)]=line.substr(pos+4,line.length()-pos-4)[0];
        }
        else
        {
            rule = line;
        }
    }
    
    cout << "Template: " << rule << endl;
    
    vector<pair<string,unsigned long long>> counts = initialize(m_instructions);
    
    for(int i=0;i<rule.length()-1;i++)
    {
        string substr = rule.substr(i,2);
        for(int k=0;k<counts.size();k++)
        {
            if(substr==counts[k].first)
            {
                counts[k].second++;
            }
        }
    }
    
    PrintCounts(counts);
    
    for(int s=1; s<=40; s++)
    {
        step(m_instructions, counts);
        cout << "After step " << s << ": \n";
    }
    
    //PrintCounts(counts);
    
    set<char>::iterator it = letters.begin();
    while (it != letters.end())
    {
        unsigned long long amt = 0;
        
        for(int i=0;i<counts.size();i++)
        {
            if((*it)==counts[i].first[0])
            {
                amt = amt + counts[i].second;
            }
        }
        cout << (*it) << " occurs " << amt << " times" << endl;
        // add one to the answer you get manually for hte last character in the rule
        it++;
    }
    return 0;
}
