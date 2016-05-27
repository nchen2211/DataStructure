// PrintStatement.cpp:
#include "../lib/PrintStatement.h"
#include <iostream>

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}

void PrintStatement::execute(ProgramState * state, std::ostream &outf) {

	outf << state->display(m_variableName) << std::endl; 
	state->executeLine(1);
	state->statementExecuted();
}