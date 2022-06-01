#include "libpq-fe.h"
#include "connection.h"

using namespace std;

const string CONN_FILE = "connection_data/connection.data";
static const char *QUERY = "SELECT * FROM table100;";

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

double singleConn(const int numConnects) 
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		clock_t begin = clock();

		for (int i = 0; i < numConnects; i++) {
			if (connect(host, port, dbName, user, password)) {
				break;
			}
		}
		
		clock_t end = clock();

		double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
		return seconds;
	} 

	catch (const std::exception &er) {
		cerr << er.what() << endl;
		return 1;
	}
}
