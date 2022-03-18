#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include "libpq-fe.h"

using namespace std;

const string CONN_FILE = "connection_data/connection.data";
const string OUT_FILE = "results/resultsMulti.txt";
const int NUM_CONNECTS = 10;

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
	ofstream out(OUT_FILE);

	if (out.is_open()) {
		out << seconds << endl;
	}

	out.close();

	cout << "Data was written to file!\n";
}

void connectFunction(const string host, const string port, const string dbName, 
					 const string user, const string password)
{
	PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr, 
    									dbName.c_str(), user.c_str(), password.c_str());

    if (PQstatus(conn) != CONNECTION_OK) {
    	cout << "Can't open database: " << PQerrorMessage(conn) << endl;
    }

    PQfinish(conn);
}

int main(void) 
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
		thread thr[NUM_CONNECTS];

		clock_t begin = clock();

			for (int i = 0; i < NUM_CONNECTS; i++) {
				thr[i] = thread(connectFunction, host, port, dbName, user, password);
			}

			for (int i = 0; i < NUM_CONNECTS; i++) {
				thr[i].join();
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
