#include <iostream>
#include<string>
#include <array>

using namespace std;

int minVals[] = {
    4
    // input the rest
};

char passChar[] = {
    'n'
  // input the rest
};

string passwords[] =
{
    "dnjjrtclnzdnghnbnn"
    // input the rest
};

void FirstHalf()
{
    int valPasswords = 0;
    int lenth_array = sizeof(minVals)/sizeof(minVals[0]);

    for (int i=0; i<lenth_array; i++)
    {
        int numOccurrances = 0;

        int minimum_val = minVals[i];
        int maximum_val = maxVals[i];
        char password_char = passChar[i];
        string curr_password = passwords[i];

        for (int j=0; j<curr_password.length(); j++)
        {
            if (curr_password[j]==password_char)
            {
                numOccurrances++;
            }
        }
        if (numOccurrances >= minimum_val && numOccurrances <= maximum_val)
        {
            valPasswords++;
        }

    }
    cout << "The number of valid passwords are: ";
    cout << valPasswords << endl;
    return;
}

void SecondHalf()
{
    int valPasswords = 0;
    int lenth_array = sizeof(minVals)/sizeof(minVals[0]);

    for (int i=0; i<lenth_array; i++)
    {
        int val1 = minVals[i];
        int val2 = maxVals[i];
        char password_char = passChar[i];
        string curr_password = passwords[i];

        if (curr_password[val1-1] == password_char ^ curr_password[val2-1] == password_char)
        {
            valPasswords++;
            // cout << i <<",";
        }

    }
    cout << "The number of valid passwords are: ";
    cout << valPasswords << endl;
    return;
}

int main()
{
    FirstHalf();
    SecondHalf();
    return 0;
}


