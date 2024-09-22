#ifndef ENCODER_H
#define ENCODER_H
#include "instruction.h"
#include <unordered_map>

//returns a string with hex code
std::string InstructionToHex(Instruction instruct);

#endif