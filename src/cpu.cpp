#include "../include/cpu.h"
void InitCPU(CPU* cpu){
    for(int i = 0; i < 32; i++){
        cpu->registers[i] = 0;
    }
}
int GetRegister(CPU* cpu, int regIndex){
    return cpu->registers[regIndex];
}
void SetRegister(CPU* cpu, int regIndex, int value){
    if(regIndex!=0)
    cpu->registers[regIndex] = value;
}