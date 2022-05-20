#include <thread>
#include <iostream>
#include <fstream>
#include "pgbackend.h"

using namespace std;

const string OUT_FILE = "/home/platosha/Desktop/BMSTU/8sem/Diplom-source/results/ddos/pool500.txt";

const int NUM_CONNECTS = 500;
const char *QUERY = "SELECT * FROM pg_database;";

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


int main(void)
{
	auto pgbackend = make_shared<PGBackend>();
	thread thr[NUM_CONNECTS];

	clock_t begin = clock();

		for (int i = 0; i < NUM_CONNECTS; i++) {
			thr[i] = thread(connectFunction, pgbackend);
		}

		for (int i = 0; i < NUM_CONNECTS; i++) {
			thr[i].join();
		}

	clock_t end = clock();

	double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
	writeParamsToFile(OUT_FILE, seconds);	

	return 0;
}
