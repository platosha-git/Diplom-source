#include "pgconnection.h"

using namespace std;

PGConnection::PGConnection()
{
    m_connection.reset(PQsetdbLogin(host.c_str(), to_string(port).c_str(), nullptr, nullptr, 
                                    dbName.c_str(), user.c_str(), password.c_str()), &PQfinish);

    if (PQstatus(m_connection.get()) != CONNECTION_OK && 
        PQsetnonblocking(m_connection.get(), 1) != 0 ) {
       throw runtime_error(PQerrorMessage(m_connection.get()));
    }
}

shared_ptr<PGconn> PGConnection::connection() const
{
    return m_connection;
}
