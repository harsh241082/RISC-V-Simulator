#ifndef MEMORY_H
#define MEMORY_H
#include "utilis.h"
#include "data.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <queue>
#include <fstream>
extern std::string instructionMemory[4096];
extern char Memory[262145];
extern int stackPointer;
extern int StoreDataAddr;
void ShowMemory(std::string address, int count);
void storeMemory(int address, int Numbytes, __int64 value);
__int64 fechMemory(int address, int Numbytes);
void storeData(std::vector<std::string> StoreData);
void DumpCache(std::string filename);
extern std::ofstream CacheResult;
void invalidatecache();
#endif