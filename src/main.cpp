#include "../include/encoder.h"
#include "../include/parser.h"
#include "../include/risc-v.h"
#include "../include/data.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string line;
    ifstream input("input.s");
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
        ProgramCounter++;
        comment_ctr = 0;
    }
    input.close();

    ofstream output("output.hex");

    int linectr = ProgramCounter;
    string hexStr;
    for (ProgramCounter = 0; ProgramCounter < linectr; ProgramCounter++)
    {
        hexStr = InstructionToHex(Lines[ProgramCounter]);
        int comment_line = EmptyLines[ProgramCounter];
        if (hexStr == "error!!")
        {
            cout << "error at line " << ProgramCounter + 1 + EmptyLines[ProgramCounter] << ": " << Lines[ProgramCounter].error << endl;
            output.close();
            remove("output.hex");
            return 0;
        }
        output << hexStr << endl;
    }
    output.close();
    return 0;
}