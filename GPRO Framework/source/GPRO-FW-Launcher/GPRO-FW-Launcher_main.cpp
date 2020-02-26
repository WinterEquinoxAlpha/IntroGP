// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdio.h>
#include <iostream>
#include <ctime>
#include "IntroGP_FW/header.h"
using namespace std;

int main()
{
	srand(time(NULL));
	bool play = true;
	int age = rand() % 120 + 1;
	cout << "Guess my age between 1 and 120" << endl;
	while (play)
	{
		int guess = NULL;
		//cout << age << endl;
		cout << "Enter your guess:";
		while (guess == NULL)
		{
			cin >> guess;
			// If the user input cannot be assigned to the variable, ask again
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please enter an integer (in the set age range):";
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		int checkedGuess = checkGuess(age, guess);
		if (checkedGuess < 0)
		{
			cout << "Too low." << endl;
		}
		else if (checkedGuess > 0)
		{
			cout << "Too high." << endl;
		}
		else
		{
			cout << "Noice" << endl;
			bool goodInput = false;
			while (!goodInput)
			{
				cout << "Replay? (y/n)";
				char answer = NULL;
				cin >> answer;
				if (answer == 'y')
				{
					cout << "Ok." << endl;
					age = rand() % 120 + 1;
					system("CLS");
					goodInput = true;
				}
				else if (answer == 'n')
				{
					cout << "Ok bye." << endl;
					play = false;
					goodInput = true;
				}
				else
				{
					cout << "Not an option idoit." << endl;
					char answer = NULL;
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}
	return 0;
}