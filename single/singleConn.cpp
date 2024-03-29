#include <iostream>
#include <fstream>
#include <ctime>
#include "libpq-fe.h"

using namespace std;

const string CONN_FILE = "../connection_data/connection.data";
const string OUT_FILE = "../results/single.txt";

int NUM_CONNECTS = 10;
const char *QUERY = "SELECT * FROM table100;";


void readParamsFromFile(const string filename, 
	string &host, string &port, 
	string &dbName, string &user, string &password)
{
	ifstream in(CONN_FILE);
	
	if (in.is_open()) {
		in >> host >> port >> dbName >> user >> password;
	}

	in.close();
}

void writeParamsToFile(const string filename, const double seconds)
{
	ofstream out;
	out.open(filename, ios::app);

	if (out.is_open()) {
		out << seconds << endl;
	}

	out.close();

	cout << "Data was written to file!\n";
}

int connect(string &host, string &port, 
			 string &dbName, string &user, string &password)
{
	PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr, 
								dbName.c_str(), user.c_str(), password.c_str());

	if (PQstatus(conn) != CONNECTION_OK) {
		PQfinish(conn);
		cout << "Can't open database: " << PQerrorMessage(conn) << endl;
		return 1;
	}

	PGresult *res = PQexec(conn, QUERY);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		PQclear(res);
		PQfinish(conn);
		cout << "Database query completed with an error: " << PQresultStatus(res) << endl;
		return 1;
	}

	PQclear(res);
	PQfinish(conn);

	return 0;
}

int main(int argc, char *argv[]) 
{
	if (argc == 2) {
		NUM_CONNECTS = strtol(argv[1], NULL, 10);
	}

	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		clock_t begin = clock();

		for (int i = 0; i < NUM_CONNECTS; i++) {
			if (!connect(host, port, dbName, user, password)) {
				break;
			}
		}
		
		clock_t end = clock();
		
		double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
		writeParamsToFile(OUT_FILE, seconds);	

		return 0;
	} 

	catch (const std::exception &er) {
		cerr << er.what() << endl;
		return 1;
	}
}
