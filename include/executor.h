#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "data.h"
#include "linerunner.h"
#include "memory.h"
#include <iostream>
extern bool breakPoints[4096];
void executeInstruction();
void RunTillBreakPoint(int totalLines);
#endif