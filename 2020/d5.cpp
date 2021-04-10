#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>
#include<math.h>
#include<algorithm>

using namespace std;

string seats[] =
{
    "FBBBFBBLRR"
    // input the rest
};

int returnVal(int i)
{
    return floor(63.0/pow(2.0,i));
}

int main()
{
    int nRows = sizeof(seats)/sizeof(seats[0]);
    int seatId[nRows];

    for (int i=0; i<nRows; i++)
    {
        string currSeat = seats[i];
        
        int minSeatRow = 0;
        int maxSeatRow = 127;
        int minSeatCol = 0;
        int maxSeatCol = 7;
        
        for (int j=0; j<7;j++)
        {
            if(currSeat[j]=='F')
            {
                maxSeatRow = minSeatRow + returnVal(j);
                 
            }
            else if(currSeat[j]=='B')
            {
                minSeatRow = maxSeatRow - returnVal(j);
            }
        }

        for(int j=7; j<10; j++)
        {
            int sum = 3;
            if (j==8)
            {sum=1;}
            else if(j==9)
            {sum=0;}

            if(currSeat[j]=='L')
            {
                maxSeatCol = minSeatCol + sum;
            }
            else if(currSeat[j]=='R')
            {
                minSeatCol = maxSeatCol - sum;
            }
        }
        
        seatId[i]=minSeatRow*8+minSeatCol;
    }

    cout << "The highest seat ID is: ";
    
    int highestSeatId = 0;
    for (int k=0; k<nRows; k++)
    {
        if(seatId[k]>highestSeatId)
            highestSeatId = seatId[k];
    }
    cout << highestSeatId << endl;
    
    //sort(seatId); paste in Google Sheets #501 for p2

    return 0;
}

