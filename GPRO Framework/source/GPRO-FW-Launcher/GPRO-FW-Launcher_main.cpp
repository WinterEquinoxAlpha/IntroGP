// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using namespace std;

int launchTicTacToe();
int launchBattleship();

int main()
{
	bool playAgain = true;
	while (playAgain)
	{
		cout << "Choose a game" << endl;
		cout << "1: Tic-Tac-Toe" << endl;
		cout << "2: Battleship" << endl;
		cout << "Enter choice:";
		bool goodChoice = false;
		int choice = 0;
		while (!goodChoice)
		{
			cin >> choice;
			// If the player dosen't input a number...
			if (cin.fail())
			{
				cout << "Please enter 1 or 2:";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			// If the number is out of range
			else if (choice > 2 || choice < 1)
			{
				cout << "Please enter 1 or 2:";
			}
			else
			{
				goodChoice = true;
			}
		}
		system("CLS");
		if (choice == 1)
		{
			launchTicTacToe();
		}
		else
		{
			launchBattleship();
		}
		system("CLS");
		cout << "Play again? (y/n):";
		char playAgainResponse;
		cin >> playAgainResponse;
		if (playAgainResponse == 'n')
		{
			playAgain = false;
		}
		system("CLS");
	}
}