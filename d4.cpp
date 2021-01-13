#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>

using namespace std;
       
int main()
{
    ifstream file("input.txt");
    string line;

    int valPassports_p1 = 0;
    int valPassports_p2 = 0;

    bool hasByr_p1 = 0;
    bool hasIyr_p1 = 0;
    bool hasEyr_p1 = 0;
    bool hasHgt_p1 = 0;
    bool hasHcl_p1 = 0;
    bool hasEcl_p1 = 0;
    bool hasPid_p1 = 0;
    
    bool hasByr_p2 = 0;
    bool hasIyr_p2 = 0;
    bool hasEyr_p2 = 0;
    bool hasHgt_p2 = 0;
    bool hasHcl_p2 = 0;
    bool hasEcl_p2 = 0;
    bool hasPid_p2 = 0;

    while(getline(file,line))
    {
        if (line.find("byr:")!=string::npos)
        {
            hasByr_p1=1;
            int byr = stoi(line.substr(line.find("byr:")+4,4));
            if(byr>=1920 && byr<=2002)
            {hasByr_p2=1;}
        }
        if (line.find("iyr:")!=string::npos)
        {
            hasIyr_p1=1;
            int iyr = stoi(line.substr(line.find("iyr:")+4,4));
            if(iyr>=2010 && iyr<=2020)
            {hasIyr_p2=1;}
        }
        if (line.find("eyr:")!=string::npos)
        {
            hasEyr_p1=1;
            int eyr = stoi(line.substr(line.find("eyr:")+4,4));
            if(eyr>=2020 && eyr<=2030)
            {hasEyr_p2=1;}
        }
        if (line.find("hgt:")!=string::npos)
        {
            hasHgt_p1=1;
            
            string hgt = line.substr(line.find("hgt:")+4,5);
            if(hgt.find("cm")!=string::npos)
            {
                try
                {
                    int hgtCm = stoi(hgt.substr(hgt.find("cm")-3,3));
                    if(hgtCm>=150 && hgtCm <= 193)
                    {hasHgt_p2=1;}
                }
                catch (...) {}
            }
           else if(hgt.find("in")!=string::npos)
            {
                int hgtIn = stoi(hgt.substr(hgt.find("in")-2,2));
                if(hgtIn>=59 && hgtIn <= 76)
                {hasHgt_p2=1;}
            }
        }
        if (line.find("hcl:")!=string::npos)
        {
            hasHcl_p1=1;
            regex regexp("#[a-f0-9]{6}");
            if(regex_match(line.substr(line.find("hcl:")+4,7),regexp))
            {hasHcl_p2=1;}
        }
        if (line.find("ecl:")!=string::npos)
        {
            hasEcl_p1=1;
            string ecl = line.substr(line.find("ecl:")+4,3);
            if(ecl=="amb" || ecl=="blu" || ecl=="brn" || ecl=="gry" || ecl=="grn" || ecl=="hzl" || ecl=="oth")
            {hasEcl_p2=1;}
        }
        if (line.find("pid:")!=string::npos)
        {
            hasPid_p1=1;
            regex regexp("[0-9]{9}");
            if(regex_match(line.substr(line.find("pid:")+4,9),regexp))
            {hasPid_p2=1;}
        }

        if(line=="")
        {
            if (hasByr_p1 && hasIyr_p1 && hasEyr_p1 && hasHgt_p1 && hasHcl_p1 && hasEcl_p1 && hasPid_p1)
            {
                valPassports_p1++;
                if (hasByr_p2 && hasIyr_p2 && hasEyr_p2 && hasHgt_p2 && hasHcl_p2 && hasEcl_p2 && hasPid_p2)
                valPassports_p2++;
            }

            hasByr_p1 = 0;
            hasIyr_p1 = 0;
            hasEyr_p1 = 0;
            hasHgt_p1 = 0;
            hasHcl_p1 = 0;
            hasEcl_p1 = 0;
            hasPid_p1 = 0;
            
            hasByr_p2 = 0;
            hasIyr_p2 = 0;
            hasEyr_p2 = 0;
            hasHgt_p2 = 0;
            hasHcl_p2 = 0;
            hasEcl_p2 = 0;
            hasPid_p2 = 0;
        }
    }
    printf ("The number of valid passports for p1 and p2 are %i, %i. \n", valPassports_p1, valPassports_p2); //skips the last line, and part 2 is off by a bit (over counts by 2)
    return 0;
}

