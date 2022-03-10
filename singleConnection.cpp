#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

const string DB_NAME = "test14";
const string USER = "postgres";
const string PASSWORD = "22rfrnec";
const string HOST = "127.0.0.1";
const string PORT = "5432";

string formConnStr()
{
	string 	connStr = "dbname = " + DB_NAME;
			connStr += " user = " + USER;
			connStr += " password = " + PASSWORD;
			connStr += " hostaddr = " + HOST;
			connStr += " port = " + PORT;

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
