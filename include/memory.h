#ifndef MEMORY_H
#define MEMORY_H
#include "utilis.h"
#include "data.h"
#include <sstream>
#include <iostream>
#include <string>
#define MEMORY_SIZE 16384;
extern std::string instructionMemory[4096];
extern int Memory[16384];
extern int stackPointer = 16384;
void ShowMemory(std::string address, int count);

#endif