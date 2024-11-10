#ifndef Main_H
#define Main_H
#include "instruction.h"
#include <unordered_map>
extern Instruction Lines[4096];
extern std::unordered_map<std::string, int> labelData;
extern int ProgramCounter;
extern int EmptyLines[4096];
struct cache
{
    bool cacheStatus;
    int cacheSize;
    int blockSize;
    int associativity;
    int noSets;
    std::string replacementPolicy;
    std::string writeBackPolicy;
    cache() : cacheStatus(false), cacheSize(0), blockSize(0), associativity(0), replacementPolicy(""), writeBackPolicy("") {}
};
extern cache cacheData;
void initCache();
#endif