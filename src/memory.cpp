#include "../include/memory.h"
using namespace std;
char Memory[262145] = {0};
string instructionMemory[4096] = {""};
int stackPointer = 262145;
void ShowMemory(string address, int count)
{
    int addr = strToInt(address);
    addr = addr - 65536;
    for (int i = 0; i < count; i++)
    {
        stringstream ss, ss1;
        string addrStr;
        ss << hex << addr + 65536;
        addrStr = ss.str();
        addrStr = "0x" + addrStr;
        int mem = Memory[addr];
        ss1 << hex << mem;
        string memStr = ss1.str();
        if (memStr.length() > 2)
            memStr = memStr.substr(memStr.length() - 2, 2);
        memStr = "0x" + memStr;
        cout << "Memory[" << addrStr << "] = " << memStr << endl;
        addr++;
    }
    cout << endl;
}

void showCallStack(int numLines)
{
    int sp = 16383;
    if (ProgramCounter >= numLines)
    {
        cout << "Empty call Stack: Execution completed" << endl
             << endl;
        return;
    }
    cout << "Call Stack:" << endl;
    cout << stackPointer << endl;
    if (stackPointer == 262145)
    {
        cout << "main:" << ProgramCounter << endl;
        return;
    }
    if (Lines[Memory[sp]].label != "main")
    {
        char lineNo = Memory[sp];
        cout << "main:" << static_cast<int>(lineNo) << endl;
        sp--;
    }
    while (sp > stackPointer)
    {
        int lineNo = static_cast<int>(Memory[sp]);
        string label;
        auto it = find_if(labelData.begin(), labelData.end(), [lineNo](const pair<string, int> &p)
                          { return p.second == lineNo; });
        label = it->first;
        cout << label << ":" << lineNo << endl;
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
