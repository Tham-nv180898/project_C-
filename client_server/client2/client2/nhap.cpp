#include <iostream>
#include <string>
using namespace std;

int main()
{
	char a[10] = "1";
	int b = stoi(a);
	cout << b << endl;
	cout << typeid(b).name() << endl;
	return 0;
}