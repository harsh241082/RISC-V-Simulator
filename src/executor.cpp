#include "../include/executor.h"

bool breakPoints[4096] = {0};

void RunTillBreakPoint(int totalLines)
{
    for (ProgramCounter; ProgramCounter < totalLines; ProgramCounter++)
    {
        if (breakPoints[ProgramCounter])
        {
            break;
        }
        exicuteInstruction();
    }
}
void exicuteInstruction()
{
}