#pragma once // tells compiler to only load file once

#include <iostream>			// allows for usage of cout / cin statements to be used
#include <string>			// allows for string to be used as a datatype
#include "Player.h"			// includes the Player class header
#include "Menu.h"			// inclueds the Menu class header

class Game
{
private:
	// 2D array holding the values of the dart board
	short int board_values[2][21] = {
									  {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
									  {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1}
	};
	// array holding what type of throw to throw on turn one when score is certain values
	const char* stratThrowType[52] = 
		// this array only deals with turn one, turn 2 is a rare occurence and turn 3 will always be a double
		/* which section to aim at */     {"T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","T","S","T","T","T","T","S","S","S","S","S","S","S","S","S","S","S","S"};
	// 3D array that deals with holding target to throw for depending on turn and score to throw for said target at
	short int stratScoring[3][52] = {
		/* score to start strat at */	  {100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49},
		/* where to aim for turn one */   {20,19,20,19,20,19,18,19,20,17,20,19,20,17,18,15,20,17,20,15,16,19,18,15,20,17,14,19,20,13,18,11,20,17,14,25,16,17,10,15,20,19,18,17,16,15,14,13,20,19,18,17},
		/* where to aim for turn three */ {20,16,19,20,18,19,20,18,16,20,15,16,14,18,16,20,12,16,11,18,16,11,12,16,8,12,16,8,6,16,8,18,4,8,12,20,8,6,16,8,20,20,20,20,20,20,20,20,16,16,16,16}
	};
	// array that holds both the range of score outcomes and the number of times these occur
	int ratio[2][14] = {
							{0,1,2,3,4,5,6,0,1,2,3,4,5,6},
							/* {7:0,7:1...0:7,1:7...}  */
							{NULL}
	};
	// array that holds the frequency that each outcome appears
	float ratioPercent[14] = {NULL};

public:
	Player* players[2];												// create a pointer array of type Player, holding 2 items
	Menu resultsText;												// create an instance of Menu class called resultsText

	Game(Player*, Player*);											// constructor for Game class, taking 2 Player pointer references as parameters
	~Game();														// deconstructor for Game class, taking no parameters

	char darts_strategy(short int, short int, short int, int);		// function that deals with the strategy of darts 501, taking 3 short ints and one int datatype as parameters

	void gamePlay();												// function that deals with the entire gameplay loop of darts 501

	void darts501Round();											// function that plays exactly one round of darts 501

	void outcomeStorage(int, int);									// function that stores the outcomes of each match of 501, taking 2 int datatypes as parameters

	void matchResults(int);											// function that prints out the results of the match, taking an int datatype as a parameters

	// functions relating to different types of throws
	short int throw_bull(short int);								// handles throwing for a bullseye
	short int throw_single(short int);								// handles throwing for a single
	short int throw_double(short int);								// handles throwing for a double
	short int throw_treble(short int, short int);					// handles throwing for a treble
};
