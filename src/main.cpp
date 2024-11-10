#ifndef MAIN_CPP
#define MAIN_CPP
#include "../include/data.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include <iostream>
#include <random>
#include <fstream>

int main()
{
    std::string fileName;
    std::ifstream input;
    while (true)
    {
        std::string command;
        std::cin >> command;
        if (command == "load")
        {
            std::cin >> fileName;
            input.open(fileName);
            if (!input.is_open())
            {
                std::cout << "file not found" << std::endl;
                std::cout << "enter a valid file name" << std::endl;
                continue;
            }
            break;
        }
        else if (command == "cache_sim")
        {
            std::string cacheQuary;
            std::cin >> cacheQuary;
            if (cacheQuary == "enable")
            {
                std::cin >> fileName;
                input.open(fileName);
                if (!input.is_open())
                {
                    std::cout << "file not found" << std::endl;
                    std::cout << "enter a valid file name" << std::endl;
                    continue;
                }
                cacheData.cacheStatus = true;
                std::string data;
                getline(input, data);
                cacheData.cacheSize = strToInt(data);
                getline(input, data);
                cacheData.blockSize = strToInt(data);
                getline(input, data);
                cacheData.associativity = strToInt(data);
                if (cacheData.associativity == 0)
                {
                    cacheData.noSets = 1;
                }
                else
                {
                    cacheData.noSets = cacheData.cacheSize / (cacheData.blockSize * cacheData.associativity);
                }
                getline(input, data);
                cacheData.replacementPolicy = data;
                getline(input, data);
                cacheData.writeBackPolicy = data;
                continue;
            }
            else if (cacheQuary == "disable")
            {
                cacheData.cacheStatus = false;
            }
        }
        else
        {
            std::cout << "load a file before exicuting any command" << std::endl;
        }
    }
    std::string line;
    ProgramCounter = 0;
    EmptyLines[0] = 0;
    int comment_ctr = 0;
    while (getline(input, line))
    {
        if (line.find(".text") != std::string::npos)
            continue;
        else if (line.find(".data") != std::string::npos)
        {
            std::string isText;
            while (getline(input, line))
            {
                std::vector<std::string> StoreData = split(line);
                isText = StoreData[0];
                if (StoreData.size() == 0)
                {
                    continue;
                }
                if (isText == ".text")
                {
                    break;
                }
                storeData(StoreData);
            }
            if (isText == ".text")
            {
                continue;
            }
        }
        Lines[ProgramCounter] = parseInstruction(line);
        if (comment_ctr == 0)
        {
            if (ProgramCounter != 0)
            {
                EmptyLines[ProgramCounter] = EmptyLines[ProgramCounter - 1];
                comment_ctr++;
            }
        }
        if (Lines[ProgramCounter].error == "empty line")
        {
            EmptyLines[ProgramCounter] = EmptyLines[ProgramCounter] + 1;
            continue;
        }
        instructionMemory[ProgramCounter] = line;
        ProgramCounter++;
        comment_ctr = 0;
    }
    int numLines = ProgramCounter;
    ProgramCounter = 0;
    input.close();
    InitCPU(cpu);
    std::string command;
    std::cin >> command;
    initCache();
    while (command != "exit")
    {
        if (command == "cache_sim")
        {
            std::string cacheQuary;
            std::cin >> cacheQuary;
            if (cacheQuary == "status")
            {
                if (cacheData.cacheStatus == false)
                {
                    std::cout << "Cache is disabled" << std::endl;
                    continue;
                }
                std::cout << "Cache is enabled" << std::endl;
                std::cout << "Cache Status: " << cacheData.cacheStatus << std::endl;
                std::cout << "Cache Size: " << cacheData.cacheSize << std::endl;
                std::cout << "Block Size: " << cacheData.blockSize << std::endl;
                std::cout << "Associativity: " << cacheData.associativity << std::endl;
                std::cout << "Replacement Policy: " << cacheData.replacementPolicy << std::endl;
                std::cout << "Write Back Policy: " << cacheData.writeBackPolicy << std::endl;
            }
        }
        else if (command == "help")
        {
            std::cout << "run - to run the program\n"
                      << "regs - to show the registers\n"
                      << "mem - to show the memory\n"
                      << "step - to execute the next instruction\n"
                      << "show-stack - to show the call stack\n"
                      << "break - to set a breakpoint\n"
                      << "del break - to delete a breakpoint\n"
                      << "exit - to exit the simulator\n"
                      << "cache_sim status - to check the status of cache\n"
                      << std::endl;
        }
        else if (command == "run")
        {
            if (ProgramCounter >= numLines)
            {
                std::cout << "Nothing to run\n"
                          << std::endl;
                std::cin >> command;
                continue;
            }
            RunTillBreakPoint(numLines);
        }
        else if (command == "regs")
        {
            std::cout << "Registers:" << std::endl;
            ShowRegisters(cpu);
        }
        else if (command == "mem")
        {
            std::string address;
            int count;
            std::cin >> address >> count;
            ShowMemory(address, count);
        }
        else if (command == "step")
        {
            if (ProgramCounter >= numLines)
            {
                std::cout << "Nothing to step\n"
                          << std::endl;
                std::cin >> command;
                continue;
            }
            executeInstruction();
            std::cout << std::endl;
        }
        else if (command == "show-stack")
        {
            showCallStack(numLines);
        }
        else if (command == "break")
        {
            int breakPoint;
            std::cin >> breakPoint;
            if (breakPoint > numLines)
            {
                std::cout << "invalid breakpoint\n"
                          << std::endl;
                std::cin >> command;
                continue;
            }
            std::cout << "breakpoint set at line " << breakPoint << std::endl
                      << std::endl;
            breakPoints[breakPoint - 1] = 1;
        }
        else if (command == "del")
        {
            int breakPoint;
            std::string isBreak;
            std::cin >> isBreak >> breakPoint;
            if (isBreak != "break")
            {
                std::cout << "invalid command\n"
                          << std::endl;
                std::cin >> command;
                continue;
            }
            if (breakPoint > numLines)
            {
                std::cout << "invalid breakpoint\n"
                          << std::endl;
                std::cin >> command;
                continue;
            }
            if (breakPoints[breakPoint - 1] == 0)
            {
                std::cout << "breakpoint not found\n"
                          << std::endl;
                std::cin >> command;
                continue;
            }
            breakPoints[breakPoint - 1] = 0;
            std::cout << "breakpoint deleted at line " << breakPoint << std::endl
                      << std::endl;
        }
        else
        {
            std::cout << "invalid command\n"
                      << std::endl;
        }
        std::cin >> command;
    }
    std::cout << "Exited the Simulator" << std::endl;
    return 0;
}
#endif