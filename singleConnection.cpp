#include <iostream>
#include <fstream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

const string CONN_FILE = "connection.data";

void readParamsFromFile(const string filename, 
	string &dbName, string &user, 
	string &password, string &host, string &port)
{
	ifstream in(CONN_FILE);
    
    if (in.is_open()) {
        in >> dbName >> user >> password >> host >> port;
    }

    in.close();
}

string formConnStr()
{
	string dbName, user, password, host, port;
	readParamsFromFile(CONN_FILE, dbName, user, password, host, port);

	string 	connStr = "dbname = " + dbName;
			connStr += " user = " + user;
			connStr += " password = " + password;
			connStr += " hostaddr = " + host;
			connStr += " port = " + port;

	return connStr;
}

int main(int argc, char* argv[]) 
{
	string connStr = formConnStr();

	try {
    	connection C(connStr);

      	if (C.is_open()) {
         	cout << "Opened database successfully: " << C.dbname() << endl;
      	} 
      	else {
         	cout << "Can't open database" << endl;
         	return 1;
      	}

      	C.disconnect ();
      	return 0;

   	} 
   	catch (const std::exception &e) {
      	cerr << e.what() << std::endl;
      	return 1;
   	}
}
