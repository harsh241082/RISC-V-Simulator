#include "../include/memory.h"
char Memory[262145] = {0};
std::string instructionMemory[4096] = {""};
int stackPointer = 1;
int StoreDataAddr = 65536;
void initCache()
{
    if (cacheData.cacheStatus)
    {
        cacheData.cacheValues = new char[cacheData.cacheSize];
        cacheData.tagData = new int[cacheData.cacheSize / cacheData.blockSize]{};
        cacheData.hit = 0;
        cacheData.miss = 0;
        cacheData.fifoQueue = new std::queue<int>[cacheData.noSets];
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
    int tempAddress = address;
    if (cacheData.cacheStatus)
    {
        int noOfBlockBits = std::log2(cacheData.blockSize);
        int noOfSetBits = std::log2(cacheData.noSets);
        int noOfLinesPerSet = cacheData.cacheSize / (cacheData.blockSize * cacheData.noSets);
        int searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
        int tag = tempAddress >> (noOfBlockBits + noOfSetBits);
        // searching for the data in the cache
        for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
        {
            if ((tag << 12) == (cacheData.tagData[searchIndex / cacheData.blockSize] << 12))
            {
                // cacheData.hit case
                cacheData.hit++;
                tag |= 1 << 31;
                int pcBits = ProgramCounter << 24;
                pcBits = pcBits >> 2;
                tag |= pcBits;
                cacheData.tagData[searchIndex / cacheData.blockSize] = tag;
                searchIndex += Numbytes - 1 + (tempAddress % cacheData.blockSize);
                for (int j = Numbytes - 1; j >= 0; j--)
                {
                    data = data << 8;
                    int num = static_cast<int>(cacheData.cacheValues[searchIndex]);
                    num = num & 0xFF;
                    data |= num;
                    searchIndex--;
                }
                return data;
            }
        }
        // cacheData.miss case
        cacheData.miss++;
        searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
        for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
        {
            if ((cacheData.tagData[searchIndex / cacheData.blockSize] >> 31) == 0)
            {
                int setNo = (tempAddress >> noOfBlockBits) % cacheData.noSets;
                cacheData.fifoQueue[setNo].push(searchIndex / cacheData.blockSize);
                tag |= 1 << 31;
                int pcBits = ProgramCounter << 24;
                pcBits = pcBits >> 2;
                tag |= pcBits;
                tempAddress -= (tempAddress % cacheData.blockSize);
                tempAddress = tempAddress - 65536;
                for (int j = 0; j < cacheData.blockSize; j++)
                {
                    char num = Memory[tempAddress];
                    cacheData.cacheValues[searchIndex] = num;
                    searchIndex++;
                    tempAddress++;
                }
                searchIndex -= cacheData.blockSize;
                cacheData.tagData[searchIndex / cacheData.blockSize] = tag;
                goto end;
            }
        }
        tempAddress = address;
        searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
        if (cacheData.replacementPolicy == "RANDOM")
        {
            srand(time(0));
            int lineNo = rand() % noOfLinesPerSet;
            searchIndex += lineNo * cacheData.blockSize;
            tempAddress -= (tempAddress % cacheData.blockSize);
            tempAddress = tempAddress - 65536;
            for (int j = 0; j < cacheData.blockSize; j++)
            {
                char num = Memory[tempAddress];
                cacheData.cacheValues[searchIndex] = num;
                searchIndex++;
                tempAddress++;
            }
            searchIndex -= cacheData.blockSize;
            tag |= 1 << 31;
            int pcBits = ProgramCounter << 24;
            pcBits = pcBits >> 2;
            tag |= pcBits;
            cacheData.tagData[searchIndex / cacheData.blockSize] = tag;
        }
        else if (cacheData.replacementPolicy == "LRU")
        {
            int min;
            int minIndex=0;
            for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
            {
                if (i == 0)
                {
                    min = cacheData.tagData[searchIndex / cacheData.blockSize] & 0x7F800000;
                }
                if ((cacheData.tagData[searchIndex / cacheData.blockSize] & 0x7F800000) < min)
                {
                    min = cacheData.tagData[searchIndex / cacheData.blockSize] & 0x7F800000;
                    minIndex = i;
                }
            }
            searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
            searchIndex += minIndex * cacheData.blockSize;
            tempAddress -= (tempAddress % cacheData.blockSize);
            tempAddress = tempAddress - 65536;
            for (int j = 0; j < cacheData.blockSize; j++)
            {
                char num = Memory[tempAddress];
                cacheData.cacheValues[searchIndex] = num;
                searchIndex++;
                tempAddress++;
            }
            searchIndex -= cacheData.blockSize;
            tag |= 1 << 31;
            int pcBits = ProgramCounter << 24;
            pcBits = pcBits >> 2;
            tag |= pcBits;
            cacheData.tagData[searchIndex / cacheData.blockSize] = tag;
        }
        else if (cacheData.replacementPolicy == "FIFO")
        {
            int setNo = (tempAddress >> noOfBlockBits) % cacheData.noSets;
            int lineNo = cacheData.fifoQueue[setNo].front();
            cacheData.fifoQueue[setNo].pop();
            cacheData.fifoQueue[setNo].push(lineNo);
            searchIndex += lineNo * cacheData.blockSize;
            tempAddress -= (tempAddress % cacheData.blockSize);
            tempAddress = tempAddress - 65536;
            for (int j = 0; j < cacheData.blockSize; j++)
            {
                char num = Memory[tempAddress];
                cacheData.cacheValues[searchIndex] = num;
                searchIndex++;
                tempAddress++;
            }
            searchIndex -= cacheData.blockSize;
            tag |= 1 << 31;
            int pcBits = ProgramCounter << 24;
            pcBits = pcBits >> 2;
            tag |= pcBits;
            cacheData.tagData[searchIndex / cacheData.blockSize] = tag;
        }
    }
    // featching directly from main mem
    end:
    address = address + Numbytes - 1;
    address = address - 65536;
    for (int i = Numbytes - 1; i >= 0; i--)
    {
        data = data << 8;
        int num = static_cast<int>(Memory[address]);
        num = num & 0xFF;
        data = data | num;
        address--;
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