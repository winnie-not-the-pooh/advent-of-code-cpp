#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

long calculateFuel(long input)
{
    return (floor(input / 3.0)-2>0?floor(input / 3.0)-2:0);
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<long> mass;
    
    while(getline(file,line))
    {
        mass.push_back(stoi(line));
    }
    
    long total_fuel_req1 = 0;
    long total_fuel_req2 = 0;
    
    for(int i=0; i<mass.size();i++)
    {
        cout << "Mass : " << mass[i] << endl;
        
        long fuel = calculateFuel(mass[i]);
        total_fuel_req1 = total_fuel_req1 + fuel;
        
        long total_fuel_fuel = fuel;
        
        while(fuel>0)
        {
            fuel = calculateFuel(fuel);
            total_fuel_fuel = total_fuel_fuel + fuel;
        }
        
        total_fuel_req2 = total_fuel_req2 + total_fuel_fuel;
    }
    cout << "Total fuel required for part one: " << total_fuel_req1 << endl;
    cout << "Total fuel required for part two: " << total_fuel_req2 << endl;
    return 0;
}
