#include <iostream>
#include "connection.h"

using namespace std;

const int MAX_NUM_CONN = 1000;

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
	system("clear");

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
}

void outputTable(const int numConn, 
				const double single, const double multi, 
				const double pool, const double custom)
{
	cout << endl << numConn << " connects\n";

	cout << "            Time     \n";
	cout << "------------------\n";
	cout << "single    " << single << endl;
	cout << "multi     " << multi << endl;
	cout << "pool      " << pool << endl;
	cout << "custom    " << custom << endl;
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
	while (numConnects < 1 || numConnects > MAX_NUM_CONN) {
		numConnects = getNumber("Input the number of connections (1-1000): ");
	}

	return numConnects;
}

int main(void)
{
	menu();

	int choose = -1;
	while (true) {
		cout << "\n>> ";		
		cin >> choose;

		if (choose < single || choose > compare) {
			break;
		}

		int numConnects = getNumConnects();

		switch (choose) {
		case(single): {
			double resS = singleConn(numConnects);
			cout << "\nTime: " << resS << endl;
			break;
		}
		case(multi): {
			double resM = multiConn(numConnects);
			cout << "\nTime: " << resM << endl;
			break;
		}
		case(pool): {
			double resP = poolConn(numConnects);
			cout << "\nTime: " << resP << endl;
			break;
		}
		case(custom): {
			double resC = customConn(numConnects);
			cout << "\nTime: " << resC << endl;
			break;
		}
		case(compare): {
			double ts = singleConn(numConnects);
			double tm = multiConn(numConnects);
			double tp = poolConn(numConnects);
			double tc = customConn(numConnects);

			outputTable(numConnects, ts, tm, tp, tc);
			break;
		}
		default:
			break;
		}
	}

	return 0;
}
