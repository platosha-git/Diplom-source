#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <ctime>
#include "libpq-fe.h"

using namespace std;

const string CONN_FILE = "../connection_data/connection.data";
const string OUT_FILE = "../results/compare/taskD.txt";

const char *QUERY = "DELETE FROM table100 WHERE day='2';";

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

void connectFunction(PGconn *conn)
{
	if (PQstatus(conn) != CONNECTION_OK) {
		cout << "Can't open database: " << PQerrorMessage(conn) << endl;
		return;
	}

	PGresult *res = PQexecThread(conn, QUERY);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		PQclear(res);
		cout << "Database query completed with an error: " << PQresultStatus(res) << endl;
		return;
	}

	PQclear(res);
}

int main(void) 
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		clock_t begin = clock();

			PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr, 
										dbName.c_str(), user.c_str(), password.c_str());

			connectFunction(conn);

			PQfinish(conn);

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
