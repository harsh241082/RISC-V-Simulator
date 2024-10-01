#ifndef MAIN_CPP
#define MAIN_CPP

#include "../include/parser.h"
#include "../include/executor.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string fileName;
    ifstream input;
    while (true)
    {
        string command;
        cin >> command;
        if (command == "load")
        {
            cin >> fileName;
            input.open(fileName);
            if (!input.is_open())
            {
                cout << "file not found" << endl;
                cout << "enter a valid file name" << endl;
                continue;
            }
            break;
        }
        else
        {
            cout << "load a file before exicuting any command" << endl;
        }
    }

    string line;
    ProgramCounter = 0;
    EmptyLines[0] = 0;
    int comment_ctr = 0;
    while (getline(input, line))
    {
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
    string command;
    cin >> command;
    while (command != "exit")
    {
        if (command == "run")
        {
            if (ProgramCounter >= numLines)
            {
                cout << "Nothing to run\n"
                     << endl;
                cin >> command;
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
            string address;
            int count;
            cin >> address >> count;
            ShowMemory(address, count);
        }
        else if (command == "step")
        {
            if (ProgramCounter >= numLines)
            {
                cout << "Nothing to step\n"
                     << endl;
                cin >> command;
                continue;
            }
            executeInstruction();
            cout << endl;
        }
        else if (command == "show-stack")
        {
            showCallStack();
        }
        else if (command == "break")
        {
            int breakPoint;
            cin >> breakPoint;
            if (breakPoint > numLines)
            {
                cout << "invalid breakpoint" << endl;
                cin >> command;
                continue;
            }
            cout << "breakpoint set at line " << breakPoint << endl
                 << endl;
            breakPoints[breakPoint - 1] = 1;
        }
        else if (command == "del")
        {
            int breakPoint;
            string isBreak;
            cin >> isBreak >> breakPoint;
            if (breakPoint > numLines)
            {
                cout << "invalid breakpoint" << endl;
                cin >> command;
                continue;
            }
            if (isBreak != "break")
            {
                cout << "invalid command" << endl;
                cin >> command;
                continue;
            }
            if (breakPoints[breakPoint - 1] == 0)
            {
                cout << "breakpoint not found" << endl;
                cin >> command;
                continue;
            }
            breakPoints[breakPoint - 1] = 0;
        }
        else
        {
            cout << "invalid command" << endl;
        }
        cin >> command;
    }

    return 0;
}
#endif