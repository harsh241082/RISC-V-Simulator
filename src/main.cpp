#include "../include/encoder.h"
#include "../include/parser.h"
#include "../include/risc-v.h"
#include "../include/data.h"
#include "../include/memory.h"
#include "../include/cpu.h"
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
    string command;
    cin >> command;
    while (command != "exit")
    {
        cin >> command;
        if (command == "run")
        {
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
        }
        else if (command == "show-stack")
        {
        }
        else if (command == "break")
        {
            int breakPoint;
            cin >> breakPoint;
            cout << "breakpoint set at line " << breakPoint << endl;
            breakPoints[breakPoint] = 1;
        }
        else if (command == "del")
        {
            int breakPoint;
            string isBreak;
            cin >> isBreak >> breakPoint;
            if (isBreak != "break")
            {
                cout << "invalid command" << endl;
                continue;
            }
            if (breakPoints[breakPoint] == 0)
            {
                cout << "breakpoint not found" << endl;
                continue;
            }
            breakPoints[breakPoint] = 0;
        }
    }

    return 0;
}