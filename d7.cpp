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

using namespace std;

using Contains_t = map<string, map<string, uint32_t>>; // need this map of map to store # bags

struct Contains_s
{
    string bagType;
    int numBags;
    int numParentBags;
};

string getBagType(string s)
{
    auto char_arr = &s[0]; // convert string to char_array
    char * pch;
    pch = strtok(char_arr, " ");
    
    string bagType ="";
    
    for (int i = 0; i<2; i++) // bag type is first two words of line
    {
        bagType.append(pch);
        pch = strtok (NULL, " ");
    }
    return bagType;
}

string removeStuff(string str)
{
    string strToRemove[]={"bags", "bag","."};
    int nThingstoRemove = sizeof(strToRemove)/sizeof(strToRemove[0]);
    
    for (int i=0; i<nThingstoRemove; i++)
    {
        if(str.find(strToRemove[i])!=str.npos)
        {
            auto startPos = str.find(strToRemove[i]);
            auto len = strToRemove[i].length();
            str.erase(startPos,len);
        }
    }
    
    str.erase(remove (str.begin(), str.end(), ' '), str.end());
    str.erase(remove (str.begin(), str.end(), ','), str.end());
    
    return str;
}

int findNthOccur(string str,
                 char ch, int N)
{
    int occur = 0;
  
    // Loop to find the Nth
    // occurence of the character
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

int main() {
    
    ifstream file("input.txt");
    string line;
    
    multimap<string, string> whichContains; // element is outer bag
    Contains_t Contains; //element is inner bag

    while(getline(file,line))
    {
        string bagType = getBagType(line);
        string contains = line.substr(line.find("contain ")+8,line.length()-line.find("contain ")-8);
        string contains1 = "";
        string contains2 = "";
        string contains3 = "";
        string contains4 = "";
        
        int num1=0;
        int num2=0;
        int num3=0;
        int num4=0;

        regex regexp("[0-9]");
        size_t numCommas = count(contains.begin(), contains.end(), ',');

        if(regex_search(contains,regexp))
        {
            contains1 = contains.substr(2,contains.find(", ")-2);
            contains1 = removeStuff(contains1);

            num1 = stoi(contains.substr(0,1));
        }
        if(contains.find(", ")!=string::npos)
        {
            if(numCommas==1)
            {
                contains2 = contains.substr(contains.find(", ")+4, contains.length()-contains.find(", "));
                contains2 = removeStuff(contains2);

                num2 = stoi(contains.substr(contains.find(", ")+2, 1));
            }
            else if(numCommas==2) // three bags, or two commas
            {
                contains2 = contains.substr(contains.find(", ")+4,findNthOccur(contains,',',2)-contains.find(", ")-2);
                contains3 = contains.substr(findNthOccur(contains,',',2)+4,contains.length());

                contains2 = removeStuff(contains2);
                contains3 = removeStuff(contains3);

                num2 = stoi(contains.substr(contains.find(", ")+2, 1));
                num3 = stoi(contains.substr(findNthOccur(contains,',',2)+2, 1));
            }
            else // four bags, or three commas
            {
                contains2 = contains.substr(contains.find(", ")+4,findNthOccur(contains,',',2)-contains.find(", ")-2);
                contains3 = contains.substr(findNthOccur(contains,',',2)+4,findNthOccur(contains,',',3)-findNthOccur(contains,',',2)-2);
                contains4 = contains.substr(findNthOccur(contains,',',3)+4,contains.length());

                contains2 = removeStuff(contains2);
                contains3 = removeStuff(contains3);
                contains4 = removeStuff(contains4);

                num2 = stoi(contains.substr(contains.find(", ")+2, 1));
                num3 = stoi(contains.substr(findNthOccur(contains,',',2)+2, 1));
                num4 = stoi(contains.substr(findNthOccur(contains,',',3)+2, 1));
            }
        }
        
        if (contains1!="")
        {
            whichContains.insert(pair<string, string>(contains1, bagType));
            Contains[bagType][contains1] = num1;
        }
        if (contains2!="")
        {
            whichContains.insert(pair<string, string>(contains2, bagType));
            Contains[bagType][contains2] = num2;
        }
        if (contains3!="")
        {
            whichContains.insert(pair<string, string>(contains3, bagType));
            Contains[bagType][contains3] = num3;
        }
        if (contains4!="")
        {
            whichContains.insert(pair<string, string>(contains4, bagType));
            Contains[bagType][contains4] = num4;
        }
    }
    
    /*map<string, string>::iterator itr;
        cout << "\tKEY\t\t\t\tELEMENT (outer bag)\n";
        for (itr = whichContains.begin(); itr != whichContains.end(); ++itr) {
            cout << '\t' << itr->first
                 << '\t' << itr->second << '\n';
        }
        cout << endl;*/
    
    /*cout << "\tKEY\t\t\t\tELEMENT (inner bags)\n";
    for (map <string, map<string, uint32_t>>::iterator it = Contains.begin(); it != Contains.end(); ++it)
    {
        cout << it->first << "\t\t\t";
        map<string, uint32_t> &internal_map = it->second;
        for (map<string, uint32_t>::iterator it2 = internal_map.begin(); it2 != internal_map.end(); ++it2)
        {
            if (it2 != internal_map.begin())
                cout << ",";
            cout << it2->first << ":" << it2->second;
        }
        cout << "\n";
    }
    cout << "\n\n\n";*/
    
    /* FIRST PART */
    map<string, string>::iterator it;

    vector<string> bagsContaining;
    set<string> uniqueBagsContaining;

    bagsContaining.push_back("shinygold");
    string bagToLookFor;

    while(!bagsContaining.empty())
    {
        bagToLookFor = *bagsContaining.begin();
        it = whichContains.find(bagToLookFor);
        if(it != whichContains.end())
        {
            bagsContaining.push_back(it->second);
            whichContains.erase (it);
            uniqueBagsContaining.insert(it->second);
        }
        else
        {
            bagsContaining.erase(bagsContaining.begin());
        }
    }
    printf ("# bags that can contain shiny gold: %lu.\n", uniqueBagsContaining.size());
    
    /* SECOND PART */
    
    map<string, map<string, uint32_t>>::iterator itr;
    map<string, uint32_t>::iterator it2;

    int totalBagsContained = 0;

    vector<Contains_s> bagsContained;

    Contains_s bag;
    bag.bagType = "shinygold";
    bag.numBags = 1;
    bag.numParentBags = 1;

    bagsContained.push_back(bag);

    while(!bagsContained.empty())
    {
        string bagToLookFor = bagsContained.front().bagType;
        int numParentBags = bagsContained.front().numBags*bagsContained.front().numParentBags;
        itr = Contains.find(bagToLookFor);

        if(itr != Contains.end())
        {
            map<string, uint32_t> &internal_map = itr->second;
            for (it2 = internal_map.begin(); it2 != internal_map.end(); ++it2)
            {
                Contains_s bag;
                bag.bagType = it2->first;
                bag.numBags = it2->second;
                bag.numParentBags = numParentBags;
                bagsContained.push_back(bag);

                totalBagsContained = totalBagsContained + numParentBags*it2->second;
            }
        }
        bagsContained.erase(bagsContained.begin());
    }
    
    printf ("# bags that are inside the shiny gold bag: %i.\n", totalBagsContained);
    return 0;
}

