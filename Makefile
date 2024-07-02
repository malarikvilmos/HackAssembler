build:
	clang++ -std=c++20 \
	src/main.cpp \
	src/Generator.cpp \
	src/Parser.cpp \
	src/SymTable.cpp \
	-o hasmbler.exe
