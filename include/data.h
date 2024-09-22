#ifndef Main_H
#define Main_H
#include "instruction.h"
#include <unordered_map>
extern Instruction Lines[50];
extern std::unordered_map<std::string, int> labelData;
extern int ProgramCounter;
extern int EmptyLines[50];
#endif