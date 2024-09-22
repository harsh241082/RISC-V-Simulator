#include "../include/parser.h"
#include "../include/encoder.h"
#include "../include/risc-v.h"
#include "../include/data.h"

using namespace std;

string InstructionToHex(Instruction instruct)
{
    string hexCode;
    if (instruct.error != "")
        return "error!!";
    switch (instruct.instructionInfo.format)
    {
    case InstructionFormat::R_TYPE:
        hexCode = R_type_to_hex(instruct);
        break;
    case InstructionFormat::I_TYPE:
        if (instruct.mnemonic == "slli" || instruct.mnemonic == "srli" || instruct.mnemonic == "srai")
        {
            int i = 0b000000111111;
            instruct.immediate &= i;
            if (instruct.mnemonic == "srai")
                instruct.immediate += 0b010000000000;
        }
        hexCode = I_type_to_hex(instruct);
        break;
    case InstructionFormat::S_TYPE:
        hexCode = S_type_to_hex(instruct);
        break;
    case InstructionFormat::U_TYPE:
        hexCode = U_type_to_hex(instruct);
        break;
    case InstructionFormat::J_TYPE:
        auto itr = labelData.find(instruct.label);
        if (itr == labelData.end())
        {
            instruct.error = "no label found as " + instruct.label;
            return "error!!";
        }
        int label;
        label = itr->second;
        instruct.immediate = 4 * (label - ProgramCounter);
        hexCode = J_type_to_hex(instruct);
        break;
    }
    if (instruct.instructionInfo.format == InstructionFormat::B_TYPE)
    {
        auto itr = labelData.find(instruct.label);
        if (itr == labelData.end())
        {
            instruct.error = "no label found as " + instruct.label;
            return "error!!";
        }
        int label;
        label = itr->second;
        instruct.immediate = 4 * (label - ProgramCounter);
        hexCode = B_type_to_hex(instruct);
    }
    else if (instruct.instructionInfo.format == InstructionFormat::UNKNOWN)
    {
        instruct.error = "Unkown instruction";
        return "error!!";
    }

    return hexCode;
}