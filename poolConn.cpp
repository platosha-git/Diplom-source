#include "pgbackend.h"
#include "connection.h"

using namespace std;

const string CONN_FILE = "connection_data/connection.data";
const string OUT_FILE = "results/custom.txt";

static const char *QUERY = "SELECT * FROM table100;";

void connectFunction(shared_ptr<PGBackend> pgbackend)
{
	auto conn = pgbackend->connection();
	
	PGresult *res = PQexec(conn->connection().get(), QUERY);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		PQclear(res);
		cout << "Database query completed with an error: " << PQresultStatus(res) << endl;
		return;
	}
	
	PQclear(res);
	pgbackend->freeConnection(conn);
}


int poolConn(const int numThreads)
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		auto pgbackend = make_shared<PGBackend>();
		thread thr[numThreads];

		clock_t begin = clock();

			for (int i = 0; i < numThreads; i++) {
				thr[i] = thread(connectFunction, pgbackend);
			}

			for (int i = 0; i < numThreads; i++) {
				thr[i].join();
			}

		clock_t end = clock();

		double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
		cout << "\nTime: " << seconds << endl;
		writeParamsToFile(OUT_FILE, seconds);	

		return seconds;
	}

	catch (const std::exception &er) {
		cerr << er.what() << endl;
		return 1;
	}
}
