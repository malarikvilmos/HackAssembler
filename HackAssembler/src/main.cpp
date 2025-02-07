#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <filesystem>

#include "Parser.h"
#include "Generator.h"
#include "SymTable.h"
#include "global.h"


int main(int argc, char** argv)
{
	//Return if the number of arguments is incorrect
	if (argc < 2 || argc > 4) {
		std::cout << "HackAssembler <OPTIONAL -switch> <assembly file path> <OPTIONAL output file name>" << std::endl
			<< "Try \"HackAssembler -HELP\" for more info" << std::endl;
		return 1;
	}

	int source = 1;
	bool binary = false;
	//Handle switches
	if (argv[1][0] == '-') {
		if (!strcmp(argv[1], "-B") || !strcmp(argv[1], "-b")) binary = true;
		else if (!strcmp(argv[1], "-HELP") || !strcmp(argv[1], "-help")){
			std::cout << "HackAssembler <OPTIONAL -switch> <assembly file path> <OPTIONAL output file name>\n" << std::endl
				<< "Availabe switches:" << std::endl << "-B or -b for binary mode" << std::endl;
			return 2;
		}
		else {
			std::cout << "Unknown switch, availabe switches: -B or -b for binary mode" << std::endl;
			return 3;
		}
		source = 2;
	}

	//Source file doesn't exist
	if (!std::filesystem::exists(argv[source])) {
		std::cout << "Assembly file \"" << argv[source] << "\" does not exist" << std::endl;
		return 4;
	}

	Parser parser(argv[source]);

	//Get the output file name
	std::string name;
	if (source == argc-1){
		name = argv[source];
		name = name.substr(0, name.find('.'));
		name += ".hack";
		name = "." + name;
	}
	else {
		name = ".";
		name += argv[source + 1];
	}
	std::filesystem::remove(name);
	Generator generator(name.c_str(), binary, parser.tokens);

	//If no error, save temporary file to the output file, then delete the temporary one
	if (!parser.error && !generator.error){
		std::filesystem::remove(name.substr(1, std::string::npos));
		std::filesystem::copy_file(name, name.substr(1, std::string::npos));
		std::filesystem::remove(name);
		std::cout << "File compiled successfully." << std::endl;
	}
	//If there is an error, delete the temporary file and do not save
	else {
		std::filesystem::remove(name);
		std::cout << "Compilation failed: ";
		if (parser.error){
			std::cout << "parser error" << std::endl;
		}
		if (generator.error){
			std::cout << "generator error" << std::endl;
		}
		
	}

	return 0;
}
