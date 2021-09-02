#pragma once
#pragma once
#include <iostream>
using namespace std;

class viewPlay
{
public:
	int checkWin(unsigned int row, unsigned int col, string player, string competitor);
	bool checkChessboard(unsigned int row, unsigned int col);
	void showChessboard();
	int putX(unsigned int row, unsigned int col);
	int putO(unsigned int row, unsigned int col);

private:
	string player1 = " X ";
	string player2 = " O ";
	unsigned int row;
	unsigned int col;
	string chessboard[10][10] = { "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //1
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //2
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",	  //3
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",	  //4
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //5
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //6
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //7
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //8
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //9
									"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   " };   //10
};

