#include "iofile.h"

using namespace std;

void readParamsFromFile(const string filename, 
						string &host, string &port, 
						string &dbName, string &user, string &password)
{
	ifstream in(filename);
	
	if (in.is_open()) {
		in >> host >> port >> dbName >> user >> password;
	}

	in.close();
}

void writeParamsToFile(const string filename, const double result)
{
	ofstream out;
	out.open(filename, ios::app);

	if (out.is_open()) {
		out << result << endl;
	}

	out.close();

	cout << "Data was written to file!\n";
}