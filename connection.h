#ifndef MULTI_H
#define MULTI_H

#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include "iofile.h"

void singleConn(const int numConnects);
void multiConn(const int numThreads);
int poolConn(const int numThreads);
int customConn(const int numThreads);

#endif //MULTI_H