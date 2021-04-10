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

using namespace std;

unsigned long long program[] =
{
    37
};

unsigned long long program_test[]={
    35,
    20,
    15,
    25,
    47,
    40,
    62,
    55,
    65,
    95,
    102,
    117,
    150,
    182,
    127,
    219,
    299,
    277,
    309,
    576
};

unsigned long long getSum(unsigned long long a, unsigned long long b)
{
    return a+b;
}

void updatePreambleNumbers(int startIdx, int preamble_length, unsigned long long program[], unsigned long long *preamble_numbers)
{
    for(int i = 0; i<preamble_length;i++)
    {
        preamble_numbers[i] = program[startIdx+i];
    }
    return;
}

bool isSumofPreambleNumbers(unsigned long long numToCheck, unsigned long long preamble_numbers[], int preamble_length)
{
    for (int j=0; j<preamble_length; j++)
    {
        for (int k=j+1; k<preamble_length; k++)
        {
            if (getSum(preamble_numbers[j],preamble_numbers[k])==numToCheck)
            {
                cout << getSum(preamble_numbers[j],preamble_numbers[k]) << "=";
                cout << preamble_numbers[j] << "+" << preamble_numbers[k] << endl;
                return 1;
            }
        }
    }
    return 0;
}

void populate_nums_to_add(unsigned long long *numsToAdd,unsigned short contiguous_length,unsigned long long program[], int startIdx)
{
    for (int i=0; i<contiguous_length; i++)
    {
        numsToAdd[i] = program[startIdx+i];
    }
    return;
}

void print_nums_to_add(unsigned long long *numsToAdd,unsigned short contiguous_length)
{
    for (int i=0; i<contiguous_length; i++)
    {
        cout << numsToAdd[i] << " ";
    }
    cout << endl;
    return;
}

unsigned long long minElement(unsigned long long arr[], int nRows)
{
    unsigned long long minVal = 66771724413646;
    for (int i=0; i<nRows; i++)
    {
        if (arr[i]<minVal)
            minVal = arr[i];
    }
    return minVal;
}

unsigned long long maxElement(unsigned long long arr[], int nRows)
{
    unsigned long long maxVal = 0;
    for (int i=0; i<nRows; i++)
    {
        if (arr[i]>maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

void FirstPart()
{
    int preamble_length = 25;
    int nRows = sizeof(program)/sizeof(program[0]);
    
    unsigned long long preamble_numbers[preamble_length];
    
    for (int i=preamble_length;i<nRows;i++)
    {
        updatePreambleNumbers(i-preamble_length,preamble_length, program,preamble_numbers);
        if (!isSumofPreambleNumbers(program[i], preamble_numbers, preamble_length))
        {
            cout << "The number is " << program[i] << endl;
            abort();
        }
    }
    return;
}

void SecondPart()
{
    unsigned long long goalSum = 177777905;
    unsigned long long currentSum = 0;
    int nRows = sizeof(program)/sizeof(program[0]);
    
    for (int k=2; k<nRows; k++)
    {
        unsigned short contiguous_length = k;
        unsigned long long numsToAdd[contiguous_length];

        for (int i=0; i<(nRows-contiguous_length+1);i++)
        {
            currentSum = 0;
            populate_nums_to_add(numsToAdd,contiguous_length,program, i);
            //print_nums_to_add(numsToAdd, contiguous_length);
            for (int j=0; j<contiguous_length; j++)
            {
                currentSum = getSum(currentSum,numsToAdd[j]);
            }
            if (currentSum==goalSum)
            {
                printf("The smallest and largest numbers are %llu, %llu\n",minElement(numsToAdd,contiguous_length),maxElement(numsToAdd,contiguous_length));
                abort();
            }
        }
    }
    return;
}
int main()
{
    FirstPart();
    SecondPart();
    return 0;
}
