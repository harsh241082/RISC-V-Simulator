#include "../include/encoder.h"
#include "../include/parser.h"
#include "../include/risc-v.h"
#include "../include/data.h"
#include "../include/memory.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string fileName;
    ifstream input(fileName);
    while (true)
    {
        string command;
        cin >> command;
        if (command == "load")
        {
            cin >> fileName;
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
    input.close();
    while (true)
    {
        
    }
    
    return 0;
}