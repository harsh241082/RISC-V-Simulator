#include "../include/data.h"
#include <unordered_map>

Instruction Lines[4096] = {};
std::unordered_map<std::string, int> labelData = {};
int ProgramCounter = 0;
int EmptyLines[4096] = {};
cache cacheData;