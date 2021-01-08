#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

int numbers[] =
{
    // input number list here
};

void FirstHalf()
{
    int nRows = sizeof(numbers)/sizeof(numbers[0]);
    for (int i=0; i<nRows; i++)
    {
        int num1 = numbers[i];
        for (int j=i+1; j<nRows; j++ )
        {
            if (num1 + numbers[j] == 2020)
            {
                printf ("The product of %i and %i are: %i\n", num1, numbers[j],  num1*numbers[j]);
            }
        }
    }
    return;
}

void SecondHalf()
{
    int nRows =sizeof(numbers)/sizeof(numbers[0]);
    for (int i=0; i<nRows-2; i++)
    {
        int num1 = numbers[i];
        for (int j=i+1; j<nRows-1; j++ )
        {
            int num2 = numbers[j];
            if (num1+num2 > 2020)
                continue;
            for (int k=j+1; k<nRows; k++)
            {
                int num3 =numbers[k];
                if (num1 + num2 + num3 == 2020)
                {
                    printf("The product of %i, %i and %i are: %i\n",num1,num2,num3,num1*num2*num3);
                }
            }
        }
    }
    return;
}

int main()
{
    FirstHalf();
    SecondHalf();
    return 0;
}
