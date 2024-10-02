#include "../include/executor.h"

bool breakPoints[4096] = {0};

void RunTillBreakPoint(int totalLines)
{
    int line = ProgramCounter;
    while (ProgramCounter < totalLines)
    {
        if (breakPoints[ProgramCounter])
        {
            std::cout << "Execution stoped at breakpoint" << std::endl;
            break;
        }
        executeInstruction();
    }

    std::cout << std::endl;
}
void executeInstruction()
{
    Instruction instruction = Lines[ProgramCounter];
    if (instruction.instructionInfo.format == InstructionFormat::B_TYPE || instruction.instructionInfo.format == InstructionFormat::J_TYPE)
    {
        auto labit = labelData.find(instruction.label);
        if (labit != labelData.end())
        {
            instruction.immediate = 4 * (labit->second - ProgramCounter);
        }
    }
    auto it = functionMap.find(instruction.mnemonic);
    if (instruction.instructionInfo.format == InstructionFormat::B_TYPE || instruction.instructionInfo.format == InstructionFormat::J_TYPE)
    {
        std::string progctr;
        std::stringstream ss;
        ss << std::hex << ProgramCounter * 4;
        progctr = ss.str();
        if (progctr.length() != 8)
        {
            progctr = std::string(8 - progctr.length(), '0') + progctr;
        }
        progctr = "0x" + progctr;
        std::cout << "Executed: " << instructionMemory[ProgramCounter] << "; PC = " << progctr << std::endl;
        it->second(instruction);
        return;
    }
    std::string progctr;
    std::stringstream ss;
    ss << std::hex << ProgramCounter * 4;
    progctr = ss.str();
    if (progctr.length() != 8)
    {
        progctr = std::string(8 - progctr.length(), '0') + progctr;
    }
    progctr = "0x" + progctr;
    std::cout << "Executed: " << instructionMemory[ProgramCounter] << "; PC = " << progctr << std::endl;
    it->second(instruction);
    ProgramCounter++;
}