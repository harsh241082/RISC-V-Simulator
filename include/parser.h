#ifndef PARSER_H
#define PARSER_H

#include "instruction.h"
#include "utilis.h"
#include "risc-v.h"
#include <iostream>
#include <vector>
#include <string>

// takes a line and returns a sturct of type Instruction

Instruction parseInstruction(std::string &line);

#endif