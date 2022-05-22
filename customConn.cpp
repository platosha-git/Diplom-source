#include "libpq-fe.h"
#include "connection.h"

using namespace std;

const string CONN_FILE = "connection_data/connection.data";
static const char *QUERY = "SELECT * FROM table100;";

void connectFunction(PGconn *conn, const int idx)
{
	if (PQstatus(conn) != CONNECTION_OK) {
		cout << "Can't open database: " << PQerrorMessage(conn) << endl;
		return;
	}

	PGresult *res = PQexecThread(conn, QUERY);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		PQclear(res);
		cout << "Database query completed with an error: " << PQresultStatus(res) << endl;
		return;
	}

	PQclear(res);
}

double customConn(const int numThreads) 
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		thread thr[numThreads];

		clock_t begin = clock();

			PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr, 
										dbName.c_str(), user.c_str(), password.c_str());

			for (int i = 0; i < numThreads; i++) {
				thr[i] = thread(connectFunction, conn, i);
			}

			for (int i = 0; i < numThreads; i++) {
				thr[i].join();
			}

			PQfinish(conn);

		clock_t end = clock();
		
		double seconds = (double)(end - begin) / CLOCKS_PER_SEC;	
		return seconds;
	} 

	catch (const std::exception &er) {
		cerr << er.what() << endl;
		return 1;
	}
}
