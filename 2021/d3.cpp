#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

vector<string> determineRating(vector<string> v, int pos, int type)
{
    int zero_counter = 0;
    int one_counter = 0;
    
    vector<string> new_vec;
    
    for(int r=0;r<v.size();r++)
    {
        if(v[r][pos]=='0')
        {
            zero_counter ++;
        }
        else
        {
            one_counter++;
        }
    }
    
    //cout << "for pos " << pos << " the 0 and 1 counter " << zero_counter << "," << one_counter << endl;
    
    for(int i=0;i<v.size();i++)
    {
        if(type == 1)
        {
            if((v[i][pos]=='1' && (one_counter > zero_counter)) || (v[i][pos]=='0' && (zero_counter > one_counter)))
            {
                new_vec.push_back(v[i]);
            }
            else if(one_counter == zero_counter && v[i][pos]=='1')
            {
                new_vec.push_back(v[i]);
            }
        }
       else if(type == 2)
        {
            if((v[i][pos]=='0' && (one_counter > zero_counter)) || (v[i][pos]=='1' && (zero_counter > one_counter)))
            {
                new_vec.push_back(v[i]);
            }
            else if(one_counter == zero_counter && v[i][pos]=='0')
            {
                new_vec.push_back(v[i]);
            }
        }
    }
    
    return new_vec;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<string> readings;
    
    while(getline(file,line))
    {
        readings.push_back(line);
    }
    
    string gamma_rate = "";
    string eps_rate = "";
    int zero_counter = 0;
    int one_counter = 0;
    
    for(int l=0;l<readings[0].length();l++)
    {
        for(int i=0;i<readings.size();i++)
        {
            if(readings[i][l]=='0')
            {
                zero_counter ++ ;
            }
            else
            {
                one_counter++;
            }
        }
        
        if(zero_counter > one_counter)
        {
            gamma_rate = gamma_rate + "0";
            eps_rate = eps_rate + "1";
            
        }
        else //if (one_counter > zero_counter)
        {
            gamma_rate = gamma_rate + "1";
            eps_rate = eps_rate + "0";
        }
        zero_counter = 0;
        one_counter = 0;
    }
    
    cout << "gamma rate is " << gamma_rate << endl;
    cout << "epsilon rate is " << eps_rate << endl;
    cout << "power consumption is: " << stoi(gamma_rate, 0, 2) * stoi(eps_rate, 0, 2) << endl;

    vector<string> vec_oxy;
    vector<string> vec_co2;
    
    vec_oxy = determineRating(readings, 0, 1);
    vec_co2 = determineRating(readings, 0, 2);
    
    for(int k=1;k<readings[0].length();k++)
    {
        vec_oxy = determineRating(vec_oxy, k, 1);
        if(vec_oxy.size()==1)
        {
            break;
        }
    }
    
    for(int k=1;k<readings[0].length();k++)
    {
        vec_co2 = determineRating(vec_co2, k, 2);
        if(vec_co2.size()==1)
        {
            break;
        }
    }
    
    cout << "oxygen generator rate is " << vec_oxy[0] << endl;
    cout << "CO2 scrubber rate is " << vec_co2[0] << endl;
    cout << "life support rating is: " << stoi(vec_oxy[0], 0, 2) * stoi(vec_co2[0], 0, 2) << endl;
    
    return 0;
}
