#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#include <sstream>
struct CPU
{
    __int64 registers[32];
};
extern CPU *cpu;
void InitCPU(CPU *cpu);
__int64 GetRegister(CPU *cpu, int regIndex);
void SetRegister(CPU *cpu, int regIndex, __int64 value);
void ShowRegisters(CPU *cpu);
#endif