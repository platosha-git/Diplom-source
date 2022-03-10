#include <iostream>
#include <fstream>
#include "libpq-fe.h"

using namespace std;

const string CONN_FILE = "connection.data";

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

int main(void) 
{
	string host, port, dbName, user, password;
	readParamsFromFile(CONN_FILE, host, port, dbName, user, password);

	try {
    	PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), 
    		nullptr, nullptr, dbName.c_str(), user.c_str(), password.c_str());

      	if (PQstatus(conn) == CONNECTION_OK) {
         	cout << "Opened database successfully: " << PQdb(conn) << endl;
      	} 
      	else {
         	cout << "Can't open database: " << PQerrorMessage(conn) << endl;
         	return 1;
      	}

      	PQfinish(conn);
      	return 0;
   	} 

   	catch (const std::exception &er) {
      	cerr << er.what() << endl;
      	return 1;
   	}
}
