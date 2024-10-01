#include "../include/cpu.h"
using namespace std;
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
        stringstream ss;
        ss << hex << cpu->registers[i];
        string regStr = ss.str();
        regStr = "0x" + regStr;
        std::cout << "x" << i << " = " << regStr << std::endl;
    }
    cout << endl;
}