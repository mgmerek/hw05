/**
 *File: hw05.cc
 *Author: Mila Gmerek
 *Date: 3/16/2022
 *Brief: Card game homework
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

bool isTriangular(int n);                                             // verifies that the inputted number is triangular
void printVector(vector<int> piles);                                  // prints vector
void sortVector(vector<int> &piles);                                  // sorts in decreasing order
bool checkGame(vector<int> piles);                                    // checks if the game is finished
int largestInteger(vector<int> &piles);                               // finds largest integer
int indexOfLargest(vector<int> &piles, int startIndex, int endIndex); // returns index of largest integer

int main(int argc, char *argv[])
{
    vector<int> piles; // vector that stores the inital random piles
    vector<int> newPiles; // vector that stores the subsequent random piles
    int n; // number of cards
    int sum = 0; // makes sure the sum doesn't exceed n
    const int MAX_CARDS = 500;
    n = atoi(argv[1]);
    int randomInteger; // generates random piles
    srand(time(nullptr));
    cout << "Enter a triangular number for the game: " << endl;
    cin >> n;
    if (n > MAX_CARDS)
    {
        cout << "Error: number is too large" << endl;
        exit(0);
    }
    if (argc > 2)
    {
        n = 45;
    }
    isTriangular(n); // checks user inputted number to make sure it is triangular 
    if (isTriangular(n) == 0)
    {
        cout << "Error: Your number is not triangular" << endl;
        exit(0);
    }
    if (isTriangular(n) == 1)
    {
        while (sum != n) // generates random numbers until the number of cards is reached
        {
            randomInteger = rand() % n + 1;
            piles.push_back(randomInteger);
            n -= randomInteger;
        }

        sortVector(piles);
        checkGame(piles);
        printVector(piles);
        cout << endl;

        if (checkGame(piles) != 1)
        {
            for (unsigned int i = 0; i < piles.size(); i++) // creates new piles
            {
                piles[i] -= 1;
                newPiles.push_back(piles[i]);
                if (piles[i] == 0) // gets rid of any 0s
                {
                    newPiles.pop_back();
                }
            }
            newPiles.push_back(piles.size());
            piles = newPiles;
            sortVector(piles);
            printVector(piles);
            checkGame(piles);
        }

        if (checkGame(piles) == 1)
        {
            cout << "Game finished" << endl;
        }

        cout << "Number of rounds: " << argc << endl; // displays the number of rounds
        for (int i = 0; i < argc; i++)
        {
            cout << argv[i] << endl;
        }
    }

    return 0;
}

bool isTriangular(int n) // checks if number is triangular by checking if (n * 8) + 1 is a perfect square
{
    int x = ((n * 8) + 1);
    int sr = sqrt(x);
    bool status(0);
    if (x > 0 && sr * sr == x)
    {
        status = 1;
    }
    if (status == 1)
    {
        return true;
    }
    return false;
}

bool checkGame(vector<int> piles) // checks if numbers are ordered
{
    int currentNum;
    int consecutiveNum;
    for (unsigned int i = 0; i < piles.size() - 1; i++)
    {
        currentNum = piles[i];
        consecutiveNum = piles[i + 1];
        if (consecutiveNum != currentNum - 1)
        {
            return false;
        }
    }
    return true;
}

void printVector(vector<int> piles) // prints vector
{
    for (unsigned int i = 0; i < piles.size(); i++)
    {
        cout << piles[i] << " ";
    }
}

void sortVector(vector<int> &piles) // sorts vector in decreasing order
{
    int maxIndex;
    for (unsigned int i = 0; i < piles.size() - 1; i++)
    {
        maxIndex = indexOfLargest(piles, i, piles.size());
        swap(piles[i], piles[maxIndex]);
    }
}

int LargestInteger(vector<int> &piles) // finds largest integer 
{
    int max = piles[0];
    for (unsigned int i = 0; i < piles.size(); i++)
    {
        if (piles[i] > max)
        {
            max = piles[i];
        }
    }
    return max;
}

int indexOfLargest(vector<int> &piles, int startIndex, int endIndex) // returns the index of the largest integer in the array
{
    int max = piles[startIndex];
    int maxIndex = startIndex;
    for (int i = startIndex; i < endIndex; i++)
    {
        if (piles[i] > max)
        {
            max = piles[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}