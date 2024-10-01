#ifndef LINERUNNER_H
#define LINERUNNER_H

#include "instruction.h"
#include "cpu.h"
#include "memory.h"
#include "data.h"
#include <unordered_map>
void func_add(Instruction instruct);
void func_sub(Instruction instruct);
void func_xor(Instruction instruct);
void func_or(Instruction instruct);
void func_and(Instruction instruct);
void func_sll(Instruction instruct);
void func_srl(Instruction instruct);
void func_sra(Instruction instruct);
void func_slt(Instruction instruct);
void func_sltu(Instruction instruct);
void func_addi(Instruction instruct);
void func_xori(Instruction instruct);
void func_ori(Instruction instruct);
void func_andi(Instruction instruct);
void func_slli(Instruction instruct);
void func_srli(Instruction instruct);
void func_srai(Instruction instruct);
void func_slti(Instruction instruct);
void func_sltui(Instruction instruct);
void func_lb(Instruction instruct);
void func_lh(Instruction instruct);
void func_lw(Instruction instruct);
void func_ld(Instruction instruct);
void func_lbu(Instruction instruct);
void func_lhu(Instruction instruct);
void func_lwu(Instruction instruct);
void func_sb(Instruction instruct);
void func_sh(Instruction instruct);
void func_sw(Instruction instruct);
void func_sd(Instruction instruct);
void func_beq(Instruction instruct);
void func_bne(Instruction instruct);
void func_blt(Instruction instruct);
void func_bge(Instruction instruct);
void func_bltu(Instruction instruct);
void func_bgeu(Instruction instruct);
void func_jal(Instruction instruct);
void func_jalr(Instruction instruct);
void func_lui(Instruction instruct);
void func_auipc(Instruction instruct);

const std::unordered_map<std::string, void (*)(Instruction)> functionMap =
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

#endif