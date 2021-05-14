#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <cmath>
#include <math.h>
#include<numeric>

using namespace std;

void PrintVec(vector<unsigned int> deck)
{
    for (vector<unsigned int>::iterator it=deck.begin(); it!=deck.end(); ++it)
       cout << *it << ' ' ;
     cout << '\n';
}

string DeckConfig(vector<unsigned int> one, vector<unsigned int> two)
{
    string deckConfig=""; // saved in format "deckOne|deckTwo"
    for (vector<unsigned int>::iterator it=one.begin(); it!=one.end(); ++it)
        deckConfig.append(to_string(*it)+" ");
    deckConfig.append("|");
    for (vector<unsigned int>::iterator it=two.begin(); it!=two.end(); ++it)
        deckConfig.append(to_string(*it)+" ");
    return deckConfig;
}

void PrintDecks(vector<unsigned int> one, vector<unsigned int> two)
{
    cout << "Player 1's deck: ";
    PrintVec(one);
    cout << "Player 2's deck: ";
    PrintVec(two);
    return;
}

void PlayRound(vector<unsigned int> &one, vector<unsigned int> &two)
{
    PrintDecks(one,two);
    unsigned int playerOneCard = one[0];
    unsigned int playerTwoCard = two[0];
    
    cout << "Player 1 plays: " << playerOneCard << endl;
    cout << "Player 2 plays: " << playerTwoCard << endl;
    
    unsigned int winner;
    if (playerOneCard>playerTwoCard)
    {
        winner = 1;
        one.push_back(playerOneCard);
        one.push_back(playerTwoCard);
    }
    else
    {
        winner = 2;
        two.push_back(playerTwoCard);
        two.push_back(playerOneCard);
    }
    
    one.erase(one.begin());
    two.erase(two.begin());
    
    cout << "Player " << winner << " wins the round!\n\n";
    
    return;
}

void PlayRoundRecursive(vector<unsigned int> &one, vector<unsigned int> &two, unsigned int &gameNumber, unsigned int roundNumber, unsigned int &subGameNumber, set<string> &deckConfigs)
{
    cout << "\n-- Round " << roundNumber << " (Game " << gameNumber << ") --" << endl;
    //PrintDecks(one,two);
    
    string currConfig = DeckConfig(one, two);
    
    if (deckConfigs.find(currConfig) != deckConfigs.end())
    {
        two.clear();
        return;
    }
   
    deckConfigs.insert(currConfig);
        
    unsigned int playerOneCard = one[0];
    unsigned int playerTwoCard = two[0];
    one.erase(one.begin());
    two.erase(two.begin());
        
    //cout << "Player 1 plays: " << playerOneCard << endl;
    //cout << "Player 2 plays: " << playerTwoCard << endl;
    
    unsigned int winner=0;
    bool subGamePlayed = 0;
        
    if(playerOneCard<=one.size()&&playerTwoCard<=two.size())
    {
        cout << "Playing a sub-game to determine the winner...\n\n";
        subGamePlayed = 1;
        subGameNumber++;
        unsigned int subSubGameNumber = subGameNumber;
        vector<unsigned int> oneCopy (one.begin(),one.begin()+playerOneCard);
        vector<unsigned int> twoCopy (two.begin(),two.begin()+playerTwoCard);
        
        cout << "=== Game " << subGameNumber << " ===\n";
        set<string> deckConfigsCopy;
        unsigned int subGameRoundNumber = 1;
        do
        {
            PlayRoundRecursive(oneCopy, twoCopy, subGameNumber, subGameRoundNumber, subSubGameNumber, deckConfigsCopy);
            subGameRoundNumber = subGameRoundNumber + 1;
        } while (!oneCopy.empty()&&!twoCopy.empty());
        
        if(oneCopy.empty())
        {
            winner = 2;
        }
        else
        {
            winner = 1;
        }
        cout << "The winner of game " << subGameNumber << " is player " << winner << "!\n\n";
        cout << "..anyway, back to game " << gameNumber << ".\n";
    }
        
    if ((subGamePlayed==0 && playerOneCard>playerTwoCard) || (subGamePlayed==1 && winner==1))
    {
        winner = 1;
        one.push_back(playerOneCard);
        one.push_back(playerTwoCard);
    }
    else
    {
        winner = 2;
        two.push_back(playerTwoCard);
        two.push_back(playerOneCard);
    }
        
    cout << "Player " << winner << " wins round " << roundNumber << " of game " << gameNumber << "!\n";
    
    return;
}

unsigned long CalculateScore(vector<unsigned int> one, vector<unsigned int> two)
{
    unsigned long score = 0;
    
    vector<unsigned int> winnerDeck;
    
    if(one.empty())
    {
        winnerDeck = two;
    }
    else
    {
        winnerDeck = one;
    }
    
    reverse(winnerDeck.begin(),winnerDeck.end());
    
    for(int i=0;i<winnerDeck.size();i++)
    {
        score = score + winnerDeck[i]*(i+1);
    }
    return score;
}

int main()
{
    ifstream file("input.txt");
    string line;
    
    vector<unsigned int> playerOneDeck;
    vector<unsigned int> playerTwoDeck;
    bool readingPlayerTwo = 0;
  
    while(getline(file,line))
    {
        if(line.find("Player")!=string::npos)
        {
            continue;
        }
        
        if (line=="")
        {
            readingPlayerTwo = 1;
            continue;
        }
        
        if(readingPlayerTwo)
        {
            playerTwoDeck.push_back(stoi(line));
        }
        else
        {
            playerOneDeck.push_back(stoi(line));
        }
    }
    
    /* // part 1
    
    unsigned int roundNumber = 1;
    do
    {
        cout << "-- Round " << roundNumber << " --" << endl;
        PlayRound(playerOneDeck, playerTwoDeck);
        roundNumber = roundNumber + 1;
    } while (!playerOneDeck.empty()&&!playerTwoDeck.empty());
    
    cout << "== Post-game results ==" << endl;
    PrintDecks(playerOneDeck,playerTwoDeck);
    cout << "Final score: " << CalculateScore(playerOneDeck,playerTwoDeck) << endl;*/
    
    // part 2
    unsigned int gameNumber = 1;
    unsigned int subGameNumber = 1;
    
    cout << "=== Game " << gameNumber << " ===\n";
    set<string> deckConfigs;
    unsigned int roundNumber = 1;
    do
    {
        PlayRoundRecursive(playerOneDeck, playerTwoDeck, gameNumber, roundNumber, subGameNumber, deckConfigs);
        roundNumber = roundNumber + 1;
    } while (!playerOneDeck.empty()&&!playerTwoDeck.empty());
    
    cout << "\n\n== Post-game results ==" << endl;
    PrintDecks(playerOneDeck,playerTwoDeck);
    cout << "Final score: " << CalculateScore(playerOneDeck,playerTwoDeck) << endl;
    
    return 0;
}
