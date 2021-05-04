#include <iostream> // allows for use of cin / cout statements

#include "Player.h" // including header for Player class

Player::Player()
{
	playerName = "Joe";
	playerAccuracy = 70;
	score = 501;
}

Player::Player(std::string name, short int accuracy) // constructor used to set variables to values from temp values in main
{
	this->playerName = name;			// set playerName to the value from the parameter passed in
	this->playerAccuracy = accuracy;	// set playerAccuracy to the value from the parameter passed in
	score = 501;						// set score to 501, as this is a game of 501
}

Player::~Player() // deconstructor intentionally empty
{
}

// GETTER for score variable
short int Player::GETscore() { return score; /* return value of score variable */ }

// MINUS, RESET and SETTER functions for score variable
void Player::MINUSscore(short int newScore)
{
	score -= newScore; // set score to the current score minus value of the parameter passed in
}
void Player::RESETscore()
{
	score = 501; // set current score to the value of the parameter passed in
}
void Player::SETscore(short int newScore)
{
	score = newScore; /* set score variable to value of parameter passed in*/
}

// GETTER and INC function for playerMatchWins variable
int Player::GETplayerMatchWins() { return playerMatchWins; /* return value of playerMatchWins variable */ }
void Player::INCplayerMatchWins()
{
	playerMatchWins++; // increment value of playerMatchWins variable
}

// GETTER and SETTER for playerSetWins variable
int Player::GETplayerSetWins() { return playerSetWins; /* return value of playerSetWins variable */ }
void Player::SETplayerSetWins(short int newSetWins)
{
	playerSetWins = newSetWins; // set value of playerSetWins to the value of the parameter passed in
}

// GET, RESET and INC functions for currentSetWins variable
short int Player::GETcurrentSetWins() { return currentSetWins; /* return value of currentSetWins variable */ }
void Player::RESETcurrentSetWins()
{
	currentSetWins = 0; // reset value of currentSetWins variable
}
void Player::INCcurrentSetWins()
{
	currentSetWins++; // increment value of currentSetWins variable
	playerSetWins++; // increment value of playerSetWins variable
}

// GETTER and SETTER functions for playerGameWins variable
int Player::GETplayerGameWins() { return playerGameWins; /* return value of playerGameWins variable */ }
void Player::SETplayerGameWins(short int newGameWins)
{
	playerGameWins = newGameWins; // set value of playerGameWins to value of parameter passed in
}

// GETTER, RESET and INC functions of currentGameWins variable
short int Player::GETcurrentGameWins() { return currentGameWins; /* return value of currentGameWins variable */ }
void Player::RESETcurrentGameWins()
{
	currentGameWins = 0; // reset value of currrentGameWins variable
}
void Player::INCcurrentGameWins()
{
	currentGameWins++; // increment currentGameWins variable
	playerGameWins++; // increment playerGameWins variable
}

// GETTER for playerAccuracy variable
short int Player::GETplayerAccuracy() { return playerAccuracy; /* return value of playerAccuracy variable */ }

// GETTER for playerName variable
std::string Player::GETplayerName() { return playerName; /* return value of playerName variable */ }

// GETTER for currentTurn variable
short int Player::GETcurrentTurn() { return currentTurn; /* return value of currentTurn variable */ }

// GETTER and RESET function for gameTurns variable
short int Player::GETgameTurns() { return gameTurns; /* return value of gameTurns variable */ }
void Player::RESETgameTurns()
{
	gameTurns = 0; // reset value of gameTurns variable
}

// SETTER and INC functions for currentTurn variable
void Player::SETcurrentTurn(short int newTurn)
{
	currentTurn = newTurn; // set value of currentTurn variable to value of parameter passed in
}
void Player::INCcurrentTurn()
{
	currentTurn++; // increment value of currentTurn variable
	gameTurns++; // increment value of gameTurns variable
}