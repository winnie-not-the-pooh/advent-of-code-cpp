#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    int x = 0;
    int z = 0;
    int aim = 0;
    
    vector<int> readings;
    
    while(getline(file,line))
    {
        string dir = line.substr(0,line.find(" "));
        int amt = stoi(line.substr(line.find(" ")+1,1));
        
        if(dir.compare("forward")==0)
        {
            x = x + amt;
            z = z + amt * aim;
        }
        else if (dir.compare("down")==0)
        {
            //z = z + amt;
            aim = aim + amt;
        }
        else
        {
            //z = z - amt;
            aim = aim - amt;
        }
    }
    
    cout << "final reading: x = " << x << " z = " << z << ".\nProduct of the two is " << x*z << endl;

    return 0;
}
