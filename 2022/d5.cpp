#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string line;
    
    vector<vector<char>> stacks;
    
    vector<char> stackOne;
    vector<char> stackTwo;
    vector<char> stackThree;
    vector<char> stackFour;
    vector<char> stackFive;
    vector<char> stackSix;
    vector<char> stackSeven;
    vector<char> stackEight;
    vector<char> stackNine;
    
    /* for test input */
    /*ifstream file("input_test.txt");
    stackOne.push_back('Z');
    stackOne.push_back('N');
    stackTwo.push_back('M');
    stackTwo.push_back('C');
    stackTwo.push_back('D');
    stackThree.push_back('P');*/
    /* end test input */
    
    /* for real input */
    ifstream file("input.txt");
    stackOne.push_back('B');
    stackOne.push_back('Z');
    stackOne.push_back('T');
    stackTwo.push_back('V');
    stackTwo.push_back('H');
    stackTwo.push_back('T');
    stackTwo.push_back('D');
    stackTwo.push_back('N');
    stackThree.push_back('B');
    stackThree.push_back('F');
    stackThree.push_back('M');
    stackThree.push_back('D');
    stackFour.push_back('T');
    stackFour.push_back('J');
    stackFour.push_back('G');
    stackFour.push_back('W');
    stackFour.push_back('V');
    stackFour.push_back('Q');
    stackFour.push_back('L');
    stackFive.push_back('W');
    stackFive.push_back('D');
    stackFive.push_back('G');
    stackFive.push_back('P');
    stackFive.push_back('V');
    stackFive.push_back('F');
    stackFive.push_back('Q');
    stackFive.push_back('M');
    stackSix.push_back('V');
    stackSix.push_back('Z');
    stackSix.push_back('Q');
    stackSix.push_back('G');
    stackSix.push_back('H');
    stackSix.push_back('F');
    stackSix.push_back('S');
    stackSeven.push_back('Z');
    stackSeven.push_back('S');
    stackSeven.push_back('N');
    stackSeven.push_back('R');
    stackSeven.push_back('L');
    stackSeven.push_back('T');
    stackSeven.push_back('C');
    stackSeven.push_back('W');
    stackEight.push_back('Z');
    stackEight.push_back('H');
    stackEight.push_back('W');
    stackEight.push_back('D');
    stackEight.push_back('J');
    stackEight.push_back('N');
    stackEight.push_back('R');
    stackEight.push_back('M');
    stackNine.push_back('M');
    stackNine.push_back('Q');
    stackNine.push_back('L');
    stackNine.push_back('F');
    stackNine.push_back('D');
    stackNine.push_back('S');
    /* end real input */
    
    stacks.push_back(stackOne);
    stacks.push_back(stackTwo);
    stacks.push_back(stackThree);
    stacks.push_back(stackFour);
    stacks.push_back(stackFive);
    stacks.push_back(stackSix);
    stacks.push_back(stackSeven);
    stacks.push_back(stackEight);
    stacks.push_back(stackNine);
    
    while(getline(file,line))
    {
        size_t from_pos = line.find(" from ");
        
        int amt = stoi(line.substr(5,from_pos-5));
        int from = stoi(line.substr(from_pos+6,1));
        int to = stoi(line.substr(from_pos+11,1));
        
        cout << line << endl;
        
        /* part one */
        /*for(int i=0;i<amt;i++)
        {
            stacks[to-1].push_back(stacks[from-1].back());
            stacks[from-1].pop_back();
        }*/
        
        string newString = "";
        for(int i=0;i<amt;i++)
        {
            long back_index = stacks[from-1].size()-1;
            newString = newString + stacks[from-1][back_index-i];
        }
        
        for(long j=newString.length()-1;j>=0;j--)
        {
            stacks[from-1].pop_back();
            stacks[to-1].push_back(newString[j]);
        }
    }
     
    //cout << "The top letter for each stack: " << stacks[0].back() << stacks[1].back() << stacks[2].back() << endl;
    
    cout << "The top letter for each stack: " << stacks[0].back() << stacks[1].back() << stacks[2].back() << stacks[3].back() << stacks[4].back() << stacks[5].back() << stacks[6].back() << stacks[7].back() << stacks[8].back() << endl;
    return 0;
}
