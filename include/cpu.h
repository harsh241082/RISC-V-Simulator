#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#include <sstream>
extern CPU *cpu;
struct CPU
{
    int registers[32];
};

void InitCPU(CPU *cpu);
int GetRegister(CPU *cpu, int regIndex);
void SetRegister(CPU *cpu, int regIndex, int value);
void ShowRegisters(CPU *cpu);
#endif