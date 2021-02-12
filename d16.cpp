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
#include<sstream>

using namespace std;

struct range
{
    int min, max;
};

struct field
// stores limits on which values CANNOT be contained by this field
// ie. 0->max1 and min2->max2 and max3->
{
    string name;
    int max1;
    int min2;
    int max2;
    int max3;
};

void FirstPart()
{
    ifstream file("input.txt");
    string line;

    bool read_requirements = 0;
    bool get_tickets = 0;
    int error_rate = 0;
    
    vector<range> Ranges;

    while(getline(file,line))
    {
        if(line=="")
        {
            read_requirements = 1;
        }
        else if(line=="nearby tickets:")
        {
            get_tickets = 1;
            continue;
        }
        
        if (!read_requirements)
        {
            regex regexp(" or ");
            smatch m;
            regex_search(line,m,regexp);
            
            range one;
            one.min = stoi(line.substr(line.find(":")+2,line.find("-")-line.find(":")-2));
            one.max = stoi(line.substr(line.find("-")+1,3));
            
            range two;
            two.min = stoi(line.substr(m.position(0)+4,3));
            two.max = stoi(line.substr(line.length()-3,3));
            
            Ranges.push_back(one);
            Ranges.push_back(two);
        }
        
        else if(get_tickets)
        {
            vector<int> ticket;
            stringstream ss(line);
            while(ss.good())
            {
                string substr;
                getline( ss, substr, ',' );
                ticket.push_back(stoi(substr));
            }
            
            bool isValid = 0;
            for (int i =0; i<ticket.size();i++)
            {
                isValid = 0;
                int value = ticket[i];
                for(int j=0;j<Ranges.size();j++)
                {
                    if(value>=Ranges[j].min && value<=Ranges[j].max)
                    {
                        isValid = 1;
                    }
                }
                if(!isValid)
                {
                    error_rate = error_rate+value;
                    // cout << line << endl; // invalid tickets for use in part two
                }
            }
        }
    }
    
   printf("Ticket error scanning rate: %i.\n", error_rate);
    
    return;
}

void read_requirements(vector<field> &Fields)
{
    ifstream file("input.txt");
    string line;

    while(getline(file,line))
    {
        if(line=="")
        {
            break;
        }
        
        regex regexp(" or ");
        smatch m;
        regex_search(line,m,regexp);
        
        field fld;
        fld.name = line.substr(0,line.find(":"));
        fld.max1 = stoi(line.substr(line.find(":")+2,line.find("-")-line.find(":")-2))-1;
        fld.min2 = stoi(line.substr(line.find("-")+1,3))+1;
        fld.max2 = stoi(line.substr(m.position(0)+4,3))-1;
        fld.max3 = stoi(line.substr(line.length()-3,3))+1;
        Fields.push_back(fld);
    }
    return;
}

void read_tickets(vector<string>&tickets)
{
    ifstream file("input_tickets.txt"); // contains all tickets including invalid and your own ticket
    string line;

    while(getline(file,line))
    {
        if(line=="")
        {
            break;
        }
        tickets.push_back(line);
    }
    
    ifstream filei("invalid_tickets.txt"); // contains invalid tickets retrieved from part 1
    string linei;

    while(getline(filei,linei))
    {
        tickets.erase(remove(tickets.begin(), tickets.end(), linei), tickets.end());
    }
    
    return;
}

bool is_valid(field fld,  vector<int> ticket_column)
{
    for (int i =0; i< ticket_column.size(); i++)
    {
        int val = ticket_column[i];
        if(val<=fld.max1 || val>=fld.max3 || (val>=fld.min2 && val <=fld.max2))
        {
            return 0;
        }
    }
    return 1;
}

void SecondPart()
{
    vector<field> Fields;
    vector<string> Tickets;
    
    read_requirements(Fields);
    
    read_tickets(Tickets);
    
    unsigned long nTickets = Tickets.size();
    unsigned long ticket_length = count(Tickets[0].begin(), Tickets[0].end(), ',')+1; //20
    int tickets[nTickets][ticket_length];

    // convert Tickets vec to 2d array
    int i_counter = 0;
    int j_counter = 0;
    
    for (int i =0; i<nTickets;i++)
    {
        stringstream ss(Tickets[i]);
        while( ss.good() )
        {
            string substr;
            getline( ss, substr, ',' );
            tickets[i_counter][j_counter] = stoi(substr);
            j_counter++;
            if(j_counter>=ticket_length)
            {
                j_counter = 0;
                i_counter++;
            }
        }
    }
    
    for (int fld = 0; fld < Fields.size(); fld++)
    {
        vector<int> col_numbers;
        
        for (int col =0; col<ticket_length; col++)
        {
            vector<int> ticket_column;
            
            for (int j=0; j<nTickets; j++)
            {
                ticket_column.push_back(tickets[j][col]);
            }
            
            if(is_valid(Fields[fld],  ticket_column))
            {
                col_numbers.push_back(col);
            }
        }
        cout << Fields[fld].name <<  " can be the following columns: \n";
        
        for (int i =0; i< col_numbers.size(); i++)
        {cout << col_numbers[i] << " ";}
        cout << endl;
    }
    return;
}

int main()
{
    FirstPart();
    SecondPart();
    return 0;
}
