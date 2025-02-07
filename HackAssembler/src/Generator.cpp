#include "Generator.h"

Generator::Generator(const char* name, bool binary, std::vector<std::string>& tokens) noexcept
{
    std::ofstream file(name, std::ios_base::out | std::ios_base::binary);

    bool A = false;
    std::string last;
    std::string instruction;
    unsigned long long anum = 1, cnum = 1;
    //Loop through each token acquired from the parser
    for (std::string& token : tokens)
    {
        //When instruction is complete, write to file
        if (instruction.length() == 16)
        {
            binary ? WriteBinary(file, instruction) : WriteText(file, instruction);
            instruction.clear();
        }

        //Handle A instructions
        if (token == "@")
        {
            instruction += "0";
            A = true;
            ++anum;
            continue;
        }
        if (A)
        {
            //Instruction is a memory address
            if (std::isdigit(token[0]))
            {
                instruction += std::bitset<15>(stoi(token)).to_string();
                A = false;
                ++anum;
                continue;
            }
            //Instruction is found in the SymTable
            else if (symtable.Find(token) != -1)
            {
                instruction += std::bitset<15>(symtable.Find(token)).to_string();
                A = false;
                ++anum;
                continue;
            }
            //Instruction is NOT found in the SymTable
            else
            {
                instruction += std::bitset<15>(symtable.Add(token)).to_string();
                A = false;
                ++anum;
                continue;
            }
        }

        //Handle C instructions
        if (token == "C")
        {
            instruction += "111";
            last = "C";
            ++cnum;
            continue;
        }
        if (comp.contains(token) && last == "C")
        {
            instruction += comp[token];
            last = "comp";
            ++cnum;
            continue;
        }
        if (dest.contains(token) && last == "comp")
        {
            instruction += dest[token];
            last = "dest";
            ++cnum;
            continue;
        }
        if (jump.contains(token) && last == "dest")
        {
            instruction += jump[token];
            last = "jump";
            ++cnum;
            continue;
        }
        std::cout << "There is an error on line " << anum / 2 + cnum / 4 + 8 << "at token: \"" << token << "\"" << std::endl;
        error = true;

    }
    //Write the final instruction to the file
    if (instruction.length() == 16)
    {
        binary ? WriteBinary(file, instruction) : WriteText(file, instruction);
        instruction.clear();
    }
}

Generator::~Generator() noexcept
{
    file.close();
}

void Generator::WriteBinary(std::ofstream& file, std::string& data) noexcept
{
    const char* str = data.c_str();
    char* second = (char*)str+8;
    int dat1 = strtoul(str, nullptr, 2);
    int dat2 = strtoul(second, nullptr, 2);
    dat1 >>= 8;

    file.put(dat1);
    file.put(dat2);
}

void Generator::WriteText(std::ofstream& file, std::string& data) noexcept
{
    file << data << std::endl;
}
