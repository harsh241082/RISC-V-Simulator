#include "../include/executor.h"
using namespace std;
bool breakPoints[4096] = {0};

void RunTillBreakPoint(int totalLines)
{
    for (ProgramCounter; ProgramCounter < totalLines; ProgramCounter++)
    {
        if (breakPoints[ProgramCounter])
        {
            cout << "Exicution stoped at breakpoint\n"
                 << endl;
            break;
        }
        exicuteInstruction();
    }
}
void executeInstruction()
{
    Instruction instruction = Lines[ProgramCounter];

    string progctr;
    stringstream ss;
    ss << hex << ProgramCounter * 4;
    progctr = ss.str();
    if (progctr.length() != 8)
    {
        progctr = string(8 - progctr.length(), '0') + progctr;
    }
    progctr = "0x" + progctr;
    cout << "Executed:" << instructionMemory[ProgramCounter] << "; PC = " << progctr << endl;
    ProgramCounter++;
}