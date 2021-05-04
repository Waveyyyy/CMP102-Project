#include <iostream>			// allows for use of cout / cin etc.
#include <string>			// allows for use of string as a data type
#include <ctime>			// used in conjunction with srand to seed random number generation to the current time
#include <Windows.h>		// allows for use of sleep function

#include "Game.h"			// includes the Game class header
#include "Player.h"			// includes the Player class header
#include "Menu.h"			// includes the Menu class header

Menu displayMenu;			// create an instance of the Menu class called displayMenu

Player* player_one;			// create a pointer reference to the Player class called player_one
Player* player_two;			// create a pointer reference to the Player class called player_two

Game* newGame;				// create a pointer reference ot the Game class called newGame

int main()
{
	srand(time(NULL));		// use the current time as a seed for random number generation

	// initialise local variables
	std::string name;								// holds players names temporarily
	short int accuracy;								// holds players accuracy temporarily
	char menuChoice = displayMenu.mainMenu();		// initialise menuChoice to returned value of mainMenu function
	int matches = 0;								// initialise games variable, which will store number of games to be played
	short int p1throw = 0, p2throw = 0;				// initialise pxthrow variables (where x is either 1 or 2) used to determine which player goes first

	
	do  // do while, is used here to run code atleast once before exiting
	{
		// when menuChoice is 1, the user has chosen to start a game
		if (menuChoice == '1')
		{
			system("cls");			// clear console for cleaner output
			break;					// breaks from current loop, which starts game
		}

		// when menuChoice is 2, the user has chosen to display the rules
		else if (menuChoice == '2')
		{

			// print to console simplified rules for darts 501
			std::cout << std::endl << std::endl <<
				"In Darts 501 you start with a score of 501 and the goal is " << std::endl <<
				"to reach zero and have your final dart thrown be either a " << std::endl <<
				"bullseye or a double." << std::endl << std::endl <<
				"Each round players have 3 darts, once one player has thrown " << std::endl <<
				"all three of their darts, its the next players turn, " << std::endl <<
				"rinse and repeat until there's a winner." << std::endl << std::endl;

			
			// display the main menu again, also allowing user to choose to display rules again or start a game
			menuChoice = displayMenu.mainMenu();
		}

	} while (menuChoice != '1');	// while menuchoice is not equal to 1, continue looping

	system("cls");					// clear console for cleaner output

	for (int i = 0; i < 2; i++)		// loop once for each player
	{
		do  // do while, is used here to run code atleast once before exiting
		{
			// print to console and recieve name input from user
			std::cout << "Enter name of player " << i + 1 << ": ";
			std::cin >> name;
			std::cout << std::endl;

			// print to console and recieve accuracy input from user
			std::cout << "Enter accuracy of player " << i + 1 << ": ";
			std::cin >> accuracy;
			std::cout << std::endl;

			system("cls");			// clear console for cleaner output

		} while (name == "" || accuracy <= 0);	// while name is empty OR accuracy is 0, continue looping until otherwise

		// check which number the loop is on, depending on if first or second loop add name and accuracy to corresponding player
		if (i == 0)
		{
			// give name and accuracy chosen above as parameters to player_one constructor
			player_one = new Player(name, accuracy);
		}
		else if (i == 1)
		{
			// same as player_one
			player_two = new Player(name, accuracy);
		}
	}
	
	// print to console detailing how its decided which player goes first
	std::cout << "Players throw for a bullseye to see who goes first, " << std::endl;
	
	do // do while, is used here to run code atleast once before exiting
	{
		// variables store the value returned from the throw_bull function
		// which will be used to decide which player goes first
		p1throw = newGame->throw_bull(player_one->GETplayerAccuracy());
		p2throw = newGame->throw_bull(player_two->GETplayerAccuracy());

		// print to console what score each player got
		std::cout << "Player " << player_one->GETplayerName() << " threw a score of: " << p1throw << std::endl << std::endl;
		std::cout << "Player " << player_two->GETplayerName() << " threw a score of: " << p2throw << std::endl << std::endl;

		Sleep(1000);	// sleep for one second to allow user to see score thrown before it gets ( possibly ) cleared below
		
		// if player_one's score is a bullseye AND higher than player_two's then player_one goes first
		if (p1throw == 50 && p1throw > p2throw)
		{
			// order that players are input into the Game constructor is how theyre ordered
			// in the players array within the game class, meaning player to the left is
			// in the first position of the array
			newGame = new Game(player_one, player_two);

			std::cout << "This means that player one goes first. " << std::endl << std::endl;
		}
		//  if player_two's score is a bullseye AND higher than player_one's then player_two goes first
		else if (p2throw == 50 && p2throw > p1throw)
		{
			// same as described above
			newGame = new Game(player_two, player_one);

			std::cout << "This means that player two goes first. " << std::endl << std::endl;
		}
		// if the players scores are equal, player_one goes first by default
		else
		{
			// below is to stop the loop from breaking if no player is certain winner
			p1throw = 0;		// reset p1throw to zero
			p2throw = 0;		// reset p2throw to zero

			system("cls");		// clear console for cleaner output
			
			std::cout << "No definative first player, trying again." << std::endl << std::endl;

			Sleep(2000);		// sleep for 2 seconds before clearing console, allows user to see message printed just before

			system("cls");		// clear console for cleaner output

		}
		// while p1throw AND p2throw are equal to zero, continue looping
	} while (p1throw == 0 && p2throw == 0);

	
	do  // do while, is used here to run code atleast once before exiting
	{
		// print to console asking the user how many matches to play,
		// one match is best of 7 sets ( 13 max played )
		// one set is best of 3 games ( 5 max played )
		std::cout << "Number of championship matches to play? " << std::endl << "Answer: ";
		std::cin >> matches;
		std::cout << std::endl;
		
		system("cls");			// clear console for cleaner output
		
		// while matches variable is less than OR equal to zero, continue looping
	} while (matches <= 0);


	// loop for amount of matches input by user above
	for (int i = 0; i < matches; i++)
	{
		// function that contains the gameplay loop
		newGame->gamePlay();
	}
	
	
	
	int counter = 10;	// initialise counter variable to 10, the amount of seconds the countdown should be

	do {
		newGame->matchResults(matches);		// call the matchResults function, and pass the matches variable in
		std::cout << std::endl << "Exiting in " << counter << "...";
		Sleep(1000);						// sleep for 10 seconds, allowing user to read output
		system("cls");						// clear console
		counter--;							// decrement counter variable
	} while (counter != 0);

	return 0;		// return an int value
	exit(420);		// exit with arbitrary exit code
}