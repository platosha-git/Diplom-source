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

	cout << "|___________РЕАЛИЗАЦИЯ__________|\n";
	cout << "|                               |\n";
	cout << "| Однопоточная................1 |\n";
	cout << "| Многопоточная...............2 |\n";
	cout << "| Внешний пул.................3 |\n";
	cout << "| Разработанный метод.........4 |\n";
	cout << "|                               |\n";
	cout << "| Сравнение...................5 |\n";
	cout << "| Выход.......................0 |\n";
	cout << "|_______________________________|\n";
}

void outputTable(const int numConn, 
				const double single, const double multi, 
				const double pool, const double custom)
{
	cout << endl << numConn << " соединений\n";

	cout << "       Время (сек)      \n";
	cout << "------------------------\n";
	cout << "однопоточная  | " << single << endl;
	cout << "многопоточная | " << multi << endl;
	cout << "пул           | " << pool << endl;
	cout << "метод         | " << custom << endl;
}

int getNumber(const string inputMsg)
{
	int number = 0;

	cout << inputMsg;
	cin >> number;

	return number;
}

int getNumConnects(const string inputMsg)
{
	int numConnects = 0;
	while (numConnects < 1 || numConnects > MAX_NUM_CONN) {
		numConnects = getNumber(inputMsg);
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

		switch (choose) {
		case(single): {
			int numConnects = getNumConnects("Введите число соединений (1-1000): ");
			double resS = singleConn(numConnects);
			cout << "\nSELECT * FROM table100;\n";
			cout << "Результат: ОК\n";
			cout << "Время: " << resS << endl;
			break;
		}
		case(multi): {
			int numConnects = getNumConnects("Введите число потоков (1-1000): ");
			double resM = multiConn(numConnects);
			cout << "\nSELECT * FROM table100;\n";
			cout << "Результат: ОК\n";
			cout << "Время: " << resM << endl;
			break;
		}
		case(pool): {
			int numConnects = getNumConnects("Введите число соединений (1-1000): ");
			double resP = poolConn(numConnects);
			cout << "\nSELECT * FROM table100;\n";
			cout << "Результат: ОК\n";
			cout << "Время: " << resP << endl;
			break;
		}
		case(custom): {
			int numConnects = getNumConnects("Введите число потоков (1-1000): ");
			double resC = customConn(numConnects);
			cout << "\nSELECT * FROM table100;\n";
			cout << "Результат: ОК\n";
			cout << "Время: " << resC << endl;
			break;
		}
		case(compare): {
			int numConnects = getNumConnects("Введите число соединений (1-1000): ");
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
