#ifndef PARSER_H
#define PARSER_H

#include "instruction.h"
#include <iostream>
#include <vector>
#include <string>

// takes a line and returns a sturct of type Instruction

Instruction parseInstruction(const std::string &line);

#endif