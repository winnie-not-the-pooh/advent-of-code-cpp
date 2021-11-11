#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

long transform(long subject, long loop_size)
{
    long val = 1;
    for(int i=0; i<loop_size; i++)
    {
        val = val * subject;
        val = val % 20201227;
    }
    
    return val;
}

int main()
{

    long card_loop_size=0;
    long door_loop_size=0;
    
    bool found = 0;
    
    long i = 1;
    
    long card_pk =  2069194;
    long door_pk =  16426071;
    
    long val = 1;
    
    cout << "Finding card loop size ... \n";
    do
    {
        cout << "iteration " << i << endl;
        
        //cout << "i = " << i;
        val = val * 7;
        val = val % 20201227;
        //cout << " val = " << val << endl;
        
        if(val == card_pk)
        {
            cout << "the card loop size is " << i << endl;
            card_loop_size = i;
            found = 1;
        }
        if(val == door_pk)
        {
            cout << "the door loop size is " << i << endl;
            door_loop_size = i;
            found = 1;
        }
        else
        {
            i++;
        }
        
    } while (!found);
    
    long encryption_key;
    
    if (card_loop_size!=0)
    {
        encryption_key = transform(door_pk, card_loop_size);
    }
    else
    {
        encryption_key = transform(card_pk, door_loop_size);
    }
    
    cout << "encryption key: " << encryption_key << endl;
    return 0;
}
