#pragma once

#include <map>
#include <string>

class SymTable
{
public:
    std::map<std::string, int> table
    {
        {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3},
        {"R4", 4}, {"R5", 5}, {"R6", 6}, {"R7", 7},
        {"R8", 8}, {"R9", 9}, {"R10", 10}, {"R11", 11},
        {"R12", 12}, {"R13", 13}, {"R14", 14}, {"R15", 15},
        {"SCREEN", 16384}, {"KBD", 24576},
        {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4}
    };

private:
    int symPointer = 16;
public:
    int Add(std::string& symbol) noexcept;
    void Add(std::string& symbol, int value) noexcept;
    int Find(std::string& symbol) noexcept;
};
