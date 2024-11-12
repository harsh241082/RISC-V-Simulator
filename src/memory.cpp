#include "../include/memory.h"
char Memory[262145] = {0};
std::string instructionMemory[4096] = {""};
int stackPointer = 1;
int StoreDataAddr = 65536;
void replaceInCache(int address);
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
                bool isDirty = cacheData.tagData[searchIndex / cacheData.blockSize] & (1 << 30);
                CacheResult << "R: Address: 0x" << std::hex << address << ", Set: 0x" << std::hex << (cacheData.associativity ? (searchIndex / cacheData.blockSize) / cacheData.associativity : 0) << ", Hit, Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
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
        bool isDirty = cacheData.tagData[searchIndex / cacheData.blockSize] & (1 << 30);
        CacheResult << "R: Address: 0x" << std::hex << address << ", Set: 0x" << std::hex << (cacheData.associativity ? (searchIndex / cacheData.blockSize) / cacheData.associativity : 0) << ", Miss, Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
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
        replaceInCache(tempAddress);
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
    if (cacheData.cacheStatus)
    {
        int tempAddress = address;
        int noOfBlockBits = std::log2(cacheData.blockSize);
        int noOfSetBits = std::log2(cacheData.noSets);
        int noOfLinesPerSet = cacheData.cacheSize / (cacheData.blockSize * cacheData.noSets);
        int searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
        int tag = tempAddress >> (noOfBlockBits + noOfSetBits);
        if (cacheData.writePolicy == "WT")
        {
            for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
            {
                if ((tag << 12) == (cacheData.tagData[searchIndex / cacheData.blockSize] << 12))
                {
                    cacheData.hit++;
                    bool isDirty = cacheData.tagData[searchIndex / cacheData.blockSize] & (1 << 30);
                    CacheResult << "W: Address: 0x" << std::hex << address << ", Set: 0x" << std::hex << (cacheData.associativity ? (searchIndex / cacheData.blockSize) / cacheData.associativity : 0) << ", Hit, Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
                    searchIndex += (tempAddress % cacheData.blockSize);
                    for (int j = 0; j < Numbytes; j++)
                    {
                        char num = static_cast<char>(value & 0xFF);
                        cacheData.cacheValues[searchIndex + j] = num;
                        value = value >> 8;
                    }
                    goto memStore;
                }
            }
            cacheData.miss++;
            bool isDirty = cacheData.tagData[searchIndex / cacheData.blockSize] & (1 << 30);
            CacheResult << "W: Address: 0x" << std::hex << address << ", Set: 0x" << std::hex << (cacheData.associativity ? (searchIndex / cacheData.blockSize) / cacheData.associativity : 0) << ", Miss, Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
            goto memStore;
        }
        else if (cacheData.writePolicy == "WB")
        {
            for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
            {
                if ((tag << 12) == (cacheData.tagData[searchIndex / cacheData.blockSize] << 12))
                {
                    cacheData.hit++;
                    bool isDirty = cacheData.tagData[searchIndex / cacheData.blockSize] & (1 << 30);
                    CacheResult << "W: Address: 0x" << std::hex << address << ", Set: 0x" << std::hex << (cacheData.associativity ? (searchIndex / cacheData.blockSize) / cacheData.associativity : 0) << ", Hit, Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
                    searchIndex += (tempAddress % cacheData.blockSize);
                    for (int j = 0; j < Numbytes; j++)
                    {
                        char num = static_cast<char>(value & 0xFF);
                        cacheData.cacheValues[searchIndex + j] = num;
                        value = value >> 8;
                    }
                    cacheData.tagData[searchIndex / cacheData.blockSize] |= 1 << 30;
                    return;
                }
            }
            cacheData.miss++;
            searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
            bool isDirty = cacheData.tagData[searchIndex / cacheData.blockSize] & (1 << 30);
            CacheResult << "W: Address: 0x" << std::hex << address << ", Set: 0x" << std::hex << (cacheData.associativity ? (searchIndex / cacheData.blockSize) / cacheData.associativity : 0) << ", Miss, Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
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
                }
            }
            replaceInCache(tempAddress);
            for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
            {
                if ((tag << 12) == (cacheData.tagData[searchIndex / cacheData.blockSize] << 12))
                {
                    searchIndex += (tempAddress % cacheData.blockSize);
                    for (int j = 0; j < Numbytes; j++)
                    {
                        char num = static_cast<char>(value & 0xFF);
                        cacheData.cacheValues[searchIndex + j] = num;
                        value = value >> 8;
                    }
                    cacheData.tagData[searchIndex / cacheData.blockSize] |= 1 << 30;
                    return;
                }
            }
        }
    }
memStore:
    address = address - 65536;
    for (int i = 0; i < Numbytes; i++)
    {
        char num = static_cast<char>(value & 0xFF);
        Memory[address + i] = num;
        value = value >> 8;
    }
}

void storeMemoryForData(int address, int Numbytes, __int64 value)
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
            storeMemoryForData(StoreDataAddr, 8, data);
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
            storeMemoryForData(StoreDataAddr, 2, data);
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
            storeMemoryForData(StoreDataAddr, 4, data);
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
            storeMemoryForData(StoreDataAddr, 1, data);
        }
    }
}

void replaceInCache(int address)
{
    int tempAddress = address;
    int noOfBlockBits = std::log2(cacheData.blockSize);
    int noOfSetBits = std::log2(cacheData.noSets);
    int noOfLinesPerSet = cacheData.cacheSize / (cacheData.blockSize * cacheData.noSets);
    int searchIndex = ((tempAddress >> noOfBlockBits) % cacheData.noSets) * noOfLinesPerSet * cacheData.blockSize;
    int tag = tempAddress >> (noOfBlockBits + noOfSetBits);
    if (cacheData.writePolicy == "WB")
    {
        for (int i = 0; i < noOfLinesPerSet; i++, searchIndex += cacheData.blockSize)
        {
            if ((tag << 12) == (cacheData.tagData[searchIndex / cacheData.blockSize] << 12))
            {
                if (cacheData.tagData[searchIndex / cacheData.blockSize] >> 30 == 3)
                {
                    tempAddress -= (tempAddress % cacheData.blockSize);
                    tempAddress = tempAddress - 65536;
                    for (int j = 0; j < cacheData.blockSize; j++)
                    {
                        Memory[tempAddress] = cacheData.cacheValues[searchIndex];
                        searchIndex++;
                        tempAddress++;
                    }
                    break;
                }
            }
        }
    }
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
        int minIndex = 0;
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
    else
    {
        std::cout << "Invalid replacement policy" << std::endl;
        exit(1);
    }
}

void DumpCache(std::string filename)
{
    std::ofstream output;
    output.open(filename);
    if (!output.is_open())
    {
        std::cout << "file not found" << std::endl;
        return;
    }
    int noOfLines = cacheData.cacheSize / cacheData.blockSize;
    for (int i = 0; i < noOfLines; i++)
    {
        bool isValid = cacheData.tagData[i] & (1 << 31);
        if (!isValid)
        {
            continue;
        }
        int setNo = cacheData.associativity ? (i + 1) / cacheData.associativity : 0;
        int tag = cacheData.tagData[i] & 0xFFFFF;
        bool isDirty = cacheData.tagData[i] & (1 << 30);
        output << "Set: 0x" << std::hex << setNo << ", Tag: 0x" << std::hex << tag << ", " << (isDirty ? "Dirty" : "Clean") << std::endl;
    }
    output.close();
}