#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_BATTLESHIP_PLAYERS				2
#define GS_BATTLESHIP_BOARD_WIDTH			10
#define GS_BATTLESHIP_BOARD_HEIGHT			10

enum gs_battleship_space_state
{
	// invalid space state
	gs_battleship_space_invalid = -1,

	// states visible to both players
	gs_battleship_space_open,			// space is open and unguessed
	gs_battleship_space_miss,			// space was guessed and missed
	gs_battleship_space_hit,			// space was guessed and hit

	// states hidden from opponent player
	gs_battleship_space_patrol2,		// 2-unit patrol boat
	gs_battleship_space_submarine3,		// 3-unit submarine
	gs_battleship_space_destroyer3,		// 3-unit destroyer
	gs_battleship_space_battleship4,	// 4-unit battleship
	gs_battleship_space_carrier5,		// 5-unit carrier
};
#ifndef __cplusplus
typedef		enum gs_battleship_space_state	gs_battleship_space_state;
#endif	// !__cplusplus

// battleship game state
typedef		unsigned char					gs_battleship_index;
typedef		gs_battleship_space_state		gs_battleship[GS_BATTLESHIP_PLAYERS][GS_BATTLESHIP_BOARD_WIDTH][GS_BATTLESHIP_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,z,w,h,d)		(x < w && y < h && z < d)
#define GS_BATTLESHIP_VALID(p,x,y)				GS_VALIDATE_COORDINATE(x,y,p,GS_BATTLESHIP_BOARD_WIDTH,GS_BATTLESHIP_BOARD_HEIGHT,GS_BATTLESHIP_PLAYERS)


inline gs_battleship_space_state gs_checkers_getSpaceState(gs_battleship const game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos]);
	return gs_battleship_space_invalid;
}

inline gs_battleship_space_state gs_checkers_setSpaceState(gs_battleship game, gs_battleship_space_state const state, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos] = state);
	return gs_battleship_space_invalid;
}

inline gs_battleship_index gs_battleship_reset(gs_battleship game)
{
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
				game[player][xpos][ypos] = gs_battleship_space_open;
	total = (player * xpos * ypos);
	return total;
}

inline void gs_battleship_printBoard(gs_battleship const game, gs_battleship_index const player, bool showTargeting)
{
	// Prints the player number
	cout << "Player " << (int)player << endl;

	// Ship board
	// Prints top bar
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	// Loops through every space
	for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; y++)
	{
		// Prints side bar
		cout << (char)('A' + y) << " ";
		for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; x++)
		{
			// Prints the board characters based on space state
			switch (gs_checkers_getSpaceState(game, player, x, y))
			{
			case gs_battleship_space_open:
				cout << "  ";
				break;
			case gs_battleship_space_miss:
				cout << "- ";
				break;
			case gs_battleship_space_hit:
				cout << "* ";
				break;
			case gs_battleship_space_patrol2:
				cout << "P ";
				break;
			case gs_battleship_space_submarine3:
				cout << "S ";
				break;
			case gs_battleship_space_destroyer3:
				cout << "D ";
				break;
			case gs_battleship_space_battleship4:
				cout << "B ";
				break;
			case gs_battleship_space_carrier5:
				cout << "C ";
				break;
			default:
				cout << "+ ";
				break;
			}
		}
		cout << endl;
	}

	// Targeting board
	if (showTargeting)
	{
		// Prints top bar
		cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
		// Loops through every space
		for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; y++)
		{
			// Prints side bar
			cout << (char)('A' + y) << " ";
			for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; x++)
			{
				// Prints the board characters based on space state
				switch (gs_checkers_getSpaceState(game, -player + 1, x, y))
				{
				case gs_battleship_space_open:
					cout << "  ";
					break;
				case gs_battleship_space_miss:
					cout << "- ";
					break;
				case gs_battleship_space_hit:
					cout << "* ";
					break;
				default:
					cout << "  ";
					break;
				}
			}
			cout << endl;
		}
	}
}

inline void gs_battleship_checkShipSet(gs_battleship const game, gs_battleship_index const player, int& row, int& col)
{
	string move{};
	bool okMove = false;
	while (!okMove)
	{
		bool okInput = false;
		while (!okInput)
		{
			// Prompts the player for their input
			cout << "Where to place (eg. A5):";
			cin >> move;
			// Ensures the input is the proper length
			if (move.length() >= 2)
			{
				okInput = true;
			}
		}
		// Gets the column number
		col = (int)(toupper(move[0])) - 65;
		// Gets the row number
		if (move.length() == 2)
		{
			row = (int)(move[1]) - 48;
		}
		else
		{
			row = ((int)(move[1]) - 48) * 10 + (int)(move[2]) - 48;
		}

		// Checks if the row and column exist on the board and reprompts the player if invalid
		if (gs_checkers_getSpaceState(game, player, row, col) != gs_battleship_space_open)
		{
			cout << "Invalid move" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			okMove = true;
		}
	}
}

inline void gs_battleship_setShips(gs_battleship game, gs_battleship_index const player, int& row, int& col)
{
	// Loops for each ship
	for (int i = 0; i < 5; i++)
	{
		bool goodPlace;
		bool goodDir;
		// For each ship...
		switch (i)
		{
		case 0:
			cout << "Patrol (2): ";
			goodPlace = false;
			while (!goodPlace) {
				// Asks player for placement position
				gs_battleship_checkShipSet(game, player, row, col);
				goodDir = false;
				// Asks player for direction
				cout << "Direction (0=Horrizontal,1=Vertical):";
				int dir{};
				// Validates direction input
				while (!goodDir)
				{
					cin >> dir;
					// If the player dosen't input a number...
					if (cin.fail())
					{
						cout << "NAN" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					// If the number is out of range
					else if (dir > 1 || dir < 0)
					{
						cout << "OOR" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
					}
					else
					{
						goodDir = true;
					}
				}
				bool invalidSpace = false;
				int checkRow = row;
				int checkCol = col;
				// Looks at each space the ship would take up and checks if it is empty
				for (int i = 0; i < 2; i++)
				{
					if (gs_checkers_getSpaceState(game, player, checkRow, checkCol) != gs_battleship_space_open)
					{
						invalidSpace = true;
					}
					if (dir == 1)
					{
						checkCol++;
					}
					else
					{
						checkRow++;
					}
				}

				// If a space is full
				if (invalidSpace)
				{
					cout << "Cannot place ship there" << endl;
				}
				else
				{
					checkRow = row;
					checkCol = col;
					// Updates the board
					for (int i = 0; i < 2; i++)
					{
						gs_checkers_setSpaceState(game, gs_battleship_space_patrol2, player, checkRow, checkCol);
						if (dir == 1)
						{
							checkCol++;
						}
						else
						{
							checkRow++;
						}
					}
					goodPlace = true;
				}
			}
			// Prints the board
			gs_battleship_printBoard(game, player, false);
			break;
		case 1:
			cout << "\nSubmarine (3):";
			goodPlace = false;
			while (!goodPlace) {
				gs_battleship_checkShipSet(game, player, row, col);
				goodDir = false;
				cout << "Direction (0=Horrizontal,1=Vertical):";
				int dir{};
				while (!goodDir)
				{
					cin >> dir;
					if (cin.fail())
					{
						cout << "NAN" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else if (dir > 1 || dir < 0)
					{
						cout << "OOR" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
					}
					else
					{
						goodDir = true;
					}
				}
				bool invalidSpace = false;
				int checkRow = row;
				int checkCol = col;
				for (int i = 0; i < 3; i++)
				{
					if (gs_checkers_getSpaceState(game, player, checkRow, checkCol) != gs_battleship_space_open)
					{
						invalidSpace = true;
					}
					if (dir == 1)
					{
						checkCol++;
					}
					else
					{
						checkRow++;
					}
				}
				if (invalidSpace)
				{
					cout << "Cannot place ship there" << endl;
				}
				else
				{
					checkRow = row;
					checkCol = col;
					for (int i = 0; i < 3; i++)
					{
						gs_checkers_setSpaceState(game, gs_battleship_space_submarine3, player, checkRow, checkCol);
						if (dir == 1)
						{
							checkCol++;
						}
						else
						{
							checkRow++;
						}
					}
					goodPlace = true;
				}
			}
			gs_battleship_printBoard(game, player, false);
			break;
		case 2:
			cout << "\nDestroyer (3):";
			goodPlace = false;
			while (!goodPlace) {
				gs_battleship_checkShipSet(game, player, row, col);
				goodDir = false;
				cout << "Direction (0=Horrizontal,1=Vertical):";
				int dir{};
				while (!goodDir)
				{
					cin >> dir;
					if (cin.fail())
					{
						cout << "NAN" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else if (dir > 1 || dir < 0)
					{
						cout << "OOR" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
					}
					else
					{
						goodDir = true;
					}
				}
				bool invalidSpace = false;
				int checkRow = row;
				int checkCol = col;
				for (int i = 0; i < 3; i++)
				{
					if (gs_checkers_getSpaceState(game, player, checkRow, checkCol) != gs_battleship_space_open)
					{
						invalidSpace = true;
					}
					if (dir == 1)
					{
						checkCol++;
					}
					else
					{
						checkRow++;
					}
				}
				if (invalidSpace)
				{
					cout << "Cannot place ship there" << endl;
				}
				else
				{
					checkRow = row;
					checkCol = col;
					for (int i = 0; i < 3; i++)
					{
						gs_checkers_setSpaceState(game, gs_battleship_space_destroyer3, player, checkRow, checkCol);
						if (dir == 1)
						{
							checkCol++;
						}
						else
						{
							checkRow++;
						}
					}
					goodPlace = true;
				}
			}
			gs_battleship_printBoard(game, player, false);
			break;
		case 3:
			cout << "\nBattleship (4):";
			goodPlace = false;
			while (!goodPlace) {
				gs_battleship_checkShipSet(game, player, row, col);
				goodDir = false;
				cout << "Direction (0=Horrizontal,1=Vertical):";
				int dir{};
				while (!goodDir)
				{
					cin >> dir;
					if (cin.fail())
					{
						cout << "NAN" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else if (dir > 1 || dir < 0)
					{
						cout << "OOR" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
					}
					else
					{
						goodDir = true;
					}
				}
				bool invalidSpace = false;
				int checkRow = row;
				int checkCol = col;
				for (int i = 0; i < 4; i++)
				{
					if (gs_checkers_getSpaceState(game, player, checkRow, checkCol) != gs_battleship_space_open)
					{
						invalidSpace = true;
					}
					if (dir == 1)
					{
						checkCol++;
					}
					else
					{
						checkRow++;
					}
				}
				if (invalidSpace)
				{
					cout << "Cannot place ship there" << endl;
				}
				else
				{
					checkRow = row;
					checkCol = col;
					for (int i = 0; i < 4; i++)
					{
						gs_checkers_setSpaceState(game, gs_battleship_space_battleship4, player, checkRow, checkCol);
						if (dir == 1)
						{
							checkCol++;
						}
						else
						{
							checkRow++;
						}
					}
					goodPlace = true;
				}
			}
			gs_battleship_printBoard(game, player, false);
			break;
		case 4:
			cout << "\nCarrier (5):";
			goodPlace = false;
			while (!goodPlace) {
				gs_battleship_checkShipSet(game, player, row, col);
				goodDir = false;
				cout << "Direction (0=Horrizontal,1=Vertical):";
				int dir{};
				while (!goodDir)
				{
					cin >> dir;
					if (cin.fail())
					{
						cout << "NAN" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else if (dir > 1 || dir < 0)
					{
						cout << "OOR" << endl;
						cout << "Direction (0=Horrizontal,1=Vertical):";
					}
					else
					{
						goodDir = true;
					}
				}
				bool invalidSpace = false;
				int checkRow = row;
				int checkCol = col;
				for (int i = 0; i < 5; i++)
				{
					if (gs_checkers_getSpaceState(game, player, checkRow, checkCol) != gs_battleship_space_open)
					{
						invalidSpace = true;
					}
					if (dir == 1)
					{
						checkCol++;
					}
					else
					{
						checkRow++;
					}
				}
				if (invalidSpace)
				{
					cout << "Cannot place ship there" << endl;
				}
				else
				{
					checkRow = row;
					checkCol = col;
					for (int i = 0; i < 5; i++)
					{
						gs_checkers_setSpaceState(game, gs_battleship_space_carrier5, player, checkRow, checkCol);
						if (dir == 1)
						{
							checkCol++;
						}
						else
						{
							checkRow++;
						}
					}
					goodPlace = true;
				}
			}
			system("CLS");
			gs_battleship_printBoard(game, player, false);
			break;
		}
	}
}

inline void gs_battleship_checkMove(gs_battleship game, gs_battleship_index const player, int& row, int& col)
{
	string move{};
	bool okMove = false;
	while (!okMove)
	{
		bool okInput = false;
		while (!okInput)
		{
			// Prompts the player for their input
			cout << "Where to attack (eg. A5):";
			cin >> move;
			// Ensures the input is the proper length
			if (move.length() >= 2)
			{
				okInput = true;
			}
		}
		// Gets the column number
		col = (int)(toupper(move[0])) - 65;
		// Gets the row number
		if (move.length() == 2)
		{
			row = (int)(move[1]) - 48;
		}
		else
		{
			row = ((int)(move[1]) - 48) * 10 + (int)(move[2]) - 48;
		}

		// Checks if the row and column exist on the board and reprompts the player if invalid
		if (gs_checkers_getSpaceState(game, -player + 1, row, col) == gs_battleship_space_invalid || gs_checkers_getSpaceState(game, -player + 1, row, col) == gs_battleship_space_hit || gs_checkers_getSpaceState(game, -player + 1, row, col) == gs_battleship_space_miss)
		{
			cout << "Invalid move" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			okMove = true;
		}
	}
	if (gs_checkers_getSpaceState(game, -player + 1, row, col) != gs_battleship_space_open)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_hit, -player + 1, row, col);
		cout << "Hit!" << endl;
	}
	else
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_miss, -player + 1, row, col);
		cout << "Miss!" << endl;
	}
}

inline int gs_battleship_checkOver(gs_battleship game)
{
	int loser = 0;
	for (int i = 0; i < GS_BATTLESHIP_PLAYERS; i++)
	{
		bool shipSpace = false;
		for (int y = 0; y < GS_BATTLESHIP_BOARD_HEIGHT; y++)
		{
			for (int x = 0; x < GS_BATTLESHIP_BOARD_WIDTH; x++)
			{
				if (gs_checkers_getSpaceState(game, i, x, y) != gs_battleship_space_open && gs_checkers_getSpaceState(game, i, x, y) != gs_battleship_space_hit && gs_checkers_getSpaceState(game, i, x, y) != gs_battleship_space_miss)
				{
					shipSpace = true;
				}
			}
		}
		if (!shipSpace)
		{
			loser = i + 1;
			break;
		}
	}
	return loser;
}

//-----------------------------------------------------------------------------
// DEFINITIONS

int launchBattleship()
{
	gs_battleship game;// = { 0 };
	gs_battleship_index player = 0;
	int row{};
	int col{};
	gs_battleship_reset(game);

	// Asks each player to input their ship positions
	do
	{
		gs_battleship_printBoard(game, player, false);
		cout << "\nPlayer " << (int)player << ", place your ships" << endl;
		gs_battleship_setShips(game, player, row, col);
		system("pause");
		player++;
		system("CLS");
	} while ((int)player < 2);
	player = 0;

	int isGameOver = 0;
	while (isGameOver == 0)
	{
		gs_battleship_printBoard(game, player, true);
		gs_battleship_checkMove(game, player, row, col);
		system("pause");
		system("CLS");
		gs_battleship_printBoard(game, player, true);
		system("pause");
		system("CLS");
		isGameOver = gs_battleship_checkOver(game);
		player = -player + 1;
	}

	if (isGameOver == 1)
	{
		cout << "Player 1 wins!" << endl;
	}
	else
	{
		cout << "Player 0 wins!" << endl;
	}

	return 0;
}
//-----------------------------------------------------------------------------