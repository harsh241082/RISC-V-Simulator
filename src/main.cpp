#ifndef MAIN_CPP
#define MAIN_CPP

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
    std::cout << "Loaded the file succesfully" << std::endl
              << std::endl;
    ProgramCounter = 0;
    input.close();
    InitCPU(cpu);
    std::string command;
    std::cin >> command;
    while (command != "exit")
    {
        if (command == "exit")
        {
            std::cout << "Exited the Simulator" << std::endl;
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