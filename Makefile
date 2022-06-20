all:
	lex lex.l
	bison -d yacc.ypp
	g++ -w -std=c++17 lex.yy.c yacc.tab.cpp -Iinclude src/entries.cpp src/scope.cpp src/table.cpp src/util.cpp -lfmt -o gocompiler
clean:
	rm lex.yy.c
	rm yacc.tab.cpp
	rm yacc.tab.hpp
	rm gocompiler