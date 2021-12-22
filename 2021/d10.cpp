#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

bool hasClosing(string str)
{
    if (str.find(")")!=string::npos || str.find("]")!=string::npos || str.find("}")!=string::npos || str.find(">")!=string::npos)
    {
        return 1;
    }
    return 0;
}

void eraseAllSubStr(string & mainStr, string toErase)
{
    size_t pos = string::npos;
    // Search for the substring in string in a loop untill nothing is found
    while ((pos  = mainStr.find(toErase) )!= string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
    return;
}

bool matchEnd(string o, string c)
{
    if(o.compare("(")==0 && c.compare(")")==0)
    {
        return 1;
    }
    
    if(o.compare("[")==0 && c.compare("]")==0)
    {
        return 1;
    }
    
    if(o.compare("{")==0 && c.compare("}")==0)
    {
        return 1;
    }
    
    if(o.compare("<")==0 && c.compare(">")==0)
    {
        return 1;
    }
    
    return 0;
}

char findClosing(char open)
{
    if(open=='(')
    {
        return ')';
    }
    else if(open=='[')
    {
        return ']';
    }
    else if(open=='{')
    {
        return '}';
    }
    else
    {
        return '>';
    }
}

long firstCloseCharPos(string str)
{
    long pos = 10000;
    
    if (str.find(")")!=string::npos)
    {
        if(str.find(")") < pos)
        {
            pos = str.find(")");
        }
    }
    if (str.find("]")!=string::npos)
    {
        if(str.find("]") < pos)
        {
            pos = str.find("]");
        }
    }
    if (str.find("}")!=string::npos)
    {
        if(str.find("}") < pos)
        {
            pos = str.find("}");
        }
    }
    if (str.find(">")!=string::npos)
    {
        if(str.find(">") < pos)
        {
            pos = str.find(">");
        }
    }
    
    return pos;
}

int main()
{
    ifstream file("input.txt");
    
    string line;
    
    vector<string> lines;
    
    while(getline(file,line))
    {
        lines.push_back(line);
    }
    
    long errorScore = 0;
    vector<long> completedScore;
    
    for(int i=0; i<lines.size(); i++)
    {
        bool corruptedLine = 0;
        cout << "line " << i <<":" << line << endl;
        string line = lines[i];
        do
        {
            eraseAllSubStr(line, "()");
            eraseAllSubStr(line, "[]");
            eraseAllSubStr(line, "{}");
            eraseAllSubStr(line, "<>");
        
            long pos = firstCloseCharPos(line);
            if(pos != 10000 && !matchEnd(line.substr(pos-1,1), line.substr(pos,1)))
            {
                cout << "corrupted line.\n";
                corruptedLine = 1;
                char illegalChar = line.substr(pos,1)[0];
                if(illegalChar==')')
                {
                    errorScore = errorScore + 3;
                }
                else if (illegalChar==']')
                {
                    errorScore = errorScore + 57;
                }
                else if (illegalChar=='}')
                {
                    errorScore = errorScore + 1197;
                }
                else
                {
                    errorScore = errorScore + 25137;
                }
                
                break;
            }
        } while (hasClosing(line));
        if(!corruptedLine)
        {
            cout << "line " << line << endl;
            long score = 0;
            for(long c=line.length()-1;c>-1;c--)
            {
                //cout << findClosing(line[c]);
                score = score * 5;
                
                if(line[c]=='(')
                {
                    score = score + 1;
                }
                else if (line[c]=='[')
                {
                    score = score + 2;
                }
                else if (line[c]=='<')
                {
                    score = score + 4;
                }
                else
                {
                    score = score + 3;
                }
            }
            cout << "score " << score << endl;
            completedScore.push_back(score);
        }
    }
    
    sort(completedScore.begin(), completedScore.end());
    
    long middleIdx = ((completedScore.size() +1) / 2) - 1 ;
    cout << "\nTotal syntax error: " << errorScore << endl;
    cout << "Middle completion score: " << completedScore[middleIdx] << endl;
    
    return 0;
}
