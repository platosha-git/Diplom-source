#include <iostream>
#include "connection.h"

using namespace std;

enum Mode
{
	exitMenu,
	single,
	multi,
	pool,
	custom,
	compare
};

void menu()
{
	//system("clear");

	cout << "|_____________MODE______________|\n";
	cout << "|                               |\n";
	cout << "| Single connection...........1 |\n";
	cout << "| Multithreaded connection....2 |\n";
	cout << "| Pool connection.............3 |\n";
	cout << "| Custom connection...........4 |\n";
	cout << "|                               |\n";
	cout << "| Full comparison.............5 |\n";
	cout << "| Exit........................0 |\n";
	cout << "|_______________________________|\n";
	cout << "\n>> ";
}

int getNumber(const string inputMsg)
{
	int number = 0;

	cout << inputMsg;
	cin >> number;

	return number;
}

int getNumConnects()
{
	int numConnects = 0;
	while (numConnects < 1 || numConnects > 1000) {
		numConnects = getNumber("Input the number of connections (1-1000): ");
	}

	return numConnects;
}

int getNumThreads()
{
	int numThreads = 0;
	while (numThreads < 1 || numThreads > 500) {
		numThreads = getNumber("Input the number of threads (1-500): ");
	}

	return numThreads;
}

int main(void)
{
	menu();

	int choose = -1;
	while (true) {
		
		cin >> choose;

		if (choose < single || choose > compare) {
			break;
		}

		int numConnects = getNumConnects();

		int numThreads = 0;
		if (choose != single) {
			numThreads = getNumThreads();
		}

		switch (choose) {
		case(single): {
			singleConn(numConnects);
			break;
		}
		case(multi): {
			multiConn(numThreads);
			break;
		}
		case(pool): {
			poolConn(numThreads);
			break;
		}
		case(custom): {
			customConn(numThreads);
			break;
		}
		//case(5):

		default:
			break;
		}
	}

	return 0;
}
