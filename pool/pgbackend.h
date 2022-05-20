#ifndef PGBACKEND_H
#define PGBACKEND_H

#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <libpq-fe.h>
#include "pgconnection.h"

using namespace std;

class PGBackend
{
public:
    PGBackend();
    shared_ptr<PGConnection> connection();
    void freeConnection(shared_ptr<PGConnection>);

private:
    void createPool();
    
    mutex m_mutex;
    condition_variable m_condition;
    queue<shared_ptr<PGConnection>> m_pool;

    const int POOL_SIZE = 500;
};

#endif //PGBACKEND_H
