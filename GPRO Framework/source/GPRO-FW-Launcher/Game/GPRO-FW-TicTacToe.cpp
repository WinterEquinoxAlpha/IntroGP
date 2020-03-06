#include <stdio.h>
#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};

#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}

inline void gs_tictactoe_printBoard(gs_tictactoe const game)
{
	for (int y = 0; y < GS_TICTACTOE_BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < GS_TICTACTOE_BOARD_WIDTH; x++)
		{
			switch (gs_tictactoe_getSpaceState(game, x, y))
			{
			case gs_tictactoe_space_open:
				cout << " ";
				break;

			case gs_tictactoe_space_o:
				cout << "O";
				break;

			case gs_tictactoe_space_x:
				cout << "X";
				break;
			}
			if (x < GS_TICTACTOE_BOARD_WIDTH - 1) cout << "|";
		}
		cout << endl;
		if (y < GS_TICTACTOE_BOARD_HEIGHT - 1)
		{
			for (int i = 0; i < (GS_TICTACTOE_BOARD_WIDTH * 2) - 1; i++)
			{
				cout << (i % 2 == 0 ? "-" : "+");
			}
			cout << endl;
		}
	}
}


//-----------------------------------------------------------------------------
// DEFINITIONS

int launchTicTacToe()
{
	gs_tictactoe game;// = { 0 };

	gs_tictactoe_reset(game);

	bool turn = false;

	gs_tictactoe_printBoard(game);

	int move = 0;
	int win = 0;

	while (win == 0) {
		cout << "Where? (1-9):";
		cin >> move;
		move--;
		system("CLS");
		bool succ = false;
		while (!succ)
		{
			if (gs_tictactoe_getSpaceState(game, move % 3, floor(move / 3)) == gs_tictactoe_space_open)
			{
				succ = true;
				if (turn) {
					gs_tictactoe_setSpaceState(game, gs_tictactoe_space_o, move % 3, floor(move / 3));
					turn = false;
				}
				else
				{
					gs_tictactoe_setSpaceState(game, gs_tictactoe_space_x, move % 3, floor(move / 3));
					turn = true;
				}
				
			}
			else
			{
				gs_tictactoe_printBoard(game);
				cout << "Invalid space:";
				cin >> move;
				move--;
				system("CLS");
			}
		}
		gs_tictactoe_printBoard(game);

		if (gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 2, 0) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 2, 1) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 2) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 2, 2) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 0, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 1, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 2) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 2, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 2, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 2, 2) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 2, 2) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 2, 0) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_x && gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_space_x)
		{
			win = 1;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 2, 0) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 2, 1) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 2) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 2, 2) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 0, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 1, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 2) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 2, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 2, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 2, 2) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 2, 2) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 2, 0) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_space_o && gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_space_o)
		{
			win = 2;
		}
		else if (gs_tictactoe_getSpaceState(game, 0, 0) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 0, 1) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 0, 2) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 1, 0) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 1, 1) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 1, 2) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 2, 0) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 2, 1) != gs_tictactoe_space_open && gs_tictactoe_getSpaceState(game, 2, 2) != gs_tictactoe_space_open)
		{
			win = 3;
		}
	}

	if (win == 1)
	{
		cout << "X Wins" << endl;
	}
	else if (win == 2)
	{
		cout << "O Wins" << endl;
	}
	else
	{
		cout << "Tie" << endl;
	}
	system("pause");
	return 0;
}
//-----------------------------------------------------------------------------