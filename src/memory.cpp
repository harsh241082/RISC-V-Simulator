#include "../include/memory.h"
char Memory[262145] = {0};
std::string instructionMemory[4096] = {""};
int stackPointer = 262145;
void ShowMemory(std::string address, int count)
{
    int addr = strToInt(address);
    addr = addr - 65536;
    for (int i = 0; i < count; i++)
    {
        std::stringstream ss, ss1;
        std::string addrStr;
        ss << std::hex << addr + 65536;
        addrStr = ss.str();
        addrStr = "0x" + addrStr;
        int mem = Memory[addr];
        ss1 << std::hex << mem;
        std::string memStr = ss1.str();
        if (memStr.length() > 2)
            memStr = memStr.substr(memStr.length() - 2, 2);
        memStr = "0x" + memStr;
        std::cout << "Memory[" << addrStr << "] = " << memStr << std::endl;
        addr++;
    }
    std::cout << std::endl;
}

void showCallStack(int numLines)
{
    int sp = 16383;
    if (ProgramCounter >= numLines)
    {
        std::cout << "Empty call Stack: Execution completed" << std::endl
                  << std::endl;
        return;
    }
    std::cout << "Call Stack:" << std::endl;
    std::cout << stackPointer << std::endl;
    if (stackPointer == 262145)
    {
        std::cout << "main:" << ProgramCounter << std::endl;
        return;
    }
    if (Lines[Memory[sp]].label != "main")
    {
        char lineNo = Memory[sp];
        std::cout << "main:" << static_cast<int>(lineNo) << std::endl;
        sp--;
    }
    while (sp > stackPointer)
    {
        int lineNo = static_cast<int>(Memory[sp]);
        std::string label;
        auto it = find_if(labelData.begin(), labelData.end(), [lineNo](const std::pair<std::string, int> &p)
                          { return p.second == lineNo; });
        label = it->first;
        std::cout << label << ":" << lineNo << std::endl;
        sp--;
    }
}

int fechMemory(int address, int Numbytes)
{
    address = address - 65536;
    int data = 0;
    for (int i = 0; i < Numbytes; i++)
    {
        data = data << 8;
        int num = static_cast<int>(Memory[address]);
        data = data | num;
        address++;
    }
    return data;
}

void storeMemory(int address, int Numbytes, int value)
{
    address = address - 65536;
    for (int i = Numbytes - 1; i >= 0; i--)
    {
        char num = static_cast<char>(value & 0xFF);
        Memory[address + i] = num;
        value = value >> 8;
    }
}
