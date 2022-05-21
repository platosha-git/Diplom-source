#include "libpq-fe.h"
#include "connection.h"

using namespace std;

const string CONN_FILE = "connection_data/connection.data";
const string OUT_FILE = "results/multi.txt";

static const char *QUERY = "SELECT * FROM table100;";

void connectFunction(const string host, const string port, const string dbName, 
					 const string user, const string password)
{
	PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr, 
										dbName.c_str(), user.c_str(), password.c_str());

	if (PQstatus(conn) != CONNECTION_OK) {
		PQfinish(conn);
		cout << "Can't open database: " << PQerrorMessage(conn) << endl;
		return;
	}

	PGresult *res = PQexec(conn, QUERY);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		PQclear(res);
		cout << "Database query completed with an error: " << PQresultStatus(res) << endl;
		return;
	}
	
	PQclear(res);
	PQfinish(conn);
}

void multiConn(const int numThreads) 
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		thread thr[numThreads];

		clock_t begin = clock();

			for (int i = 0; i < numThreads; i++) {
				thr[i] = thread(connectFunction, host, port, dbName, user, password);
			}

			for (int i = 0; i < numThreads; i++) {
				thr[i].join();
			}

		clock_t end = clock();
		
		double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
		cout << "\nTime: " << seconds << endl;
		writeParamsToFile(OUT_FILE, seconds);	
	} 

	catch (const std::exception &er) {
		cerr << er.what() << endl;
	}
}
