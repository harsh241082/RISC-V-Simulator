#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#include <sstream>
struct CPU
{
    int registers[32];
};
extern CPU *cpu;
void InitCPU(CPU *cpu);
int GetRegister(CPU *cpu, int regIndex);
void SetRegister(CPU *cpu, int regIndex, int value);
void ShowRegisters(CPU *cpu);
#endif