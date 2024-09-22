#ifndef CPU_H
#define CPU_H
struct CPU{
    int registers[32];
};

void InitCPU(CPU* cpu);
int GetRegister(CPU* cpu, int regIndex);
void SetRegister(CPU* cpu, int regIndex, int value);
#endif