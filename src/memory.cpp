#include "../include/memory.h"
char Memory[262145] = {0};
std::string instructionMemory[4096] = {""};
int stackPointer = 1;
int StoreDataAddr = 65536;
void initCache()
{
    if (cacheData.cacheStatus)
    {
        cache = new char[cacheData.cacheSize];
        tagData = new int[cacheData.cacheSize / cacheData.blockSize]{};
    }
}

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
    int sp = 1;
    int address = 0x4fff8;
    if (ProgramCounter >= numLines)
    {
        std::cout << "Empty call Stack: Execution completed" << std::endl;
        return;
    }
    std::cout << "Call Stack:" << std::endl;
    if (stackPointer == 1)
    {
        std::cout << "main:" << ProgramCounter << std::endl;
        std::cout << std::endl;
        return;
    }
    int lineno = fechMemory(address, 8) / 4 - 1;
    std::cout << "main:" << lineno << std::endl;
    sp++;
    while (sp < stackPointer)
    {
        std::string label;
        label = Lines[lineno].label;
        address -= 8;
        lineno = fechMemory(address, 8);
        std::cout << label << ":" << lineno + 1 << std::endl;
        sp++;
    }
    std::string label;
    label = Lines[lineno].label;
    address -= 8;
    lineno = fechMemory(address, 8);
    std::cout << label << ":" << ProgramCounter << std::endl;
    std::cout << std::endl;
}

__int64 fechMemory(int address, int Numbytes)
{

    __int64 data = 0;
    address = address + Numbytes - 1;
    for (int i = Numbytes - 1; i >= 0; i--)
    {
        if (cacheData.cacheStatus)
        {
            int noOfBlockBits = std::log2(cacheData.blockSize);
            int noOfSetBits = std::log2(cacheData.noSets);
            int noOfLinesPerSet = cacheData.cacheSize / (cacheData.blockSize * cacheData.noSets);
            int searchIndex = ((address >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet;
            int tag = address >> (noOfBlockBits + noOfSetBits);
            // searching for the data in the cache
            for (int i = 0; i < noOfLinesPerSet; i++)
            {
                if (tag == tagData[searchIndex + i])
                {
                    // hit case
                    continue;
                }
            }
            // miss case
            // featching directly from main mem
        }
        address = address - 65536;
        data = data << 8;
        int num = static_cast<int>(Memory[address]);
        num = num & 0xFF;
        data = data | num;
        address--;
        address = address + 65536;
    }
    return data;
}

void storeMemory(int address, int Numbytes, __int64 value)
{
    address = address - 65536;
    for (int i = 0; i < Numbytes; i++)
    {
        char num = static_cast<char>(value & 0xFF);
        Memory[address + i] = num;
        value = value >> 8;
    }
}

void storeData(std::vector<std::string> StoreData)
{
    if (StoreData[0] == ".dword")
    {
        __int64 data;
        for (int i = 1; i < StoreData.size(); i++, StoreDataAddr += 8)
        {
            if (i == StoreData.size() - 1)
            {
                data = strToInt(StoreData[i].substr(0, StoreData[i].length()));
            }
            else
            {

                data = strToInt(StoreData[i].substr(0, StoreData[i].length() - 1));
            }
            storeMemory(StoreDataAddr, 8, data);
        }
    }
    else if (StoreData[0] == ".half")
    {
        for (int i = 1; i < StoreData.size(); i++, StoreDataAddr += 2)
        {
            __int64 data;
            if (i == StoreData.size() - 1)
            {
                data = strToInt(StoreData[i].substr(0, StoreData[i].length()));
            }
            else
            {

                data = strToInt(StoreData[i].substr(0, StoreData[i].length() - 1));
            }
            storeMemory(StoreDataAddr, 2, data);
        }
    }
    else if (StoreData[0] == ".word")
    {
        for (int i = 1; i < StoreData.size(); i++, StoreDataAddr += 4)
        {
            __int64 data;
            if (i == StoreData.size() - 1)
            {
                data = strToInt(StoreData[i].substr(0, StoreData[i].length()));
            }
            else
            {

                data = strToInt(StoreData[i].substr(0, StoreData[i].length() - 1));
            }
            storeMemory(StoreDataAddr, 4, data);
        }
    }
    else if (StoreData[0] == ".byte")
    {
        for (int i = 1; i < StoreData.size(); i++, StoreDataAddr += 1)
        {
            __int64 data;
            if (i == StoreData.size() - 1)
            {
                data = strToInt(StoreData[i].substr(0, StoreData[i].length()));
            }
            else
            {

                data = strToInt(StoreData[i].substr(0, StoreData[i].length() - 1));
            }
            storeMemory(StoreDataAddr, 1, data);
        }
    }
}