#ifndef PGCONNECTION_H
#define PGCONNECTION_H

#include <memory>
#include <mutex>
#include <libpq-fe.h>

class PGConnection
{
public:
    PGConnection();
    std::shared_ptr<PGconn> connection() const;

private:
    void establish_connection();

    std::string host = "127.0.0.1";
    int port = 5432;
    std::string dbName = "conn";
    std::string user = "postgres";
    std::string password = "22rfrnec";

    std::shared_ptr<PGconn>  m_connection;
};


#endif //PGCONNECTION_H
