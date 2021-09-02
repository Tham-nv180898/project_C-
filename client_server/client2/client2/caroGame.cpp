#include <iostream>
#include "caroGame.h"

using namespace std;

int viewPlay::checkWin(unsigned int row, unsigned int col, string player, string competitor)
{
	// check condition along row.
	if ((chessboard[row][col] == chessboard[row + 1][col]) and (chessboard[row][col] != chessboard[row - 1][col]))
	{
		if ((chessboard[row + 1][col] == chessboard[row + 2][col]) and (chessboard[row + 2][col] == chessboard[row + 3][col]))
		{
			if (chessboard[row - 1][col] != competitor and chessboard[row + 4][col] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}

	else if ((chessboard[row][col] == chessboard[row - 1][col]) and (chessboard[row][col] != chessboard[row + 1][col]))
	{
		if ((chessboard[row - 1][col] == chessboard[row - 2][col]) and (chessboard[row - 2][col] == chessboard[row - 3][col]))
		{
			if (chessboard[row + 1][col] != competitor and chessboard[row - 4][col] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}

	else if ((chessboard[row][col] == chessboard[row - 1][col]) and (chessboard[row][col] == chessboard[row + 1][col]))
	{
		if ((chessboard[row - 1][col] == chessboard[row - 2][col]) and (chessboard[row - 3][col] != competitor) and (chessboard[row + 2][col] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
		else if ((chessboard[row + 1][col] == chessboard[row + 2][col]) and (chessboard[row + 3][col] != competitor) and (chessboard[row - 2][col] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
	}

	// check condition along the column
	else if ((chessboard[row][col] == chessboard[row][col + 1]) and (chessboard[row][col] != chessboard[row][col - 1]))
	{
		if ((chessboard[row][col + 1] == chessboard[row][col + 2]) and (chessboard[row][col + 2] == chessboard[row][col + 3]))
		{
			if (chessboard[row][col - 1] != competitor and chessboard[row][col + 4] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}

	else if ((chessboard[row][col] == chessboard[row][col - 1]) and (chessboard[row][col] != chessboard[row][col + 1]))
	{
		if ((chessboard[row][col - 1] == chessboard[row][col - 2]) and (chessboard[row][col - 2] == chessboard[row][col - 3]))
		{
			if (chessboard[row][col + 1] != competitor and chessboard[row][col - 4] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}

	else if ((chessboard[row][col] == chessboard[row][col - 1]) and (chessboard[row][col] == chessboard[row][col + 1]))
	{
		if ((chessboard[row][col - 1] == chessboard[row][col - 2]) and (chessboard[row][col - 3] != competitor) and (chessboard[row][col + 2] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
		else if ((chessboard[row][col + 1] == chessboard[row][col + 2]) and (chessboard[row][col + 3] != competitor) and (chessboard[row][col - 2] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
	}

	// check condition along the cross
	// the first cross
	else if ((chessboard[row][col] == chessboard[row + 1][col + 1]) and (chessboard[row][col] != chessboard[row - 1][col - 1]))
	{
		if ((chessboard[row + 1][col + 1] == chessboard[row + 2][col + 2]) and (chessboard[row + 2][col + 2] == chessboard[row + 3][col + 3]))
		{
			if (chessboard[row - 1][col - 1] != competitor and chessboard[row + 4][col + 4] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}
	else if ((chessboard[row][col] == chessboard[row - 1][col - 1]) and (chessboard[row][col] != chessboard[row + 1][col + 1]))
	{
		if ((chessboard[row - 1][col - 1] == chessboard[row - 2][col - 2]) and (chessboard[row - 2][col - 2] == chessboard[row - 3][col - 3]))
		{
			if (chessboard[row + 1][col + 1] != competitor and chessboard[row - 4][col - 4] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}

	else if ((chessboard[row][col] == chessboard[row - 1][col - 1]) and (chessboard[row][col] == chessboard[row + 1][col + 1]))
	{
		if ((chessboard[row - 1][col - 1] == chessboard[row - 2][col - 2]) and (chessboard[row - 3][col - 3] != competitor) and (chessboard[row + 2][col + 2] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
		else if ((chessboard[row + 1][col + 1] == chessboard[row + 2][col + 2]) and (chessboard[row + 3][col + 3] != competitor) and (chessboard[row - 2][col - 2] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
	}

	// the second cross
	else if ((chessboard[row][col] == chessboard[row - 1][col + 1]) and (chessboard[row][col] != chessboard[row + 1][col - 1]))
	{
		if ((chessboard[row - 1][col + 1] == chessboard[row - 2][col + 2]) and (chessboard[row - 2][col + 2] == chessboard[row - 3][col + 3]))
		{
			if (chessboard[row + 1][col - 1] != competitor and chessboard[row - 4][col + 4] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}
	else if ((chessboard[row][col] == chessboard[row + 1][col - 1]) and (chessboard[row][col] != chessboard[row - 1][col + 1]))
	{
		if ((chessboard[row + 1][col - 1] == chessboard[row + 2][col - 2]) and (chessboard[row + 2][col - 2] == chessboard[row + 3][col - 3]))
		{
			if (chessboard[row - 1][col + 1] != competitor and chessboard[row + 4][col - 4] != competitor)
			{
				cout << "player is the winner with" + player + "chess" << endl;
				return 1;
			}
		}
	}
	else if ((chessboard[row][col] == chessboard[row - 1][col + 1]) and (chessboard[row][col] == chessboard[row + 1][col - 1]))
	{

		if ((chessboard[row - 1][col + 1] == chessboard[row - 2][col + 2]) and (chessboard[row - 3][col + 3] != competitor) and (chessboard[row + 2][col - 2] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
		else if ((chessboard[row + 1][col - 1] == chessboard[row + 2][col - 2]) and (chessboard[row + 3][col - 3] != competitor) and (chessboard[row - 2][col + 2] != competitor))
		{
			cout << "player is the winner with" + player + "chess" << endl;
			return 1;
		}
	}
}

void viewPlay::showChessboard()
{
	cout << "     Player 1 <X> - Player 2 <O>" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "STT";
	for (int k = 0; k < 10; k++)
	{
		cout << "|" << " " << k << " ";
	}
	cout << "|\n============================================" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << "|" << i << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << "|" << chessboard[i][j];
		}
		cout << "|\n--------------------------------------------" << endl;
	}
}

// the player put X or O into the chessboard 
int viewPlay::putX(unsigned int row, unsigned int col)
{
	system("cls");
	chessboard[row][col] = player1;
	showChessboard();
	int ret = checkWin(row, col, player1, player2);
	return ret;
}


int viewPlay::putO(unsigned int row, unsigned int col)
{
	system("cls");
	chessboard[row][col] = player2;
	showChessboard();
	int ret = checkWin(row, col, player2, player1);
	return ret;
}

bool viewPlay::checkChessboard(unsigned int row, unsigned int col)
{
	if (chessboard[row][col] == player1 or chessboard[row][col] == player2)
		return 1;
	else
		return 0;

}

