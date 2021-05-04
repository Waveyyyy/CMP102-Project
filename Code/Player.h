#pragma once							// tells compiler to only load this file once
class Player
{
private:
	// create / initialise private variables to be used within Player.cpp
	std::string playerName;				
	short int playerAccuracy;			
	short int score;

	int playerMatchWins = 0;

	int playerSetWins = 0;
	short int currentSetWins = 0;

	int playerGameWins = 0;
	short int currentGameWins = 0;

	short int gameTurns = 0;
	short int currentTurn = 0;

public:
	Player();								// default constructor for Player class
	Player(std::string, short int);			// Constructor for Player class with string and short int datatypes as parameters
	~Player();								// Deconstructor for Player class

	short int GETscore();					// GETTER for score variable
	void MINUSscore(short int);				// function to take score away from a player, with short int datatype as a parameter
	void RESETscore();						// RESET function for score variable, sets score to 501
	void SETscore(short int);				// SETTER for score variable

	int GETplayerMatchWins();				// GETTER for playerMatchWins variable
	void INCplayerMatchWins();				// function to increment playerMatchWins variable

	int GETplayerSetWins();					// GETTER for playerSetWins variable
	void SETplayerSetWins(short int);		// SETTER for playerSetWins variable, with short int datatype as a parameter

	short int GETcurrentSetWins();			// GETTER for currentSetWins variable
	void RESETcurrentSetWins();				// RESET function for currentSetWins variable, sets currentSetWins to 0
	void INCcurrentSetWins();				// function to increment currentSetWins variable

	int GETplayerGameWins();				// GETTER for playerGameWins variable
	void SETplayerGameWins(short int);		// SETTER for playerGameWins variable, with short int datatype as a parameter

	short int GETcurrentGameWins();			// GETTER for currentGameWins variable
	void RESETcurrentGameWins();			// RESET function for currentGameWins variable, sets currentGameWins to 0
	void INCcurrentGameWins();				// function to increment currentGameWins variable

	short int GETplayerAccuracy();			// GETTER for playerAccuracy variable

	std::string GETplayerName();			// GETTER for playerName variable

	short int GETgameTurns();				// GETTER for gameTurns variable
	void RESETgameTurns();					// RESET function for gameTurns variable, sets gameTurns to 0

	short int GETcurrentTurn();				// GETTER for currentTurn variable
	void SETcurrentTurn(short int);			// SETTER for currentTurn variable, with short int datatype as a parameter
	void INCcurrentTurn();					// function to increment currentTurns variable
};
