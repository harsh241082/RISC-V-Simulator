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
        memStr = "0x" + memStr;
        cout << "Memory[" << addrStr << "] = " << memStr << endl;
        addr++;
    }
    cout << endl;
}

void showCallStack()
{
    int sp = 16383;
    cout << "Call Stack:" << endl;
    if (stackPointer == 262145)
    {
        cout << "main:" << ProgramCounter << endl;
        return;
    }
    if (Lines[Memory[sp]].label != "main")
    {
        cout << "main:" << Memory[sp] << endl;
        sp--;
    }
    while (sp > stackPointer)
    {
        int lineNo = Memory[sp];
        string label = Lines[lineNo].label;
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
        data = data | Memory[address];
        address++;
    }
}

void storeMemory(int address, int Numbytes, int value)
{
    address = address - 65536;
    for (int i = Numbytes - 1; i >= 0; i--)
    {
        Memory[address + i] = value & 0xFF;
        value = value >> 8;
    }
}
