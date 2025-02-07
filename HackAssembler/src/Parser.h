#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "global.h"

class Parser
{
public:
    std::string buffer;
    std::vector<std::string> tokens;
    bool error = false;
private:
    std::string line;
    std::ifstream file;
public:
    Parser(const char* file) noexcept;
    ~Parser() noexcept;
};
