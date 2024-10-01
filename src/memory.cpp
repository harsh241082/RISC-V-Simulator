#include "../include/memory.h"
using namespace std;
int Memory[16384] = {0};
string instructionMemory[4096] = {""};
int stackPointer = 16384;
void ShowMemory(string address, int count)
{
    int addr = strToInt(address);
    addr = addr - 65536;
    for (int i = 0; i < count; i++)
    {
        stringstream ss;
        string addrStr;
        ss << hex << addr + 65536;
        addrStr = ss.str();
        ss << hex << Memory[addr];
        string memStr = ss.str();
        cout << "Memory[" << addrStr << "] = " << memStr << endl;
        addr++;
    }
}

void showCallStack()
{
    int sp = 16383;
    cout << "Call Stack:" << endl;
    if (stackPointer == 16384)
    {
        cout << "main:0" << endl;
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

int fechMemory(int address, int Numbytes, int byteOffset)
{
    if (byteOffset == 0)
    {
        int data = Memory[address];
    }
}

void storeMemory(int address, int Numbytes, int byteOffset)
{
}