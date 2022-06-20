all:
	lex lex.l
	bison -d yacc.ypp
	g++ -w -std=c++17 lex.yy.c entries.cpp scope.cpp table.cpp util.cpp yacc.tab.cpp -lfmt -o gocompiler
clean:
	rm lex.yy.c
	rm yacc.tab.cpp
	rm yacc.tab.hpp
	rm gocompiler