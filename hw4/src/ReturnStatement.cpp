// ReturnStatement.cpp:
#include "../lib/ReturnStatement.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

void ReturnStatement::execute(ProgramState * state, std::ostream &outf) {

	state->returnStatement();	
	state->executeLine(1);	
	state->statementExecuted();
}


