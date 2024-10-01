#include "../include/linerunner.h"

void func_add(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 + rs2;
    SetRegister(cpu, rd_index, result);
}
void func_sub(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 - rs2;
    SetRegister(cpu, rd_index, result);
}
void func_xor(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 ^ rs2;
    SetRegister(cpu, rd_index, result);
}
void func_or(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 | rs2;
    SetRegister(cpu, rd_index, result);
}
void func_and(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 & rs2;
    SetRegister(cpu, rd_index, result);
}
void func_sll(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 << rs2;
    SetRegister(cpu, rd_index, result);
}
void func_srl(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    unsigned int result = rs1 >> rs2;
    SetRegister(cpu, rd_index, result);
}

void func_sra(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 >> rs2;
    SetRegister(cpu, rd_index, result);
}
void func_slt(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 < rs2;
    SetRegister(cpu, rd_index, result);
}
void func_sltu(Instruction instruct)
{
    int rd_index = instruct.rd;
    unsigned int rs1 = GetRegister(cpu, instruct.rs1);
    unsigned int rs2 = GetRegister(cpu, instruct.rs2);
    int result = rs1 < rs2;
    SetRegister(cpu, rd_index, result);
}
void func_addi(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 + imm;
    SetRegister(cpu, rd_index, result);
}
void func_xori(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 ^ imm;
    SetRegister(cpu, rd_index, result);
}
void func_ori(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 | imm;
    SetRegister(cpu, rd_index, result);
}
void func_andi(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 & imm;
    SetRegister(cpu, rd_index, result);
}
void func_slli(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 << imm;
    SetRegister(cpu, rd_index, result);
}
void func_srli(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned int result = rs1 >> imm;
    SetRegister(cpu, rd_index, result);
}
void func_srai(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 >> imm;
    SetRegister(cpu, rd_index, result);
}
void func_slti(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = rs1 < imm;
    SetRegister(cpu, rd_index, result);
}
void func_sltui(Instruction instruct)
{
    int rd_index = instruct.rd;
    unsigned int rs1 = GetRegister(cpu, instruct.rs1);
    unsigned int imm = instruct.immediate;
    int result = rs1 < imm;
    SetRegister(cpu, rd_index, result);
}
void func_lb(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = fechMemory(rs1 + imm, 1);
    result = result & 0x000000FF;
    SetRegister(cpu, rd_index, result);
}
void func_lh(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = fechMemory(rs1 + imm, 2);
    result = result & 0x0000FFFF;
    SetRegister(cpu, rd_index, result);
}
void func_lw(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = fechMemory(rs1 + imm, 4);
    result = result & 0xFFFFFFFF;
    SetRegister(cpu, rd_index, result);
}
void func_ld(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    int result = fechMemory(rs1 + imm, 8);
    SetRegister(cpu, rd_index, result);
}
void func_lbu(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned int result = fechMemory(rs1 + imm, 1);
    result = result & 0x000000FF;
    SetRegister(cpu, rd_index, result);
}
void func_lhu(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned int result = fechMemory(rs1 + imm, 2);
    result = result & 0x0000FFFF;
    SetRegister(cpu, rd_index, result);
}
void func_lwu(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned int result = fechMemory(rs1 + imm, 4);
    SetRegister(cpu, rd_index, result);
}
void func_sb(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 1, rs2);
}
void func_sh(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 2, rs2);
}
void func_sw(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 4, rs2);
}
void func_sd(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 8, rs2);
}
void func_beq(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 == rs2)
    {
        ProgramCounter += imm;
    }
}
void func_bne(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 != rs2)
    {
        ProgramCounter += imm;
    }
}
void func_blt(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 < rs2)
    {
        ProgramCounter += imm;
    }
}
void func_bge(Instruction instruct)
{
    int rs1 = GetRegister(cpu, instruct.rs1);
    int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 >= rs2)
    {
        ProgramCounter += imm;
    }
}
void func_bltu(Instruction instruct)
{
    unsigned int rs1 = GetRegister(cpu, instruct.rs1);
    unsigned int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 < rs2)
    {
        ProgramCounter += imm;
    }
}
void func_bgeu(Instruction instruct)
{
    unsigned int rs1 = GetRegister(cpu, instruct.rs1);
    unsigned int rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 >= rs2)
    {
        ProgramCounter += imm;
    }
}
void func_jal(Instruction instruct)
{
    int rd_index = instruct.rd;
    SetRegister(cpu, rd_index, (ProgramCounter + 1) * 4);
    int imm = instruct.immediate / 4;
    ProgramCounter += imm;
    stackPointer--;
}
void func_jalr(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1);
    SetRegister(cpu, rd_index, (ProgramCounter + 1) * 4);
    int imm = instruct.immediate / 4;
    ProgramCounter = rs1 + imm;
    stackPointer++;
}
void func_lui(Instruction instruct)
{
    int rd_index = instruct.rd;
    int imm = instruct.immediate;
    SetRegister(cpu, rd_index, imm << 12);
}
void func_auipc(Instruction instruct)
{
    int rd_index = instruct.rd;
    int imm = instruct.immediate;
    SetRegister(cpu, rd_index, ProgramCounter * 4 + imm);
}

std::unordered_map<std::string, void (*)(Instruction)> functionMap =
    {
        {"add", &func_add},
        {"sub", &func_sub},
        {"xor", &func_xor},
        {"or", &func_or},
        {"and", &func_and},
        {"sll", &func_sll},
        {"srl", &func_srl},
        {"sra", &func_sra},
        {"slt", &func_slt},
        {"sltu", &func_sltu},
        {"addi", &func_addi},
        {"xori", &func_xori},
        {"ori", &func_ori},
        {"andi", &func_andi},
        {"slli", &func_slli},
        {"srli", &func_srli},
        {"srai", &func_srai},
        {"slti", &func_slti},
        {"sltiu", &func_sltui},
        {"lb", &func_lb},
        {"lh", &func_lh},
        {"lw", &func_lw},
        {"ld", &func_ld},
        {"lbu", &func_lbu},
        {"lhu", &func_lhu},
        {"lwu", &func_lwu},
        {"sb", &func_sb},
        {"sh", &func_sh},
        {"sw", &func_sw},
        {"sd", &func_sd},
        {"beq", &func_beq},
        {"bne", &func_bne},
        {"blt", &func_blt},
        {"bge", &func_bge},
        {"bltu", &func_bltu},
        {"bgeu", &func_bgeu},
        {"jal", &func_jal},
        {"jalr", &func_jalr},
        {"lui", &func_lui},
        {"auipc", &func_auipc}};