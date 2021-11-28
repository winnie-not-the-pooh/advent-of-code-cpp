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

struct allergen
{
    string name;
    vector<string> possible_ingredients;
    int nLines = 0;
    string match = "None";
};

void printVector(vector<allergen> vec)
{
    for (int i =0; i<vec.size(); i++)
    {
        cout << vec[i].name;
        cout << " ingredients:";
        for(int s=0;s<vec[i].possible_ingredients.size();s++)
        {
            cout << vec[i].possible_ingredients[s] << "/" ;
        }
        cout << " matches:" << vec[i].match << endl;
    }
    cout << "\n";
    return;
}

void removeSpaces(vector<string> &allergen_list)
{
    for(int s=0;s<allergen_list.size();s++)
    {
        allergen_list[s].erase(remove(allergen_list[s].begin(), allergen_list[s].end(), ' '), allergen_list[s].end());
    }
    return;
}

bool isInAllergens(vector<allergen> allergens, string allergen)
{
    for(int i=0; i<allergens.size();i++)
    {
        if(allergens[i].name.compare(allergen)==0)
        {
            return true;
        }
    }
    
    return false;
}

void addIngredients(vector<allergen> &allergens, string allergen_name, vector<string> vec_ingredient_list)
{
    for(int i =0;i<allergens.size();i++)
    {
            if(allergens[i].name.compare(allergen_name)==0)
            {
                for(int j=0;j<vec_ingredient_list.size();j++)
                {
                    allergens[i].possible_ingredients.push_back(vec_ingredient_list[j]);
                }
                return;
            }
    }
    
    return;
}

bool isInVec(string str, vector<string> v)
{
    for(int i =0;i<v.size();i++)
    {
        if(v[i].compare(str)==0)
        {
            return 1;
        }
    }
    return 0;
}

int countSafeIngredients(string all_ingredients, vector<allergen> allergens)
{
    vector<string> nWords = split(all_ingredients, ' ');
    vector<string> v;
   
    int nSafeIngredients = 0;
    for(int i=0;i<allergens.size();i++)
    {
        v.push_back(allergens[i].match);
    }
    
    for(int j=0;j<nWords.size();j++)
    {
        if(!isInVec(nWords[j], v))
        {
            nSafeIngredients++;
        }
    }
   
    return nSafeIngredients;
}

vector<string> mostFrequent(vector<string> vec)
{
    vector<string> most_frequent;
    map<string, int> frequency;
    for (vector<string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        ++frequency[*it];
        //cout << *it << "," << frequency[*it]  << endl;
    }
   
    int max_count = 0;
    for(map<string, int>::iterator it = frequency.begin(); it != frequency.end(); it++)
    {
        if(it->second > max_count)
        {
            max_count = it->second;
        }
    }
    
    for(map<string, int>::iterator it = frequency.begin(); it != frequency.end(); it++)
    {
        /*if(it->second > 10)
        {
            cout << it->first << ":" << it->second << endl;
        }*/
        
        if(it->second == max_count)
        {
            most_frequent.push_back(it->first);
        }
    }
    
    return most_frequent;
}

void removeIngredients(vector<allergen> &allergens, string toRemove)
{
    for(int i=0; i<allergens.size();i++)
    {
        vector<string> v = allergens[i].possible_ingredients;
        v.erase(remove(v.begin(), v.end(), toRemove), v.end());
        allergens[i].possible_ingredients = v;
    }
    
    return;
}

bool allMatchesFound(vector<allergen> v)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i].match.compare("None")==0)
        {
            return 0;
        }
    }
    
    return 1;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<allergen> allergens;
    vector<string> possible_ingredients;
    string all_ingredients = "";
    
    while(getline(file,line))
    {
        unsigned long containsStart = line.find("(contains ");
    
        if (containsStart!= string::npos)
        {
            string ingredient_list = line.substr(0,containsStart);
            all_ingredients = all_ingredients + ingredient_list;
            vector<string> allergen_list = split(line.substr(containsStart+10,line.length()-containsStart-11),',');
            vector<string> vec_ingredient_list = split(ingredient_list, ' ');
            removeSpaces(allergen_list);
            for(int i=0;i<allergen_list.size();i++)
            {
                string allergen_name = allergen_list[i];
                if(isInAllergens(allergens, allergen_list[i]))
                {
                    addIngredients(allergens, allergen_name, vec_ingredient_list);
                }
                else
                {
                    allergen a;
                    a.name = allergen_name;
                    a.possible_ingredients = vec_ingredient_list;
                    allergens.push_back(a);
                }
            }
            
            continue;
        }
        else
        {
            cout << "*****************This line doesn't have allergens*****************\n" ;
        }
    }
    
    do
    {
        for(int a = 0; a< allergens.size(); a++)
        {
            //cout << "Calculating frequency for " << allergens[a].name << endl;
            vector<string> most_frequent = mostFrequent(allergens[a].possible_ingredients);
            if(most_frequent.size()==1)
            {
                string str_match = most_frequent[0];
                cout << allergens[a].name << " matches " << str_match << endl;
                allergens[a].match = str_match;
                removeIngredients(allergens,  str_match);
            }
        }
    } while(!allMatchesFound(allergens));
    
    cout << endl;
    //printVector(allergens);
    //cout << all_ingredients << endl;
    cout << "Times non-allergen ingredients appear:  " << countSafeIngredients(all_ingredients, allergens) << endl;
    // answer is between 2400 and 2639
    return 0;
}
