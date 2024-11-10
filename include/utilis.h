#ifndef UTILIS_H
#define UTILIS_H
#include "encoder.h"
#include "risc-v.h"
#include "data.h"
#include <vector>
#include <string>
#include <sstream>

// function takes a line and returns vators with all the instrections
std::vector<std::string> tokenize(std::string &line);

// converts string to int
int64_t strToInt(const std::string &num);

// converts registers to int
int rigToInt(const std::string &num);

std::vector<std::string> split(const std::string &str);
#endif