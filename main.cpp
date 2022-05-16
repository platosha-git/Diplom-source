#include <iostream>

using namespace std;

void menu()
{
	system("clear");
	cout << "|_____________MODE______________|\n";
	cout << "|                               |\n";
	cout << "| Exit........................0 |\n";
	cout << "| Single connection...........1 |\n";
	cout << "| Multithreaded connection....2 |\n";
	cout << "| Pool connection.............3 |\n";
	cout << "| Custom connection...........4 |\n";
	cout << "|_______________________________|\n";
	cout << "\n>> ";
}

int main(void)
{
	menu();
	
	int choose = -1;
	cin >> choose;

	cout << "choose = " << choose << endl;

	return 0;
}