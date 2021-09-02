#pragma once
#include <iostream>
using namespace std;

class viewPlay
{
public:
	viewPlay();
	int checkWin(unsigned int row, unsigned int col, string player, string competitor);
	void showChessboard();
	int putX();
	int putO();

private:
	string player1 = " X ";
	string player2 = " O ";
	unsigned int row;
	unsigned int col;
string chessboard[10][10] =    {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ",     //1
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

