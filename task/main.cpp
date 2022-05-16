#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include "/home/platosha/Desktop/BMSTU/8sem/Diplom/postgresql-14.2/src/interfaces/libpq/libpq-fe.h"
#include "/home/platosha/Desktop/BMSTU/8sem/Diplom/postgresql-14.2/src/include/postgres_ext.h"

using namespace std;

const string CONN_FILE = "/home/platosha/Desktop/BMSTU/8sem/Diplom-source/connection_data/connection.data";
const string OUT_FILE = "/home/platosha/Desktop/BMSTU/8sem/Diplom-source/results/resultsMulti.txt";
const int NUM_CONNECTS = 1;

void readParamsFromFile(string &host, string &port,
    string &dbName, string &user, string &password)
{
    ifstream in(CONN_FILE);

    if (in.is_open()) {
        in >> host >> port >> dbName >> user >> password;
    }

    in.close();
}

void writeParamsToFile(const double seconds)
{
    ofstream out(OUT_FILE);

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
    }
    else {
        cout << "Thread function!\n";
        PGresult *res = PQexec(conn, "select * from pg_database;");

        //cout << "res status: " << PQresultStatus(res) << endl;
        cout << "res: " << (res == NULL) << endl;
        cout << PQerrorMessage(conn) << endl;

        /*if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            cout <<  PQerrorMessage(conn);
            PQclear(res);
            return;
        }
        */

        /*if (PQresultStatus(res) == PGRES_EMPTY_QUERY)
        {
            cout << "PGRES_EMPTY_QUERY!\n";
        } else if (PQresultStatus(res) == PGRES_COMMAND_OK)
        {
            cout << "PGRES_COMMAND_OK!\n";
        } else if (PQresultStatus(res) == PGRES_TUPLES_OK)
        {
            cout << "PGRES_TUPLES_OK!\n";
        } else if (PQresultStatus(res) == PGRES_COPY_OUT)
        {
            cout << "PGRES_COPY_OUT!\n";
        } else if (PQresultStatus(res) == PGRES_COPY_IN)
        {
            cout << "PGRES_COPY_IN!\n";
        } else if (PQresultStatus(res) == PGRES_BAD_RESPONSE)
        {
            cout << "PGRES_BAD_RESPONSE!\n";
        } else if (PQresultStatus(res) == PGRES_NONFATAL_ERROR)
        {
            cout << "PGRES_NONFATAL_ERROR!\n";
        } else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << "PGRES_FATAL_ERROR!\n";
        } else if (PQresultStatus(res) == PGRES_COPY_BOTH)
        {
            cout << "PGRES_COPY_BOTH!\n";
        } else if (PQresultStatus(res) == PGRES_SINGLE_TUPLE)
        {
            cout << "PGRES_SINGLE_TUPLE!\n";
        } else if (PQresultStatus(res) == PGRES_PIPELINE_SYNC)
        {
            cout << "PGRES_PIPELINE_SYNC!\n";
        } else if (PQresultStatus(res) == PGRES_PIPELINE_ABORTED)
        {
            cout << "PGRES_PIPELINE_ABORTED!\n";
        }
        */

        //PQclear(res);
    }
}

int main(void)
{
    string host, port, dbName, user, password;
    readParamsFromFile(host, port, dbName, user, password);

    try {
        thread thr[NUM_CONNECTS];

        clock_t begin = clock();

            PGconn *conn = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr,
                                        dbName.c_str(), user.c_str(), password.c_str());

            for (int i = 0; i < NUM_CONNECTS; i++) {
                thr[i] = thread(connectFunction, conn);
            }

            for (int i = 0; i < NUM_CONNECTS; i++) {
                thr[i].join();
            }

            PQfinish(conn);

        clock_t end = clock();

        double seconds = (double)(end - begin) / CLOCKS_PER_SEC;
        writeParamsToFile(seconds);

        return 0;
    }

    catch (const std::exception &er) {
        cerr << er.what() << endl;
        return 1;
    }
}
