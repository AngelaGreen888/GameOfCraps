/* 
Angela (Nikki) Green
October 24, 2016
Craps Game
*/

// Roll Bones.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

unsigned askForInititalStakeAmountFunc();
unsigned askForBetDonePlayingFunc(unsigned stakeUns);
unsigned rollDemBonesFunc(unsigned &rollCountUns);
void     evaluateRollFunc(unsigned diceRollResultsUns, unsigned &rollCountUns, unsigned &stakeUns, unsigned betUns);
bool     pointRollDemBonesFunc(unsigned pointUns, unsigned &rollCountUns);

int main() {
	unsigned
		betUns,
		rollCountUns = 0,
		diceRollResultsUns,
		stakeUns = askForInititalStakeAmountFunc();

	do {
		betUns = askForBetDonePlayingFunc(stakeUns);
		if (betUns != 0) {
			diceRollResultsUns = rollDemBonesFunc(rollCountUns);
			evaluateRollFunc(diceRollResultsUns, rollCountUns, stakeUns, betUns);
		}
	} while ((betUns != 0) && (stakeUns != 0));

	cout << endl << endl;

	if (betUns == 0) {
	cout << "Player ends Game" << endl;
	system("pause");
}
	else 
		cout << "Out of money, Game ends" << endl;

	cout << "Roll Count :         " << rollCountUns << endl;
	cout << "Final Stake Amount : " << stakeUns << endl << endl << endl;

	getchar(); //freeze screen
	return 0;
}

/*
Name:              askForInitialStakeAmountFunc
Function Purpose : Retrieves the initial money from prompting the user
Function Design:   Checks if the input stake amount the player eneters a proper amount.
Inputs:            None
Outputs:           By function name an unsigned integer that's the stake amount
*/

unsigned askForInititalStakeAmountFunc() {
	long int stakeStartUns;

	do {
		cout << "What is your total stake amount? ";
		cin >> stakeStartUns;
		cout << endl << endl;

		if (stakeStartUns > 0)
			break;

		else {
			cout << "You have to enter a positive amount of money to bet with. Try again.";
			continue;
		}
	} while (true);

	return stakeStartUns;
}

/*
Name: askForBetDonePlayingFunc
Function Purpose : Asks for what the player will bet and checks for validity
Function Design:   Checks for valid entry has been entered
Inputs:            stakeUns - The total stake amount
Outputs:           By function name an unsigned integer that's the bet amount
*/

unsigned askForBetDonePlayingFunc(unsigned stakeUns) {
	int inputUns;
	unsigned betUns;

	do {
		cout << endl << "Current Stake Amount: " << stakeUns << endl << endl;
		cout << "What will you bet? ";
		cin >> inputUns;
		cout << endl << endl;
			
		// Bet is larger than the stake
			if (inputUns > (long int)stakeUns) {
				cout << "Sorry, you can't bet more than your stake!" << endl << endl;
				continue;
			}
		// Bet is negative
			else if (inputUns < 0) {
				cout << "You have to bet a positive number less than or equal to the stake amount!" << endl << endl;
				continue;
			}
		// Bet is valid
			else {
				betUns = (unsigned)inputUns;
				break;
			}
	} while (true);
	return betUns;
}


/*
Name:             rollDemBonesFunc
Function Purpose: generates a random number for a roll and increment rollCountUns
Function Design:  Prompts the user to throw the dice
Using rand() generates 2 random variables from 1 to 6 and adds to simulate dice throw
Inputs/Outpuut:   &rollCountUns - Reference of total rolls count in game
Outputs:          By function name an unsigned integer that's the sum of the two rolled dice
*/

unsigned rollDemBonesFunc(unsigned &rollCountUns) {
	unsigned die01value, 
			die02value, 
			diceSumUns;
	cout << "Time to roll the dice!" << endl;
	system("pause");
	cout << endl << endl;

	//Uses the random number generator for the dice rolls
	rollCountUns++;
	srand(clock()); 

	die01value = (rand() % 6 + 1);
	die02value = (rand() % 6 + 1);
	diceSumUns = die01value + die02value;
	cout << "The first dice value is:  " << die01value << endl;
	cout << "The second dice value is: " << die02value << endl;
	cout << "The dice roll result is:  " << diceSumUns << " !" << endl << endl << endl;
	
	return diceSumUns;
}

/*
Name: evaluateRollFunc
Function Purpose: Check for a winning roll, a losing roll, or a point roll result
Function Design:  2, 3, 12      loses
				7, 11         winner
anything else executes point rolls
Inputs:           diceRollResultsUns - The dice roll sum
Input/Output:     &rollCountUns      - Reference to tally of total rolls
&stakeUns          - Reference to the total at stake
Inputs:           betUns             - The placed bet
*/

void evaluateRollFunc(unsigned diceRollResultsUns, unsigned &rollCountUns, unsigned &stakeUns, unsigned betUns) {
	switch (diceRollResultsUns) {
		case 2:
		case 3:
		case 12:
			cout << "Sorry, you lose." << endl << endl;
			stakeUns -= betUns;
			break;

		case 7:
		case 11:
			cout << "You're a winner!" << endl << endl;
			stakeUns += (2 * betUns);
			break;

		default: 
			if (pointRollDemBonesFunc(diceRollResultsUns, rollCountUns)) {
				cout << "You're a winner!" << endl << endl;
				stakeUns += (2 * betUns);
			}
			else {
				cout << "Sorry, you lose!" << endl << endl;
				stakeUns -= betUns;
			}
	}

}

/*
Name:             pointRollDemBonesFunc
Function Purpose: Executes the point rolls
Function Design:  Displays the point value.
Uses rollDemBonesFunc until the point or 7 is the result
Complex Elements: rollCountUns is passed from this function to rollDemBonesFunc()
Inputs:           pointUns      - The point set by the first roll
&rollCountUns - Reference to total roll count
Outputs:          Returns true if wins or false if loses
*/

bool pointRollDemBonesFunc(unsigned pointUns, unsigned &rollCountUns) {
	unsigned pointRollUns;

	//Executes until point value or 7 is rolled
	do {
		cout << endl << "The point is " << pointUns << endl << "Throw the dice again, and good luck!" << endl << endl;
		pointRollUns = rollDemBonesFunc(rollCountUns);
	} while ((pointRollUns != 7) & (pointRollUns != pointUns));

	if (pointRollUns != 7)
		return(true);
	else
		return(false);

}

