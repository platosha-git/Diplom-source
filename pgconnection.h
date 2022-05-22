#ifndef PGCONNECTION_H
#define PGCONNECTION_H

#include <memory>
#include <mutex>
#include <libpq-fe.h>

class PGConnection
{
public:
    PGConnection(const std::string host, const std::string port, 
                 const std::string dbName, const std::string user, const std::string password);
    std::shared_ptr<PGconn> connection() const;

private:
    void establish_connection();
    std::shared_ptr<PGconn>  m_connection;
};

#endif //PGCONNECTION_H
