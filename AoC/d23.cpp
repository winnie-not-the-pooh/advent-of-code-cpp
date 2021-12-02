#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int getIndex(vector <int> v, int val)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i]==val)
        {
            return i;
        }
    }
    return 0;
}

int getNextCup(vector<int> v, int currCup)
{
    int currIdx = getIndex(v, currCup);
    
    if(currIdx + 1 < v.size())
    {
        return v[currIdx+1];
    }
    else
    {
        return v[0];
    }
}

vector<int> getPickUp(vector<int> v, int idxCurrCup)
{
    // get val of three cups clockwise of current cup
    vector<int> pickUpVal;
    int pickUpIdx = idxCurrCup;
    for(int i = 0; i<3; i++)
    {
        pickUpIdx ++;
        if( pickUpIdx < v.size())
        {
            pickUpVal.push_back(v[pickUpIdx]);
        }
        else
        {
            pickUpIdx = 0;
            pickUpVal.push_back(v[pickUpIdx]);
        }
    }
    return pickUpVal;
}

void PrintCups(vector<int> v, int idxCurrCup)
{
    cout << "cups: ";
    for(int i=0; i<v.size();i++)
    {
        if(i==idxCurrCup)
        {
            cout << "(" << v[i] << ") ";
        }
        else
        {
            cout << v[i] << " ";
        }
    }
    cout << endl;
    return;
}

void PrintPickUp(vector<int> PickUp)
{
    cout << "pick up: ";
    for(int p=0;p<PickUp.size();p++)
    {
        cout << PickUp[p];
        if(p<PickUp.size()-1)
        {
            cout << ", ";
        }
    }
    cout << endl;
    return;
}

int getMaxVal(vector <int> vec_cups)
{
    int maxVal = 0;
    
    for(int i =0; i<vec_cups.size(); i++)
    {
        if(maxVal < vec_cups[i])
        {
            maxVal = vec_cups[i];
        }
    }
    
    return maxVal;
}

void Move(vector <int> &vec_cups, int currentCup, int moveNo)
{
    cout << "-- move " << moveNo << " --\n";
    int idxCurrCup = getIndex(vec_cups, currentCup);
    vector<int> PickUp = getPickUp(vec_cups, idxCurrCup);
    PrintCups(vec_cups, idxCurrCup);
    PrintPickUp(PickUp);
    // erase them from circle
    vec_cups.erase(remove(vec_cups.begin(), vec_cups.end(), PickUp[0]), vec_cups.end());
    vec_cups.erase(remove(vec_cups.begin(), vec_cups.end(), PickUp[1]), vec_cups.end());
    vec_cups.erase(remove(vec_cups.begin(), vec_cups.end(), PickUp[2]), vec_cups.end());

    int destinationCup = currentCup - 1;
    
    int maxVal = getMaxVal(vec_cups);
    bool foundCup = 0;
    do
    {
        if (find(vec_cups.begin(), vec_cups.end(),destinationCup)!=vec_cups.end())
        {
            cout << "destination: " << destinationCup << endl;
            foundCup = 1;
        }
        else
        {
            destinationCup --;
            if(destinationCup<0)
            {
                destinationCup = maxVal;
            }
        }
    } while(!foundCup);
    
    int destinationIdx = getIndex(vec_cups, destinationCup);

    vec_cups.insert(vec_cups.begin()+destinationIdx+1, PickUp[2]);
    vec_cups.insert(vec_cups.begin()+destinationIdx+1, PickUp[1]);
    vec_cups.insert(vec_cups.begin()+destinationIdx+1, PickUp[0]);
    
    cout << endl;
    return;
}

int main()
{
    string cups = "389125467";
    //string cups = "614752839";
    vector <int> vec_cups;
    
    for(int i = 0;i<cups.length();i++)
    {
        string val = cups.substr(i,1);
        vec_cups.push_back(stoi(val));
    }
    
    int currentCup = vec_cups.front();
    int currentCupIdx = 0;
    
    for(int m=1; m<1000002;m++)
    {
        Move(vec_cups, currentCup, m);
        currentCup = getNextCup(vec_cups, currentCup);
    }
   
    return 0;
}
