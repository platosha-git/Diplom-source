#ifndef IOFILE_H
#define IOFILE_H

#include <iostream>
#include <fstream>
#include <ctime>

void readParamsFromFile(const std::string filename, 
						std::string &host, std::string &port, 
						std::string &dbName, std::string &user, std::string &password);

void writeParamsToFile(const std::string filename, const double result);

#endif //IOFILE_H