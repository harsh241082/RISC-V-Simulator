#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <cstdint>

enum class InstructionFormat
{
    R_TYPE,
    I_TYPE,
    S_TYPE,
    B_TYPE,
    U_TYPE,
    J_TYPE,
    UNKNOWN
};

struct InstructionInfo
{
    InstructionFormat format;
    int opcode;
    int funct3;
    int funct7;
    InstructionInfo() : format(InstructionFormat::UNKNOWN), opcode(0), funct3(0), funct7(0) {}
    InstructionInfo(InstructionFormat format, int opcode, int func3, int func7) : format(format), opcode(opcode), funct3(func3), funct7(func7) {}
};

struct Instruction
{
    InstructionInfo instructionInfo;
    std::string mnemonic;
    int rd;
    int rs1;
    int rs2;
    std::string label;
    int immediate;
    std::string error;
    Instruction() : instructionInfo(InstructionInfo()), mnemonic(""), rd(0), rs1(0), rs2(0), label(""), immediate(0), error("") {}
};

// functions to convert all types of instructions
std::string R_type_to_hex(const Instruction R);
std::string I_type_to_hex(const Instruction I);
std::string S_type_to_hex(const Instruction S);
std::string B_type_to_hex(const Instruction B);
std::string U_type_to_hex(const Instruction U);
std::string J_type_to_hex(const Instruction J);

#endif