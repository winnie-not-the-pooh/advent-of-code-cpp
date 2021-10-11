#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <iterator>
#include <cmath>
#include <math.h>
#include<numeric>

using namespace std;

void findAndReplaceAll(string &subject, string search, string replace)
{
    size_t pos = subject.find(search);
    while( pos != string::npos)
    {
        subject.replace(pos, search.size(), replace);
        pos = subject.find(search, pos + replace.size());
    }
}

int findNthOccur(string str, char ch, int N)
{
    int occur = 0;
  
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ch)
        {
            occur += 1;
        }
        if (occur == N)
            return i;
    }
    return -1;
}

string relevantSubject(string subject, string search)
// find part of rule that should be copied
{
    long numPossibilities = count(subject.begin(), subject.end(), '|') + 1;
    string relevantSubject;
    int previous_replace = -1;
    for(int p=1; p<=numPossibilities; p++)
    {
        int pos_replace = findNthOccur(subject, '|', p);
        string newSubject = subject.substr(previous_replace+1,pos_replace-previous_replace-1);
        previous_replace = pos_replace;
       
        if (newSubject.find(search)!=string::npos)
        {
            if(relevantSubject.empty())
            {
                relevantSubject = newSubject;
            }
            else
            {
                relevantSubject = relevantSubject + "|" + newSubject;
            }
        }
    }
    
    return relevantSubject;
}

void ReplaceString(string &subject, string search, string newRule)
{
    long numPossibilities = count(newRule.begin(), newRule.end(), '|') + 1;
    string original_subject = subject;
    string edited_subject = relevantSubject(subject, search);
    
    //cout << "num possibilities is " << numPossibilities << endl;
    if (numPossibilities>1)
    {
        int previous_replace = -1;
        for (int n=1;n<=numPossibilities;n++)
        {
            //cout << "replacing rule: " << search << " subject: " << subject << endl;
            int pos_replace = findNthOccur(newRule, '|', n);
            string replace = newRule.substr(previous_replace+1,pos_replace-previous_replace-1);
            previous_replace = pos_replace;
            findAndReplaceAll(subject, search, replace);
            if(n<numPossibilities){subject = subject + "|" + edited_subject;}
            //cout << "updated subject is " << subject << endl;
            //cout << "edited subject is " << edited_subject << endl;
        }
    }
   else
   {
       findAndReplaceAll(subject, search, newRule);
   }

    return;
}

bool hasDigits(string str)
{
    for (int i = 0; i < str.size(); i++)
      {
        if (isdigit(str[i]))
        {
            return true;
        }
      }
    return false;
}

bool alreadyConverted(int rule, vector<int> convertedRules)
{
    for (int i = 0; i < convertedRules.size(); i++)
      {
        if (convertedRules[i]==rule)
        {
            return true;
        }
      }
    return false;
}

void updateRules(map<int, string> &rules, int rule2bReplaced, string newRule)
{
    cout << "updating rules ... " << rule2bReplaced << endl; //  " to " << newRule << endl;
    map<int, string>::iterator it;
    for (it = rules.begin(); it != rules.end(); it++)
    {
        string replace = to_string(rule2bReplaced);
        std::size_t found = it->second.find(replace);
        
        if(found!=std::string::npos)
        {
            ReplaceString(it->second, replace, newRule);
        }
    }
    return;
}

void printMap(map<int, string> rules)
{
    map<int, string>::iterator it;
    for (it = rules.begin(); it != rules.end(); it++)
    {
        cout << it->first << ':' << it->second << endl;
    }
    return;
}

string getRule(string rule)
{
    if (rule.find('"') != std::string::npos)
    {
        return rule.substr(1,1);
    }
    else
    {
        return rule;
    }
}

int main()
{
    ifstream file("input.txt");
    string line;
    map<int, string> rules;
    
    vector<string> messages;
    bool getMessages = 0;
  
    while(getline(file,line))
    {
        if (line=="")
        {
            getMessages = 1;
            continue;
        }
        
        if(getMessages)
        {
            messages.push_back(line);
        }
        else
        {
            unsigned long colPos = line.find(": ");
            int ruleNo = stoi(line.substr(0,colPos));
            string rule = line.substr(colPos+2,line.length()-colPos-2);
            rules.insert(pair<int,string>(ruleNo,rule));
        }
    }
    
    
    map<int, string>::iterator it;

    int rule2bReplaced;
    string rule;
    vector<int> convertedRules;
    
    //for(int p=0;p<3;p++)
    do
    {
        for (it = rules.begin(); it != rules.end(); it++)
        {
            if(!hasDigits(it->second)&&!alreadyConverted(it->first,convertedRules))
            {
                rule2bReplaced  = it->first;
                rule = getRule(it->second);
                updateRules(rules, rule2bReplaced, rule);
                convertedRules.push_back(it->first);
            }
        }
        cout << "rules: \n";
        printMap(rules);
    } while(hasDigits(rules.begin()->second));
    
    int validMessages = 0;
    string valid_rules = rules.begin()->second;
    valid_rules.erase (remove (valid_rules.begin(), valid_rules.end(), ' '), valid_rules.end());
    
    //cout << valid_rules;
    
    for (int i =0 ; i<messages.size();i++)
    {
        if (valid_rules.find(messages[i]) != string::npos)
        {
            validMessages++;
        }
    }
    
    cout << "\nNumber of valid messages: " << validMessages << endl;
    return 0;
}
