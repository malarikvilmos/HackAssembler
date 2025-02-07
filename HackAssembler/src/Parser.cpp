#include "Parser.h"
#include <cstdint>
#include <algorithm>

Parser::Parser(const char* file) noexcept
{
    std::ifstream fileIN(file);
    uint64_t linenumber = 1;
    uint64_t skipped = 0;

    while (getline(fileIN, line))
    {
        //Remove whitespaces and comments
        if (!line.empty() && !(line[0] == '/' && line[1] == '/'))
        {
            //std::cout << line << std::endl;
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            uint64_t location = std::find(line.begin(), line.end(), '/') - line.begin();
            if (line[location + 1] == '/')
                line.erase(line.begin() + location, line.end());

            //Translate label declarations to instruction numbers
            if (line[0] == '(')
            {
                int instruction_number = linenumber - 1 - skipped;
                line = line.substr(1, line.find(')') - 1);
                symtable.Add(line, instruction_number);
                continue;
            }

            //Handle A instructions
            if (line[0] == '@')
            {
                const char* address = line.c_str() + 1;
                std::string str = address;
                if (std::isdigit(str[0]) && str.substr(0, std::string::npos).find_first_not_of("0123456789") != std::string::npos)
                {
                    std::cout << "There is an error on line " << linenumber << std::endl;
                    error = true;
                }
                tokens.push_back("@");
                tokens.push_back(address);
            }
            //Handle C instructions
            else
            {
                tokens.push_back("C");
                if (line.find('=') != std::string::npos)
                {
                    uint64_t first = line.find('=');
                    uint64_t second = line.find(';', first);
                    tokens.push_back(line.substr(first + 1, second - (first + 1)));
                    tokens.push_back(line.substr(0, first));
                    std::string last = line.substr(++second);
                    if (last.find('=') != std::string::npos) tokens.push_back("null");
                    else tokens.push_back(last);
                }
                else if (line[0] == '0')
                {
                    tokens.push_back("0");
                    tokens.push_back("null");
                    tokens.push_back("JMP");
                }
                else if (line[0] == 'D')
                {
                    tokens.push_back("D");
                    tokens.push_back("null");
                    tokens.push_back(line.substr(line.find(';')+1, std::string::npos));
                }
                else
                {
                    std::cout << "There is an error on line " << linenumber << std::endl;
                    error = true;
                }
            }
        }
        else ++skipped;
        ++linenumber;
    }
}

Parser::~Parser() noexcept
{
    file.close();
}
