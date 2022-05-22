#ifndef MULTI_H
#define MULTI_H

#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include "iofile.h"

double singleConn(const int numConnects);
double multiConn(const int numThreads);
double poolConn(const int numThreads);
double customConn(const int numThreads);

#endif //MULTI_H
