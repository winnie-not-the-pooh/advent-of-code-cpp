#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>

using namespace std;

unsigned long findFirstSpace(long startPos, string str)
{
    return str.substr(startPos,str.length()-startPos).find(' ');
}

int main()
{
    ifstream file("input.txt");
    string line;

    int valPassports_p1 = 0;
    int valPassports_p2 = 0;

    bool hasByr = 0;
    bool hasIyr = 0;
    bool hasEyr = 0;
    bool hasHgt = 0;
    bool hasHcl = 0;
    bool hasEcl = 0;
    bool hasPid = 0;
    
    bool byr_val = 0;
    bool iyr_val = 0;
    bool eyr_val = 0;
    bool hgt_val = 0;
    bool hcl_val = 0;
    bool ecl_val = 0;
    bool pid_val = 0;

    while(getline(file,line))
    {
        if (line.find("byr:")!=string::npos)
        {
            hasByr=1;
            unsigned long byr_start = line.find("byr:");
            unsigned int byr = stoi(line.substr(byr_start+4,findFirstSpace(byr_start, line)-4));
            if(byr>=1920 && byr<=2002)
            {byr_val=1;}
        }
        if (line.find("iyr:")!=string::npos)
        {
            hasIyr=1;
            unsigned long iyr_start = line.find("iyr:");
            unsigned int iyr = stoi(line.substr(iyr_start+4,findFirstSpace(iyr_start, line)-4));
            if(iyr>=2010 && iyr<=2020)
            {iyr_val=1;}
        }
        if (line.find("eyr:")!=string::npos)
        {
            hasEyr=1;
            unsigned long eyr_start = line.find("eyr:");
            unsigned int eyr = stoi(line.substr(eyr_start+4,findFirstSpace(eyr_start, line)-4));
            if(eyr>=2020 && eyr<=2030)
            {eyr_val=1;}
        }
        if (line.find("hgt:")!=string::npos)
        {
            hasHgt=1;
            unsigned long hgt_start = line.find("hgt:");
            string hgt = line.substr(hgt_start+4,findFirstSpace(hgt_start, line)-4);
            string unit = hgt.substr(hgt.length()-2,2);
            if(unit == "cm" || unit == "in")
            {
                unsigned long height_val = stol(hgt.substr(0,hgt.length()-2));
                if(
                   (unit == "cm" && (height_val>=150 && height_val <= 193)) ||
                   (unit == "in" && (height_val>=59  && height_val <= 76))
                   )
                {
                    hgt_val=1;
                }
            }
        }
        if (line.find("hcl:")!=string::npos)
        {
            hasHcl=1;
            unsigned long hcl_start = line.find("hcl:");
            regex regexp("#[a-f0-9]{6}");
            string stringToMatch = line.substr(hcl_start+4,findFirstSpace(hcl_start, line)-4);
            if(regex_match(stringToMatch,regexp))
            {hcl_val=1;}
        }
        if (line.find("ecl:")!=string::npos)
        {
            hasEcl=1;
            string ecl = line.substr(line.find("ecl:")+4,3);
            if(ecl=="amb" || ecl=="blu" || ecl=="brn" || ecl=="gry" || ecl=="grn" || ecl=="hzl" || ecl=="oth")
            {ecl_val=1;}
        }
        if (line.find("pid:")!=string::npos)
        {
            hasPid=1;
            unsigned long pid_start = line.find("pid:");
            string stringToMatch = line.substr(pid_start+4,findFirstSpace(pid_start, line)-4);
            regex regexp("[0-9]{9}");
            if(regex_match(stringToMatch,regexp))
            {pid_val=1;}
        }

        if(line=="")
        {
            if (hasByr && hasIyr && hasEyr && hasHgt && hasHcl && hasEcl && hasPid)
            {valPassports_p1++;}
            
            if (byr_val && iyr_val && eyr_val && hgt_val && hcl_val && ecl_val && pid_val)
            {valPassports_p2++;}

            hasByr = 0;
            hasIyr = 0;
            hasEyr = 0;
            hasHgt = 0;
            hasHcl = 0;
            hasEcl = 0;
            hasPid = 0;
            
            byr_val = 0;
            iyr_val = 0;
            eyr_val = 0;
            hgt_val = 0;
            hcl_val = 0;
            ecl_val = 0;
            pid_val = 0;
        }
    }
    printf ("The number of valid passports for p1 and p2 are %i, %i. \n", valPassports_p1, valPassports_p2);
    return 0;
}
