#include "../include/cpu.h"
CPU *cpu = new CPU;

void InitCPU(CPU *cpu)
{
    for (int i = 0; i < 32; i++)
    {
        cpu->registers[i] = 0;
    }
}
int GetRegister(CPU *cpu, int regIndex)
{
    return cpu->registers[regIndex];
}
void SetRegister(CPU *cpu, int regIndex, int value)
{
    if (regIndex != 0)
        cpu->registers[regIndex] = value;
}

void ShowRegisters(CPU *cpu)
{
    for (int i = 0; i < 32; i++)
    {
        std::stringstream ss;
        ss << std::hex << cpu->registers[i];
        std::string regStr = ss.str();
        regStr = "0x" + regStr;
        if (i < 10)
            std::cout << "x" << i << "  = " << regStr << std::endl;
        else
            std::cout << "x" << i << " = " << regStr << std::endl;
    }
    std::cout << std::endl;
}