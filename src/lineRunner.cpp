#include "../include/linerunner.h"

void func_add(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 + rs2;
    SetRegister(cpu, rd_index, result);
}
void func_sub(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 - rs2;
    SetRegister(cpu, rd_index, result);
}
void func_xor(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 ^ rs2;
    SetRegister(cpu, rd_index, result);
}
void func_or(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 | rs2;
    SetRegister(cpu, rd_index, result);
}
void func_and(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 & rs2;
    SetRegister(cpu, rd_index, result);
}
void func_sll(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 << rs2;
    SetRegister(cpu, rd_index, result);
}
void func_srl(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    unsigned __int64 result = rs1 >> rs2;
    SetRegister(cpu, rd_index, result);
}

void func_sra(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 >> rs2;
    SetRegister(cpu, rd_index, result);
}
void func_slt(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 < rs2;
    SetRegister(cpu, rd_index, result);
}
void func_sltu(Instruction instruct)
{
    int rd_index = instruct.rd;
    unsigned __int64 rs1 = GetRegister(cpu, instruct.rs1);
    unsigned __int64 rs2 = GetRegister(cpu, instruct.rs2);
    __int64 result = rs1 < rs2;
    SetRegister(cpu, rd_index, result);
}
void func_addi(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 imm = instruct.immediate;
    __int64 result = rs1 + imm;
    SetRegister(cpu, rd_index, result);
}
void func_xori(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = rs1 ^ imm;
    SetRegister(cpu, rd_index, result);
}
void func_ori(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = rs1 | imm;
    SetRegister(cpu, rd_index, result);
}
void func_andi(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = rs1 & imm;
    SetRegister(cpu, rd_index, result);
}
void func_slli(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = rs1 << imm;
    SetRegister(cpu, rd_index, result);
}
void func_srli(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned __int64 result = rs1 >> imm;
    SetRegister(cpu, rd_index, result);
}
void func_srai(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = rs1 >> imm;
    SetRegister(cpu, rd_index, result);
}
void func_slti(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = rs1 < imm;
    SetRegister(cpu, rd_index, result);
}
void func_sltui(Instruction instruct)
{
    int rd_index = instruct.rd;
    unsigned __int64 rs1 = GetRegister(cpu, instruct.rs1);
    unsigned int imm = instruct.immediate;
    __int64 result = rs1 < imm;
    SetRegister(cpu, rd_index, result);
}
void func_lb(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = fechMemory(rs1 + imm, 1);
    int sign = result & 0x80;
    if (sign == 0x80)
    {
        result = result | 0xFFFFFFFFFFFFFF00;
    }
    SetRegister(cpu, rd_index, result);
}
void func_lh(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = fechMemory(rs1 + imm, 2);
    int sign = result & 0x8000;
    if (sign == 0x8000)
    {
        result = result | 0xFFFFFFFFFFFF0000;
    }
    SetRegister(cpu, rd_index, result);
}
void func_lw(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = fechMemory(rs1 + imm, 4);
    int sign = result & 0x80000000;
    if (sign == 0x80000000)
    {
        result = result | 0xFFFFFFFF00000000;
    }
    SetRegister(cpu, rd_index, result);
}
void func_ld(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    __int64 result = fechMemory(rs1 + imm, 8);
    SetRegister(cpu, rd_index, result);
}
void func_lbu(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned __int64 result = fechMemory(rs1 + imm, 1);
    result = result & 0x000000FF;
    SetRegister(cpu, rd_index, result);
}
void func_lhu(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned __int64 result = fechMemory(rs1 + imm, 2);
    result = result & 0x0000FFFF;
    SetRegister(cpu, rd_index, result);
}
void func_lwu(Instruction instruct)
{
    int rd_index = instruct.rd;
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    int imm = instruct.immediate;
    unsigned __int64 result = fechMemory(rs1 + imm, 4);
    result = result & 0xFFFFFFFF;
    SetRegister(cpu, rd_index, result);
}
void func_sb(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 1, rs2);
}
void func_sh(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 2, rs2);
}
void func_sw(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 4, rs2);
}
void func_sd(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate;
    storeMemory(rs1 + imm, 8, rs2);
}
void func_beq(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 == rs2)
    {
        ProgramCounter += imm;
    }
    else
        ProgramCounter++;
}
void func_bne(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 != rs2)
    {
        ProgramCounter += imm;
    }
    else
        ProgramCounter++;
}
void func_blt(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 < rs2)
    {
        ProgramCounter += imm;
    }
    else
        ProgramCounter++;
}
void func_bge(Instruction instruct)
{
    __int64 rs1 = GetRegister(cpu, instruct.rs1);
    __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 >= rs2)
    {
        ProgramCounter += imm;
    }
    else
        ProgramCounter++;
}
void func_bltu(Instruction instruct)
{
    unsigned __int64 rs1 = GetRegister(cpu, instruct.rs1);
    unsigned __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 < rs2)
    {
        ProgramCounter += imm;
    }
    else
        ProgramCounter++;
}
void func_bgeu(Instruction instruct)
{
    unsigned __int64 rs1 = GetRegister(cpu, instruct.rs1);
    unsigned __int64 rs2 = GetRegister(cpu, instruct.rs2);
    int imm = instruct.immediate / 4;
    if (rs1 >= rs2)
    {
        ProgramCounter += imm;
    }
    else
        ProgramCounter++;
}
void func_jal(Instruction instruct)
{
    int rd_index = instruct.rd;
    SetRegister(cpu, rd_index, (ProgramCounter + 1) * 4);
    int imm = instruct.immediate / 4;
    ProgramCounter += imm;
    stackPointer++;
}
void func_jalr(Instruction instruct)
{
    int rd_index = instruct.rd;
    int rs1 = GetRegister(cpu, instruct.rs1) / 4;
    SetRegister(cpu, rd_index, (ProgramCounter + 1) * 4);
    int imm = instruct.immediate / 4;
    ProgramCounter = rs1 + imm - 1;
    stackPointer--;
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