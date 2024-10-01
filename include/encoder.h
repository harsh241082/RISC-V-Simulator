#ifndef ENCODER_H
#define ENCODER_H
#include "instruction.h"
#include <unordered_map>
#include "risc-v.h"
#include "data.h"
#include "parser.h"
// returns a string with hex code
std::string InstructionToHex(Instruction instruct);

#endif