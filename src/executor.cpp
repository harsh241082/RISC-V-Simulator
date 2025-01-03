#include "../include/executor.h"

bool breakPoints[4096] = {0};

void RunTillBreakPoint(int totalLines)
{
    int line = ProgramCounter;
    if (breakPoints[ProgramCounter])
    {
        executeInstruction(totalLines);
    }
    while (ProgramCounter < totalLines)
    {
        if (breakPoints[ProgramCounter])
        {
            std::cout << "Execution stoped at breakpoint" << std::endl;
            break;
        }
        executeInstruction(totalLines);
    }

    std::cout << std::endl;
}
void executeInstruction(int noOfLines)
{
    Instruction instruction = Lines[ProgramCounter];
    if (instruction.error != "")
    {
        std::cout << "Error: " << instruction.error << "at line " << ProgramCounter + 1 << std::endl;
        ProgramCounter++;
        exit(0);
    }
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
        std::string line = instructionMemory[ProgramCounter];
        int index = line.find(":");
        if (index != std::string::npos)
            line = line.substr(index + 2, line.length());
        std::cout << "Executed: " << line << "; PC = " << progctr << std::endl;
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
    std::string line = instructionMemory[ProgramCounter];
    int index = line.find(":");
    if (index != std::string::npos)
        line = line.substr(index + 2, line.length());
    std::cout << "Executed: " << line << "; PC = " << progctr << std::endl;
    it->second(instruction);
    ProgramCounter++;
    if (ProgramCounter >= noOfLines)
    {
        printf("\nD-cache statistics: Accesses=%d, Hit=%d, Miss=%d, Hit Rate=%.2f\n\n", (cacheData.hit + cacheData.miss), cacheData.hit, cacheData.miss, ((cacheData.hit + cacheData.miss) != 0 ? ((float)cacheData.hit / (cacheData.hit + cacheData.miss)) : 0));
    }
}