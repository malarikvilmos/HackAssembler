#include "SymTable.h"

#include <iostream>

SymTable symtable;

int SymTable::Add(std::string& symbol) noexcept
{
    table.emplace(symbol, symPointer++);
    return table[symbol];
}

void SymTable::Add(std::string& symbol, int value) noexcept
{
    table.emplace(symbol, value);
}

int SymTable::Find(std::string& symbol) noexcept
{
    if (table.contains(symbol))
        return table[symbol];
    else return -1;
}
