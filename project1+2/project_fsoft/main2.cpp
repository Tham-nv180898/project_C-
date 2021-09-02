#include <iostream>
#include <string>
#include <fstream>	
#include <windows.h>
#include <tchar.h>
using namespace std;




class registerNickName
{	
public:
	registerNickName(string);
	bool checkNickName(string, string);
	unsigned int getNumberPlayer();
	void initializeNickName();
	bool checkplayer();


private:
	string name;
	char file[12] = "./file.ini";
	unsigned int win = 0;
	unsigned int lose = 0;
	unsigned int draw = 0;
};

// contructor of class registerNickName
registerNickName::registerNickName(string name)
{
	this->name = name;
}

// check your nick name
bool registerNickName::checkNickName(string name, string section)
{
	char checkName[20];
	GetPrivateProfileStringA(section.c_str(), "name", "No name", checkName, 20, file);;
	if (name == checkName)
		return true;
	else
		return false;
}

// get the number of player
unsigned int registerNickName::getNumberPlayer()
{
	int number = GetPrivateProfileIntA("number of players", "number", 0, file);
	return number;
}
// initialize Nick Name
void registerNickName::initializeNickName()
{
	bool checker = false;
	unsigned int number = getNumberPlayer();
	for (int i = 0; i < number; i++)
	{
		string section1 = "Player" + to_string(i);
		checker = checkNickName(this->name, section1);
		if (checker == true)
			break;
	}
	if (checker == 1)
	{
		cout << "This name is already registered!" << endl;
		checker = false;
	}
	else
	{
		// register nick name
		string section2 = "Player" + to_string(getNumberPlayer());
		WritePrivateProfileStringA(section2.c_str(), "Name", this->name.c_str(), file);
		WritePrivateProfileStringA(section2.c_str(), "Win", "0", file);
		WritePrivateProfileStringA(section2.c_str(), "Loss", "0", file);
		WritePrivateProfileStringA(section2.c_str(), "Draw", "0", file);

		// update number of players
		WritePrivateProfileStringA("number of players", "number", to_string(getNumberPlayer() + 1).c_str(), file);
		cout << "Your name has been registered successfully" << endl;
	}
}

bool registerNickName::checkplayer()
{
	bool checker = false;
	unsigned int number = getNumberPlayer();
	for (int i = 0; i < number; i++)
	{
		string section1 = "Player" + to_string(i);
		checker = checkNickName(this->name, section1);
		if (checker == true)
			break;
	}
	return checker;
}


int main()
{	

	int input = 0;
	int input1 = 0;
	while (true)
	{

		cout << "=====GOMOCU GAME=====" << endl;
		cout << "1. LOGIN" << endl;
		cout << "2. REGISTER" << endl;
		cout << "3. EXIT" << endl;
		cout << "INPUT: ";
		cin >> input;

		while (cin.fail() or input > 3)
		{
			cin.clear();
			cin.ignore(256, '\n');   // ignore the line change
			cout << "INPUT: ";
			cin >> input;

		}

		// login 
		if (input == 1)
		{
			string name;
			bool checker = false;
			char cont_ex;
			int choose;

			system("cls");
			cout << "=====LOGIN=====" << endl;
			cout << "ENTER NAME: ";
			cin.ignore(256, '\n');
			getline(cin, name);
			registerNickName player(name);
			checker = player.checkplayer();

			if (checker == true)
			{
				cout << "Successful login!" << endl;
				cout << "Press a key to continue: ";
				cin >> cont_ex;
				system("cls");
				cout << "1. Play Game" << endl;
				cout << "2. Back" << endl;

				cin.ignore(256, '\n');
				cout << "INPUT: ";
				cin >> input1;

				while (cin.fail() or input1 > 2)
				{
					cin.clear();
					cin.ignore(256, '\n');   // ignore the line change
					cout << "INPUT: ";
					cin >> input1;
				}

				if (input1 == 1)
				{
					system("cls");
					cout << "1. X" << endl;
					cout << "2. O" << endl;
					cout << "Choose: ";
					cin >> choose;
				}
				if (input1 == 2)
				{
					system("cls");
				}
			}
			else
			{
				cout << "This name doesn't exist yet. please register!" << endl;
				cout << "Press a key to back: ";
				cin >> cont_ex;
				system("cls");
			}

		}

		//register
		if (input == 2)
		{
			string name;
			char exit;
			system("cls");
			cout << "=====REGISTER=====" << endl;
			cout << "ENTER NAME: ";

			cin.ignore(256, '\n');
			getline(cin, name);
			while (name.length() > 20)
			{
				cout << "The number of characters in the name cannot be more than 20!" << endl;
				cout << "ENTER NAME AGAIN: ";
				getline(cin, name);
			}
			registerNickName player(name);
			player.initializeNickName();
			// enter to close
			cout << "Press a key to back: ";
			cin >> exit;
			system("cls");
		}

		else if (input == 3)
		{
			break;
		}
	}
	return 0;
}