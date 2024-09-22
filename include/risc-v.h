#ifndef RISC_V_H
#define RISC_V_H

#include "instruction.h"
#include <unordered_map>

const std::unordered_map<std::string, InstructionInfo> instructionData = {
    {"add", {InstructionFormat::R_TYPE, 0x33, 0x0, 0x00}},
    {"sub", {InstructionFormat::R_TYPE, 0x33, 0x0, 0x20}},
    {"xor", {InstructionFormat::R_TYPE, 0x33, 0x4, 0x00}},
    {"or", {InstructionFormat::R_TYPE, 0x33, 0x6, 0x00}},
    {"and", {InstructionFormat::R_TYPE, 0x33, 0x7, 0x00}},
    {"sll", {InstructionFormat::R_TYPE, 0x33, 0x1, 0x00}},
    {"srl", {InstructionFormat::R_TYPE, 0x33, 0x5, 0x00}},
    {"sra", {InstructionFormat::R_TYPE, 0x33, 0x5, 0x20}},
    {"slt", {InstructionFormat::R_TYPE, 0x33, 0x2, 0x00}},
    {"sltu", {InstructionFormat::R_TYPE, 0x33, 0x3, 0x00}},
    {"addi", {InstructionFormat::I_TYPE, 0x13, 0x0, 0x00}},
    {"xori", {InstructionFormat::I_TYPE, 0x13, 0x4, 0x00}},
    {"ori", {InstructionFormat::I_TYPE, 0x13, 0x6, 0x00}},
    {"andi", {InstructionFormat::I_TYPE, 0x13, 0x7, 0x00}},
    {"slli", {InstructionFormat::I_TYPE, 0x13, 0x1, 0x00}},
    {"srli", {InstructionFormat::I_TYPE, 0x13, 0x5, 0x00}},
    {"srai", {InstructionFormat::I_TYPE, 0x13, 0x5, 0x00}},
    {"slti", {InstructionFormat::I_TYPE, 0x13, 0x2, 0x00}},
    {"sltiu", {InstructionFormat::I_TYPE, 0x13, 0x3, 0x00}},
    {"lb", {InstructionFormat::I_TYPE, 0x03, 0x0, 0x00}},
    {"lh", {InstructionFormat::I_TYPE, 0x03, 0x1, 0x00}},
    {"lw", {InstructionFormat::I_TYPE, 0x03, 0x2, 0x00}},
    {"ld", {InstructionFormat::I_TYPE, 0x03, 0x3, 0x00}},
    {"lbu", {InstructionFormat::I_TYPE, 0x03, 0x4, 0x00}},
    {"lhu", {InstructionFormat::I_TYPE, 0x03, 0x5, 0x00}},
    {"ldu", {InstructionFormat::I_TYPE, 0x03, 0x6, 0x00}},
    {"sb", {InstructionFormat::S_TYPE, 0x23, 0x0, 0x00}},
    {"sh", {InstructionFormat::S_TYPE, 0x23, 0x1, 0x00}},
    {"sw", {InstructionFormat::S_TYPE, 0x23, 0x2, 0x00}},
    {"sd", {InstructionFormat::S_TYPE, 0x23, 0x3, 0x00}},
    {"beq", {InstructionFormat::B_TYPE, 0x63, 0x0, 0x00}},
    {"bne", {InstructionFormat::B_TYPE, 0x63, 0x1, 0x00}},
    {"blt", {InstructionFormat::B_TYPE, 0x63, 0x4, 0x00}},
    {"bge", {InstructionFormat::B_TYPE, 0x63, 0x5, 0x00}},
    {"bltu", {InstructionFormat::B_TYPE, 0x63, 0x6, 0x00}},
    {"bgeu", {InstructionFormat::B_TYPE, 0x63, 0x7, 0x00}},
    {"jal", {InstructionFormat::J_TYPE, 0x6F, 0x0, 0x00}},
    {"jalr", {InstructionFormat::I_TYPE, 0x67, 0x0, 0x00}},
    {"lui", {InstructionFormat::U_TYPE, 0x37, 0x0, 0x00}},
    {"auipc", {InstructionFormat::U_TYPE, 0x17, 0x0, 0x00}},
    {"ecall", {InstructionFormat::I_TYPE, 0x73, 0x0, 0x00}},
    {"ebreak", {InstructionFormat::I_TYPE, 0x73, 0x0, 0x01}},
};

const std::unordered_map<std::string, std::string> registerData = {
    {"zero", "x0"},
    {"ra", "x1"},
    {"sp", "x2"},
    {"gp", "x3"},
    {"tp", "x4"},
    {"t0", "x5"},
    {"t1", "x6"},
    {"t2", "x7"},
    {"s0", "x8"},
    {"s1", "x9"},
    {"a0", "x10"},
    {"a1", "x11"},
    {"a2", "x12"},
    {"a3", "x13"},
    {"a4", "x14"},
    {"a5", "x15"},
    {"a6", "x16"},
    {"a7", "x17"},
    {"s2", "x18"},
    {"s3", "x19"},
    {"s4", "x20"},
    {"s5", "x21"},
    {"s6", "x22"},
    {"s7", "x23"},
    {"s8", "x24"},
    {"s9", "x25"},
    {"s10", "x26"},
    {"s11", "x27"},
    {"t3", "x28"},
    {"t4", "x29"},
    {"t5", "x30"},
    {"t6", "x31"},
};

#endif