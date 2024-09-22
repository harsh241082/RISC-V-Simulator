#include "../include/parser.h"
#include "../include/utilis.h"
#include "../include/risc-v.h"
#include "../include/instruction.h"
using namespace std;

Instruction parseInstruction(const std::string &line)
{
    vector<string> tokens = tokenize(line);
    Instruction instrction;

    if (tokens.size() == 0)
    {
        instrction.error = "empty line";
        return instrction;
    }

    auto instrectInfo = instructionData.find(tokens[0]);
    if (instrectInfo == instructionData.end())
    {
        instrction.error = "No instruction as " + tokens[0];
        return instrction;
    }

    instrction.mnemonic = tokens[0];
    instrction.instructionInfo = instrectInfo->second;

    int size = tokens.size();
    if (instrction.instructionInfo.format == InstructionFormat::B_TYPE)
        size--;
    // convers alias names to rigester names
    for (int i = 1; i < size; i++)
    {
        string token = tokens[i];
        string newToken = "";
        if (token[0] != 'x')
        {
            if (token[0] == 'r' || token[0] == 's' || token[0] == 'g' || token[0] == 't' || token[0] == 'a' || token[0] == 'z')
            {
                auto reg = registerData.find(token);
                if (reg == registerData.end())
                {
                    instrction.error = "No register as " + token;
                    return instrction;
                }
                newToken = reg->second;
                tokens[i] = newToken;
            }
        }
    }

    // adds all the values acording to the respective format
    switch (instrction.instructionInfo.format)
    {
    case InstructionFormat::B_TYPE:
        try
        {
            instrction.rs1 = rigToInt(tokens[1]);
            instrction.rs2 = rigToInt(tokens[2]);
        }
        catch (const std::exception &e)
        {
            instrction.error = "invalid registers";
        }
        instrction.label = tokens[3];
        if (instrction.rs1 > 32 || instrction.rs2 > 32)
            instrction.error = "invalid registers";
        break;
    case InstructionFormat::R_TYPE:
        try
        {
            instrction.rd = rigToInt(tokens[1]);
            instrction.rs1 = rigToInt(tokens[2]);
            instrction.rs2 = rigToInt(tokens[3]);
        }
        catch (const std::exception &e)
        {
            instrction.error = "invalid registers";
        }
        if (instrction.rs1 > 32 || instrction.rs2 > 32 || instrction.rd > 32)
            instrction.error = "invalid registers";
        break;
    case InstructionFormat::I_TYPE:
        if (instrction.mnemonic[0] == 'e')
        {
            instrction.rd = 0;
            instrction.rs1 = 0;
            if (instrction.mnemonic == "ecall")
                instrction.immediate = 0;
            else
                instrction.immediate = 1;
            break;
        }
        try
        {
            instrction.rd = rigToInt(tokens[1]);
            instrction.rs1 = rigToInt(tokens[2]);
            instrction.immediate = strToInt(tokens[3]);
        }
        catch (const std::exception &e)
        {
            instrction.error = "invalid registers or immediate value";
        }
        if (instrction.rs1 > 32 || instrction.rd > 32)
            instrction.error = "invalid registers";
        break;
    case InstructionFormat::S_TYPE:
        try
        {
            instrction.rs1 = rigToInt(tokens[2]);
            instrction.rs2 = rigToInt(tokens[1]);
            instrction.immediate = strToInt(tokens[3]);
        }
        catch (const std::exception &e)
        {
            instrction.error = "invalid registers or immediate value";
        }
        if (instrction.rs1 > 32 || instrction.rs2 > 32)
            instrction.error = "invalid registers";
        break;
    case InstructionFormat::J_TYPE:
        instrction.label = tokens[2];
        try
        {
            instrction.rd = rigToInt(tokens[1]);
        }
        catch (const std::exception &e)
        {
            instrction.error = "invalid register";
        }
        if (instrction.rd > 32)
            instrction.error = "invalid register";
        break;
    case InstructionFormat::U_TYPE:
        try
        {
            instrction.rd = rigToInt(tokens[1]);
            instrction.immediate = strToInt(tokens[2]);
        }
        catch (const std::exception &e)
        {
            instrction.error = instrction.error = "invalid registers or immediate value";
        }
        if (instrction.rd > 32)
            instrction.error = "invalid register";
        break;
    default:
        break;
    }
    return instrction;
}