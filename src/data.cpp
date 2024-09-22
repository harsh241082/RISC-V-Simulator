#include "../include/data.h"
#include "../include/instruction.h"
#include <unordered_map>

Instruction Lines[50] = {};
std::unordered_map<std::string, int> labelData = {};
int ProgramCounter = 0;
int EmptyLines[50] = {};