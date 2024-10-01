#ifndef LINERUNNER_H
#define LINERUNNER_H

#include "instruction.h"
#include "cpu.h"
#include "memory.h"
#include "data.h"
#include <unordered_map>

extern std::unordered_map<std::string, void (*)(Instruction)> functionMap;

#endif