#include "../include/instruction.h"
#include <sstream>

using namespace std;

string R_type_to_hex(const Instruction R)
{
    unsigned int decimal_value = 0;
    decimal_value += (R.instructionInfo.funct7 << 25);
    decimal_value += (R.rs2 << 20);
    decimal_value += (R.rs1 << 15);
    decimal_value += (R.instructionInfo.funct3 << 12);
    decimal_value += (R.rd << 7);
    decimal_value += (R.instructionInfo.opcode);
    string str;
    stringstream ss;
    ss << std::hex << decimal_value;
    str = ss.str();
    if (str.length() != 8)
    {
        str = string(8 - str.length(), '0') + str;
    }
    return str;
}

string I_type_to_hex(const Instruction I)
{
    unsigned int decimal_value = 0;
    decimal_value += (I.immediate << 20);
    decimal_value += (I.rs1 << 15);
    decimal_value += (I.instructionInfo.funct3 << 12);
    decimal_value += (I.rd << 7);
    decimal_value += (I.instructionInfo.opcode);
    string str;
    stringstream ss;
    ss << std::hex << decimal_value;
    str = ss.str();
    if (str.length() != 8)
    {
        str = string(8 - str.length(), '0') + str;
    }
    return str;
}

string S_type_to_hex(const Instruction S)
{
    unsigned int decimal_value = 0;
    unsigned int i = 0b111111100000;
    unsigned int j = S.immediate & i;
    j = j >> 5;
    decimal_value += (j << 25);
    decimal_value += (S.rs2 << 20);
    decimal_value += (S.rs1 << 15);
    decimal_value += (S.instructionInfo.funct3 << 12);
    i = 0b11111;
    j = S.immediate & i;
    decimal_value += (j << 7);
    decimal_value += (S.instructionInfo.opcode);
    string str;
    stringstream ss;
    ss << std::hex << decimal_value;
    str = ss.str();
    if (str.length() != 8)
    {
        str = string(8 - str.length(), '0') + str;
    }
    return str;
}

string B_type_to_hex(const Instruction B)
{
    unsigned int decimal_value = 0;
    unsigned int i = 0b1000000000000;
    unsigned int j = B.immediate & i;
    j >>= 12;
    decimal_value += (j << 31);
    i = 0b11111100000;
    j = B.immediate & i;
    j >>= 5;
    decimal_value += (j << 25);
    decimal_value += (B.rs2 << 20);
    decimal_value += (B.rs1 << 15);
    decimal_value += (B.instructionInfo.funct3 << 12);
    i = 0b11110;
    j = B.immediate & i;
    j >>= 1;
    decimal_value += (j << 8);
    i = 0b100000000000;
    j = B.immediate & i;
    j >>= 11;
    decimal_value += (j << 7);
    decimal_value += (B.instructionInfo.opcode);
    string str;
    stringstream ss;
    ss << std::hex << decimal_value;
    str = ss.str();
    if (str.length() != 8)
    {
        str = string(8 - str.length(), '0') + str;
    }
    return str;
}

string U_type_to_hex(const Instruction U)
{
    unsigned int decimal_value = 0;
    decimal_value += (U.instructionInfo.opcode);
    decimal_value += (U.rd << 7);
    decimal_value += (U.immediate << 12);
    string str;
    stringstream ss;
    ss << std::hex << decimal_value;
    str = ss.str();
    if (str.length() != 8)
    {
        str = string(8 - str.length(), '0') + str;
    }
    return str;
}

string J_type_to_hex(const Instruction J)
{
    unsigned int decimal_value = 0;
    int i = 0b100000000000000000000;
    int j = J.immediate & i;
    decimal_value += (j << 11);
    i = 0b11111111110;
    j = J.immediate & i;
    decimal_value += (j << 20);
    i = 0b100000000000;
    j = J.immediate & i;
    decimal_value += (j << 9);
    i = 0b11111111000000000000;
    j = J.immediate & i;
    decimal_value += (j);
    decimal_value += (J.rd << 7);
    decimal_value += (J.instructionInfo.opcode);

    string str;
    stringstream ss;
    ss << std::hex << decimal_value;
    str = ss.str();
    if (str.length() != 8)
    {
        str = string(8 - str.length(), '0') + str;
    }
    return str;
}