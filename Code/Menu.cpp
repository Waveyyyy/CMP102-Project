#include <iostream> // allowing for cout / cin to be used
#include <fstream>	// allows reading of files
#include <string>	// allows string to be used as a data type

#include "Menu.h" // include header for Menu class

// function deals with displaying the main menus basic gui
char Menu::mainMenu()
{
	// initialise variables
	std::string lineTxt = "";
	char menuChoice = ' ';

	// opens txt file 'mainMenu' for reading
	std::ifstream displayMenu("mainMenu.txt");

	// while there are lines left in the file, continue reading and printing to console
	while (std::getline(displayMenu, lineTxt))
	{
		// take current lines text, print to console then move to the next line
		std::cout << lineTxt << std::endl;
	}
	// take an input from the user, this will be the option selected
	// 1 = start a new game
	// 2 = read rules
	std::cin >> menuChoice;

	// return value input by user above
	return menuChoice;
}

// function deals with displaying the results text
void Menu::resultsScreen()
{
	// initialise variables
	std::string lineTxt = "";

	// opens txt file 'mainMenu' for reading
	std::ifstream resultsText("Results.txt");

	// while there are lines left in the file, continue reading and printing to console
	while (std::getline(resultsText, lineTxt))
	{
		// take current lines text, print to console then move to the next line
		std::cout << lineTxt << std::endl;
	}
}