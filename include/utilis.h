#ifndef UTILIS_H
#define UTILIS_H

#include <vector>
#include <string>

// function takes a line and returns vators with all the instrections
std::vector<std::string> tokenize(const std::string &line);

// converts string to int
int strToInt(const std::string &num);

// converts registers to int
int rigToInt(const std::string &num);
#endif