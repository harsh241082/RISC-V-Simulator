#include "../include/memory.h"
using namespace std;
int Memory[16384] = {0};
string instructionMemory[4096] = {""};

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