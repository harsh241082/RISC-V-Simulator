#ifndef MEMORY_H
#define MEMORY_H
#include "utilis.h"
#include "data.h"
#include <sstream>
#include <iostream>
#include <string>
extern std::string instructionMemory[4096];
extern char Memory[262145];
extern int stackPointer;
void ShowMemory(std::string address, int count);
void storeMemory(int address, int Numbytes, int value);
int fechMemory(int address, int Numbytes);
void showCallStack();
#endif