#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include "pgbackend.h"

using namespace std;

PGBackend::PGBackend(const string host, const string port, 
              		 const string dbName, const string user, const string password)
{
	createPool(host, port, dbName, user, password); 
}

void PGBackend::createPool(const string host, const string port, 
              		 	   const string dbName, const string user, const string password)
{
	lock_guard<mutex> locker_( m_mutex );

	for (int i = 0; i < POOL_SIZE; i++) {
		m_pool.emplace(make_shared<PGConnection>(host, port, dbName, user, password));
	}
}

shared_ptr<PGConnection> PGBackend::connection()
{
	unique_lock<mutex> lock_( m_mutex );

	while (m_pool.empty()){
		m_condition.wait(lock_);
	}

	auto conn = m_pool.front();
	m_pool.pop();

	return conn;
}


void PGBackend::freeConnection(shared_ptr<PGConnection> conn)
{
	unique_lock<mutex> lock_(m_mutex);
	m_pool.push(conn);
	lock_.unlock();
	m_condition.notify_one();
}
