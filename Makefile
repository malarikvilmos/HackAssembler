build:
	clear
	g++ -std=c++2a -no-pie \
	src/main.cpp \
	src/Generator.cpp \
	src/Parser.cpp \
	src/SymTable.cpp \
	-o hasmbler
clean:
	rm -f hasmbler
