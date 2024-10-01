#include "../include/executor.h"
using namespace std;
bool breakPoints[4096] = {0};

void RunTillBreakPoint(int totalLines)
{
    int line = ProgramCounter;
    for (line; line < totalLines; line++)
    {
        if (breakPoints[ProgramCounter])
        {
            cout << "Execution stoped at breakpoint" << endl;
            break;
        }
        executeInstruction();
    }

    cout << endl;
}
void executeInstruction()
{
    Instruction instruction = Lines[ProgramCounter];
    auto it = functionMap.find(instruction.mnemonic);
    it->second(instruction);
    string progctr;
    stringstream ss;
    ss << hex << ProgramCounter * 4;
    progctr = ss.str();
    if (progctr.length() != 8)
    {
        progctr = string(8 - progctr.length(), '0') + progctr;
    }
    progctr = "0x" + progctr;
    cout << "Executed: " << instructionMemory[ProgramCounter] << "; PC = " << progctr << endl;
    ProgramCounter++;
}