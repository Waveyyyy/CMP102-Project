#include <iomanip>			// allows for use of setprecision and fixed to be used in cout statements

#include "Game.h"			// including header for Game class

Game::Game(Player* player_one, Player* player_two) // constructor taking 2 player pointers as parameters
{
	players[0] = player_one;		// assign the Player class pointer passed in the left side of the parameters to be player one
	players[1] = player_two;		// assign the Player class pointer passed in the right side of the parameters to be player two
}

Game::~Game() // deconstructor intentionally empty
{
}

// function to handle the strategy of throwing darts, where to aim based on score etc
char Game::darts_strategy(short int currentScore, short int currentTurn, short int accuracy, int index)
{
	// initialise random variable to a value between 1 and 20
	short int random = rand() % 21 + 1;

	// if players score is more than 501, code in conditional will run
	if (players[index]->GETscore() > 501)
	{
		players[index]->RESETscore();		// set score of current player back to 501
		players[index]->SETcurrentTurn(0);	// set currentTurn back to 0
	}

	// if the players current score is less than OR equal to 501 AND is greater than 100
	// code in the following conditional will run
	if (currentScore <= 501 && currentScore > 100)
	{
		// use the throw_treble function using current players accuracy and 20(target) as parameters
		players[index]->MINUSscore(throw_treble(20, accuracy));
		// return 2 for switch statement in gamePlay function that calls this current function
		// returning 2 tells gamePlay that a treble is being thrown
		return '2';
	}
	// if the players current score is less than OR equal to 100 AND is greater than OR equal to 49
	// code in the following conditional will run
	else if (currentScore <= 100 && currentScore >= 49)
	{
		short int i = 0;		// initialise i to zero, this will be our loop counter variable

		do	// using a do while loop to always run the following code once before looping / exiting
		{
			// if players current score is == to the value in position i ( between 100 and 49 )
			// and currentScore is NOT equal to 99
			// then the code in the conditional will run
			if (currentScore == stratScoring[0][i] && currentScore != 99)
			{
				// if current turn is zero AND the throw type in position i of array 0 is a treble, run the code in the conditional
				if (currentTurn == 0 && stratThrowType[i] == "T")
				{
					// using throw_treble function with target in position i of array 1 and accuracy as parameters
					players[index]->MINUSscore(throw_treble(stratScoring[1][i], accuracy));
					// return 2 for switch statement in gamePlay function that calls this one
					// returning 2 tells gamePlay that a treble is being thrown
					return '2';
				}
				// if current turn is zero AND thow type in position i of array 0 is a single run the code inside the conditional
				else if (currentTurn == 0 && stratThrowType[i] == "S")
				{
					// using throw_single function with target in position i of array 1 as a parameter
					players[index]->MINUSscore(throw_single(stratScoring[1][i]));
					// return 0 for switch statement in gamePlay function that calls this current function
					// returning 0 tells gamePlay that a single is being thrown
					return '0';
				}
				// current turn is one AND current score is 99, code within the conditional is ran
				if (currentTurn == 1 && currentScore == 99)
				{
					// using throw_single function with 10 as a parameter
					players[index]->MINUSscore(throw_single(10));
					// return 0 for switch statement in gamePlay function that calls this current function
					// returning 0 tells gamePlay that a single is being thrown
					return '0';
				}
				// if current turn is two AND current score is == to the value in position i ( between 100 and 49 ) of array zero
				// code within the conditional will run
				else if (currentTurn == 2 && currentScore == stratScoring[0][i])
				{
					// using throw_double function with target in position i of array 2 as a parameter
					players[index]->MINUSscore(throw_double(stratScoring[2][i]));
					// return 1 for switch statement in gamePlay function that calls this current function
					// returning 1 tells gamePlay that a double is being thrown
					return '1';
				}
				else
				{
					// using throw_double function with target in position i of array 2 as a parameter
					players[index]->MINUSscore(throw_double(random));
					// return 1 for switch statement in gamePlay function that calls this current function
					// returning 1 tells gamePlay that a double is being thrown
					return '1';
				}
			}
			else
			{
				// using throw_double function with random as a parameter
				players[index]->MINUSscore(throw_double(random));
				// return 1 for switch statement in gamePlay function that calls this current function
				// returning 1 tells gamePlay that a double is being thrown
				return '1';
			}
			// increment counter variable, which is used to change array position
			i++;
		} while (currentScore != stratScoring[0][i]);	// while current score is not equal to value in i position of array 0, continue looping
	}
	// if current score is greater than 49 AND less than 40, code in the following conditional will run
	else if (currentScore < 49 && currentScore > 40)
	{
		// aim for a random double
		players[index]->MINUSscore(throw_double(random));
		// return 1 for switch statement in gamePlay function that calls this current function
		// returning 1 tells gamePlay that a double is being thrown
		return '1';
	}
	// if current score is less than OR equal to 40 AND current score is an even number, code in the following conditional will run
	else if (currentScore <= 40 && currentScore % 2 == 0)
	{
		// aim for a double of half the current score
		players[index]->MINUSscore(throw_double(currentScore/2));
		// return 1 for switch statement in gamePlay function that calls this current function
		// returning 1 tells gamePlay that a double is being thrown
		return '1';
	}
	// if current score is less than 40 AND is an odd number, code in the following conditional will run
	else if (currentScore < 40 && currentScore % 2 != 0)
	{
		// aim for a random single to get score back to being even, allowing for a double throw
		players[index]->MINUSscore(throw_single(random));
		// return 0 for switch statement in gamePlay function that calls the current function
		// returning 0 tells gamePlay that a double is being thrown
		return '0';
	}
	else
	{
		// using throw_double function with random(target) as a parameter
		players[index]->MINUSscore(throw_double(random));
		// return 1 for switch statement in gamePlay function that calls this current function
		// returning 1 tells gamePlay that a double is being thrown
		return '1';
	}
}

// function to deal with the gamePlay loop
void Game::gamePlay()
{
	// loop for the (maximum) 13 sets per one match
	for (int i = 0; i < 13; i++)
	{
		// checking which player has the 7 set wins required to win a match
		if (players[0]->GETcurrentSetWins() != 7 && players[1]->GETcurrentSetWins() != 7)
		{
			// loop for the (maximum) 5 games per set
			for (int j = 0; j < 5; j++)
			{
				// if either player does NOT have 3 wins, code in following conditional will run
				if (players[0]->GETcurrentGameWins() != 3 && players[1]->GETcurrentGameWins() != 3)
				{
					
					do  // loop for ONE round of 501 darts
					{
						darts501Round();	// call the darts501Round function to play one round of 501 per loop

						// while either players score is not equal to 0, continue looping
					} while (players[0]->GETscore() != 0 && players[1]->GETscore() != 0);

					// if player ones score is equal to 0, code in following conditional will run
					if (players[0]->GETscore() == 0)
					{
						players[0]->INCcurrentGameWins();		// increment player ones game wins 

						players[0]->RESETscore();				// reset player ones score to 501
						players[1]->RESETscore();				// reset player twos score to 501
					}
					// if player twos score is equal to 0, code in the following conditional will be run
					else if (players[1]->GETscore() == 0)
					{
						players[1]->INCcurrentGameWins();		// increment player twos game wins

						players[0]->RESETscore();				// reset player ones score to 501
						players[1]->RESETscore();				// reset player twos score to 501
					}
				}
				else
				{
					// if player ones number of game wins is equal to 3, code in the following conditional will be run
					if (players[0]->GETcurrentGameWins() == 3)
					{
						players[0]->INCcurrentSetWins();		// increment player ones set wins

						players[0]->RESETcurrentGameWins();		// reset player ones current game wins to 0
						players[1]->RESETcurrentGameWins();		// reset player twos current game wins to 0

						break; // break out of current loop, which ends the current set, allowing for a new set to start
					}
					else if (players[1]->GETcurrentGameWins() == 3)
					{
						players[1]->INCcurrentSetWins();		// increment player twos set wins

						players[0]->RESETcurrentGameWins();		// reset player ones current game wins to 0
						players[1]->RESETcurrentGameWins();		// reset player twos current game wins to 0

						break; // break out of current loop, which ends the current set, allowing for a new set to start
					}
				}
			}
		}
		else
		{
			// if player ones number of set wins is equal to 7, code in following conditional will be run
			if (players[0]->GETcurrentSetWins() == 7)
			{
				players[0]->INCplayerMatchWins();													// increment player ones match wins

				outcomeStorage(players[1]->GETcurrentSetWins(), players[0]->GETcurrentSetWins());	// store frequency of results, taking current setwins for each player as parameters

				players[0]->RESETcurrentSetWins();													// reset player ones current set wins to 0
				players[1]->RESETcurrentSetWins();													// reset player twos current set wins to 0

				break; // break out of current loop, ending the current match ready for the next match
			}
			// if player twos number of set wins is equal to 7, code in following conditional will be run
			else if (players[1]->GETcurrentSetWins() == 7)
			{
				players[1]->INCplayerMatchWins();													// increment player twos match wins

				outcomeStorage(players[1]->GETcurrentSetWins(), players[0]->GETcurrentSetWins());	// store frequency of results, taking current setwins for each player as parameters

				players[0]->RESETcurrentSetWins();													// reset player ones current set wins to 0
				players[1]->RESETcurrentSetWins();													// reset player twos current set wins to 0

				break; // break out of current loop, which ends the current match, allowing for a new match to start
			}
		}
	}
	// if player ones number of set wins is equal to 7, code in following conditional will be run
	if (players[0]->GETcurrentSetWins() == 7)
	{
		players[0]->INCplayerMatchWins();													// increment player ones match wins

		outcomeStorage(players[1]->GETcurrentSetWins(), players[0]->GETcurrentSetWins());	// store frequency of results, taking current setwins for each player as parameters

		players[0]->RESETcurrentSetWins();													// reset player ones current set wins to 0
		players[1]->RESETcurrentSetWins();													// reset player twos current set wins to 0
	}
	// if player twos number of set wins is equal to 7, code in following conditional will be run
	else if (players[1]->GETcurrentSetWins() == 7)
	{
		players[1]->INCplayerMatchWins();													// increment player twos match wins

		outcomeStorage(players[1]->GETcurrentSetWins(), players[0]->GETcurrentSetWins());	// store frequency of results, taking current setwins for each player as parameters

		players[0]->RESETcurrentSetWins();													// reset player ones current set wins to 0
		players[1]->RESETcurrentSetWins();													// reset player twos current set wins to 0
	}
}

// function to handle playing one round of 501 darts
void Game::darts501Round()
{
	// initialise local variables
	short int temp_score = 0;		// variable to hold players score at the start of a round, to be used if bust or etc.
	short int new_score = 0;		// variable to hold players perspective score if their throw is not found as illegal etc.
	char throw_type = '4';			// variable to indicate the type of throw, used to check if a throw is legal or not

	// loop 2 times, once for each player in the 2 player array
	for (int i = 0; i < 2; i++)
	{
		players[i]->SETcurrentTurn(0);	// start of loop set current turn value to zero

		// loop 3 times, each loop setting j to the value of current turn variable
		for (int j = 0; j < 3; j = players[i]->GETcurrentTurn())
		{
			// if current players turn is equal to 0, code in the following conditional will run
			if (players[i]->GETcurrentTurn() == 0)
			{
				temp_score = players[i]->GETscore();	// set temp_score to the score of the current player
			}

			// set throw type to the value returned by the darts_strategy function
			throw_type = darts_strategy(players[i]->GETscore(), players[i]->GETcurrentTurn(), players[i]->GETplayerAccuracy(), i);
			new_score = players[i]->GETscore();		// set new_score to the value of the current players score

			// checking that the score to be taken off will not,
				// 1. bust the player
				// 2. allow the player to win without their last throw being a double
			if (throw_type == '1' && players[i]->GETscore() == 0)
			{
				players[i]->MINUSscore(new_score);		// set value of the current players playerScore variable to the new score as this throw was legal
				break;									// break from the current loop, (loop that loops for 3 turns)
			}
			else if (throw_type == '3' && players[i]->GETscore() == 0)
			{
				players[i]->MINUSscore(new_score);		// set value of the current players playerScore variable to the new score as this throw was legal
				break;									// break from the current loop, (loop that loops for 3 turns)
			}
			else if (players[i]->GETscore() <= 1)
			{
				players[i]->SETscore(temp_score);		// set value of current players playerScore variable back to score before current turn as this throw was illegal
				break;									// break from the current loop, (loop that loops for 3 turns)
			}

			players[i]->INCcurrentTurn();				// increment current turn variable for current player
		}
		// if current players score is equal to 0, code in following conditional will be run
		if (players[i]->GETscore() == 0)
		{
			break;										// break from current loop ( loop that loops 2 times, one for each player)
		}
	}
}

// function to handle storing amount of times each possible game outcome happens
void Game::outcomeStorage(int setWinsP2, int setWinsP1) // matches been remove thats why errorrs
{
	switch (setWinsP2)		// switch using value of setWinsP2 parameter as an expression
	{
	case 0:					// if player 2 won 0 sets ( 7 : 0 ) this case is triggered
	{
		ratio[1][0]++;		// increment value of position 0 in array 1 of ratio
		break;				// break from switch statement
	}
	case 1:					// if player 2 won 1 sets ( 7 : 1 ) this case is triggered
	{
		ratio[1][1]++;		// increment value of position 1 in array 1 of ratio
		break;				// break from switch statement
	}
	case 2:					// if player 2 won 2 sets ( 7 : 2 ) this case is triggered
	{
		ratio[1][2]++;		// increment value of position 2 in array 1 of ratio
		break;				// break from switch statement
	}
	case 3:					// if player 2 won 3 sets ( 7 : 3 ) this case is triggered
	{
		ratio[1][3]++;		// increment value of position 3 in array 1 of ratio
		break;				// break from switch statement
	}
	case 4:					// if player 2 won 4 sets ( 7 : 4 ) this case is triggered
	{
		ratio[1][4]++;		// increment value of position 4 in array 1 of ratio
		break;				// break from switch statement
	}
	case 5:					// if player 2 won 5 sets ( 7 : 5 ) this case is triggered
	{
		ratio[1][5]++;		// increment value of position 5 in array 1 of ratio
		break;				// break from switch statement
	}
	case 6:					// if player 2 won 6 sets ( 7 : 6 ) this case is triggered
	{
		ratio[1][6]++;		// increment value of position 6 in array 1 of ratio
		break;				// break from switch statement
	}
	}

	switch (setWinsP1)		// switch using value of setWinsP2 parameter as an expression
	{
	case 0:					// if player 1 won 0 sets ( 0 : 7 ) this case is triggered
	{
		ratio[1][7]++;		// increment value of position 7 in array 1 of ratio
		break;				// break from switch statement
	}
	case 1:					// if player 1 won 1 sets ( 1 : 7 ) this case is triggered
	{
		ratio[1][8]++;		// increment value of position 8 in array 1 of ratio
		break;				// break from switch statement
	}
	case 2:					// if player 1 won 2 sets ( 2 : 7 ) this case is triggered
	{
		ratio[1][9]++;		// increment value of position 9 in array 1 of ratio
		break;				// break from switch statement
	}
	case 3:					// if player 1 won 3 sets ( 3 : 7 ) this case is triggered
	{
		ratio[1][10]++;		// increment value of position 10 in array 1 of ratio
		break;				// break from switch statement
	}
	case 4:					// if player 1 won 4 sets ( 4 : 7 ) this case is triggered
	{
		ratio[1][11]++;		// increment value of position 11 in array 1 of ratio
		break;				// break from switch statement
	}
	case 5:					// if player 1 won 5 sets ( 5 : 7 ) this case is triggered
	{
		ratio[1][12]++;		// increment value of position 12 in array 1 of ratio
		break;				// break from switch statement
	}
	case 6:					// if player 1 won 6 sets ( 6 : 7 ) this case is triggered
	{
		ratio[1][13]++;		// increment value of position 13 in array 1 of ratio
		break;				// break from switch statement
	}
	}
}

void Game::matchResults(int matches)
{
	resultsText.resultsScreen();	// prints the results screen ascii text

	// output a line at the top of results, with the players names, and frequency as a headers to data that will be displayed below
	std::cout << players[0]->GETplayerName() << " : " << players[1]->GETplayerName() << "     " << "Frequency" << std::endl;

	// loop 14 times, the length of the ratio array
	for (int i = 0; i < 14; i++)
	{
		// if the value of any position of array one ( array holding how many times that a game was won with that score)
		// is not equal to zero, code in the following conditional will run
		if (ratio[1][i] != 0)
		{
			// if i, the array index is less than 7, detailing games where player 1 won, code in the following conditional will run
			if (i < 7)
			{
				ratioPercent[i] = (float(ratio[1][i]) / matches) * 100;																	// calculate the frequency that every score combination occurred
				std::cout << "7 : " << ratio[0][i] << "      ";																			// formatting for output of the ratio
				std::cout << std::setw(4) << ratioPercent[i] << std::fixed << std::setprecision(2) << "%" << std::endl << std::endl;	// more formatting for output 
			}
			// if i, the array index is greater than OR equal to 7, detailing games where player 2 won, code in the following conditional will run
			else if (i >= 7)
			{
				ratioPercent[i] = (float(ratio[1][i]) / matches) * 100;																	// calculate the frequency that every score combination occurred
				std::cout << ratio[0][i] << " : 7" << "      ";																			// formatting for output of the ratio, flipped in comparison to player 1's format
				std::cout << std::setw(4) << ratioPercent[i] << std::fixed << std::setprecision(2) << "%" << std::endl << std::endl;	// more formatting for output
			}
		}
	}
}

// function to handle throwing for a bullseye, taking the accuracy as a parameter
short int Game::throw_bull(short int accuracy)
{
	// setting variable random, to a value between 1 and 100
	short int random = rand() % 100 + 1;

	// if value of random is less than OR equal to accuracy - 20, an inner bullseye has been hit
	if (random <= (accuracy - 20)) { return 50; }

	// if random is less than OR equal to 85, an outer bullseye has been hit
	else if (random <= 85) { return 25; }

	// if random is greater than both values detailed above, neither bullseye's have been hit
	// a random score between 1 and 20 will be returned
	else { return rand() % 20 + 1; }
}

// function to handle throwing for a single, taking the target as a parameter
short int Game::throw_single(short int target)
{
	// setting variable random, to a value between 1 and 100
	short int random = rand() % 100 + 1;

	// if the target is equal to 25 AND random is less than OR equal to 80 (success rate of 80%)
	// a single(outer bullseye) has been hit
	if (target == 25) {
		if (random <= 80)
			return 25;
		// if random is less than OR equal to 90 then a inner bullseye has been hit
		else if (random <= 90)
			return 50;
		// if random is any other value, return a random value between 1 and 20
		else
			return rand() % 20 + 1;
	}
	// any other target chosen run through the following conditionals
	else
		// if random is less than OR equal to 88 the target has been hit
		if (random <= 88)
			return target;
	// must be aiming for between 1 and 20 single
	// if random is less than OR equal to 92 then target position in array is returned
		else if (random <= 92)
			return board_values[0][target];
	// if random is less than OR equal to 96 then the target position in array 2 is returned
		else if (random <= 96)
			return board_values[1][target];
	// if random is less than OR equal to 98 then treble target position in array was hit
		else if (random <= 98)
			return 3 * target;
	// if random is any other value, then double target value was hit
		else
			return 2 * target;
}

// function to deal with throwing a treble, taking target and accuracy as a parameter
short int Game::throw_treble(short int target, short int accuracy)
{
	// setting variable random, to a value between 1 and 100
	short int random = rand() % 100 + 1;

	// if random is less than OR equal to accuracy, treble target has been hit
	if (random <= accuracy)
		return 3 * target;
	// if random is less than OR equal to 90, target has been hit
	else if (random <= 90)
		return target;
	// if random is less than OR equal to 93, treble the value in target position of array will be returned
	else if (random <= 93)
		return 3 * board_values[0][target];
	// if random is less than OR equal to 96, treble the value in target position of array 2 will be returned
	else if (random <= 96)
		return 3 * board_values[1][target];
	// if random is less than OR equal to 98, treble the value in target position will be returned
	else if (random <= 98)
		return board_values[0][target];
	// if random is any other value, value of target pos in array 2 is returned
	else
		return board_values[1][target];
}

// function to deal with throwing a double, taking target as a parameter
short int Game::throw_double(short int target)
{
	// setting variable random, to a value between 1 and 100
	short int random = rand() % 100 + 1;

	// if random is less than OR equal to 80, double target has been hit
	if (random <= 80)
		return 2 * target;
	// if random is less than OR equal to 85, target was missed
	else if (random <= 85)
		return 0;
	// if random is less than OR equal to  90, target has been hit
	else if (random <= 90)
		return target;
	// if random is less than OR equal to 93, value of double of targets position in array will be returned
	else if (random <= 93)
		return 2 * board_values[0][target];
	// if random is less than OR equal to 96, value of double of targets position in array 2 will be returned
	else if (random <= 96)
		return 2 * board_values[1][target];
	// if random is less than OR equal to 98, value of targets position in array will be returned
	else if (random <= 98)
		return board_values[0][target];
	// if random is any other value, value of targets position in array 2 will be returned
	else
		return board_values[1][target];
}