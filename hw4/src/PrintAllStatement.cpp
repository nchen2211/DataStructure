// PrintAllStatement.cpp:
#include "../lib/PrintAllStatement.h"
#include <iostream>

void PrintAllStatement::execute(ProgramState * state, std::ostream &outf) {
	
	state->displayAll(outf);
	state->executeLine(1);
	state->statementExecuted();
} 


