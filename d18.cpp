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
#include <cmath>
#include <math.h>

using namespace std;

string program_test[]=
{
    "1 + 2 * 3 + 4 * 5 + 6",
    "1 + (2 * 3) + (4 * (5 + 6))",
    "2 * 3 + (4 * 5)",
    "5 + (8 * 3 + 9 + 3 * 4 * 3)",
    "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))",
    "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"
};

string program[]=
{
    "5 + 9 + 5 + 9 * 9"
};

bool bracketsExist(string expression)
{
    if(expression.find('(') != string::npos)
        return 1;
    else
        return 0;
}

int findNthOccur(string str, char ch, int N)
{
    int occur = 0;
  
    // Loop to find the Nth
    // occurence of the character
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ch)
        {
            occur += 1;
        }
        if (occur == N)
            return i;
    }
    return -1;
}

unsigned long long calculate(unsigned long long firstVal, unsigned long long secondVal, string operation)
{
    if (operation=="+")
        return firstVal + secondVal;
    else
        return firstVal * secondVal;
}

string modifyString(unsigned long charStart, unsigned long len, string newString, string expression)
{
    return expression.erase(charStart, len).insert(charStart, newString);
}

string evaluateExpression(string expression) // part 1
{
    // evaluates an expression within the same pair of brackets
    string simplifiedExpression;
    string operation = expression.substr(expression.find(' ')+1, 1);
    
    unsigned long nTerms = count(expression.begin(), expression.end(), '+')+count(expression.begin(), expression.end(), '*')+1;
    
    for(int i=1; i<nTerms; i++)
    {
        string operation = expression.substr(expression.find(' ')+1, 1);

        unsigned long long firstVal = stoll(expression.substr(0, expression.find(' ')));
        unsigned long long secondVal;
        if (nTerms==2)
        {
            secondVal = stoll(expression.substr(findNthOccur(expression, ' ', 2), expression.length()-findNthOccur(expression, ' ', 2)));
        }
        else
        {
            secondVal = stoll(expression.substr(findNthOccur(expression, ' ', 2), findNthOccur(expression, ' ', 3)-findNthOccur(expression, ' ', 2)));
        }
        
        simplifiedExpression = to_string(calculate(firstVal, secondVal, operation));
        
        if (nTerms>2)
        {
            expression = modifyString(0, findNthOccur(expression, ' ', 3), simplifiedExpression, expression);
        }
    }
    
    return simplifiedExpression;
}

string evaluateExpressionAddFirst(string expression) // part 2
{
    // evaluates an expression within the same pair of brackets
    string simplifiedExpression;
    
    unsigned long nTerms = count(expression.begin(), expression.end(), '+')+count(expression.begin(), expression.end(), '*')+1;
    unsigned long nExpressionsAddition = count(expression.begin(), expression.end(), '+');
    
    for(int j=0; j<nExpressionsAddition; j++)
    {
        unsigned long plusPos = expression.find(" + ");
        unsigned long firstSpaceBeforeFirstVal = 0;
        string expressionBeforePlus = expression.substr(0,plusPos);
        
        for(unsigned long k=expressionBeforePlus.length()-1; k>0;k--)
        {
            if(expressionBeforePlus[k]==' ')
            {
                firstSpaceBeforeFirstVal = k+1;
                break;
            }
        }
        
        unsigned long firstSpaceAfterSecondVal;
        if(expression.substr(plusPos+3, expression.length()-plusPos-3).find(' ')!=expression.npos)
        {
            firstSpaceAfterSecondVal =expression.substr(plusPos+3, expression.length()-plusPos-3).find(' ');
        }
        else
        {
            firstSpaceAfterSecondVal = expression.length()-firstSpaceBeforeFirstVal;
        }
        
        unsigned long long firstVal = stoll(expression.substr(firstSpaceBeforeFirstVal, plusPos));
        unsigned long long secondVal = stoll(expression.substr(plusPos+3,firstSpaceAfterSecondVal));
        simplifiedExpression = to_string(firstVal+secondVal);
        if (nTerms>2)
        {
            expression = modifyString(firstSpaceBeforeFirstVal, firstSpaceAfterSecondVal+plusPos+3-firstSpaceBeforeFirstVal, simplifiedExpression, expression);
        }
    }
    
    if(nTerms>nExpressionsAddition+1)
    {
        simplifiedExpression = evaluateExpression(expression);
    }
        
    return simplifiedExpression;
}

string clearBrackets(string expression, string (*function)(string))
{
    while(bracketsExist(expression))
    {
        unsigned long bracket_start = expression.find_last_of("(");
        unsigned long bracket_end = expression.substr(bracket_start, expression.length()-bracket_start).find(")")+1;
        string expToEval = expression.substr(bracket_start, bracket_end); // contains brackets
        // the substring cuts off the opening and closing brackets (first and last characters)
        function(expToEval.substr(1,expToEval.length()-2));
        expression = modifyString(bracket_start, bracket_end, function(expToEval.substr(1,expToEval.length()-2)), expression);
    }
    return expression;
}

void PartOne()
{
    int nRows =  sizeof(program)/sizeof(program[0]);
    unsigned long long totalSum = 0;
   
    for (int i =0; i<nRows;i++)
    {
        string expression = program[i];
        expression = clearBrackets(expression, &evaluateExpression);
        expression = evaluateExpression(expression);
        totalSum = totalSum + stoll(expression);
    }
    
    cout << "total sum is: " << totalSum << endl;
    return;
}

void PartTwo()
{
    int nRows =  sizeof(program)/sizeof(program[0]);
    unsigned long long totalSum = 0;
   
   for (int i =0; i<nRows;i++)
    {
        string expression = program[i];
        expression = clearBrackets(expression, &evaluateExpressionAddFirst);
        expression = evaluateExpressionAddFirst(expression);
        totalSum = totalSum + stoll(expression);
    }
    
    cout << "total sum is: " << totalSum << endl;
    return;
}

int main()
{
    PartOne();
    PartTwo();
    return 0;
}
