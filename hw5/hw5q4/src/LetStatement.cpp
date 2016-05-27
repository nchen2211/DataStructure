// LetStatement.cpp:
#include "../lib/LetStatement.h"
#include <iostream>

using namespace std;

LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{}


void LetStatement::execute(ProgramState * state, ostream &outf)
{	
	state->setValue(m_variableName, m_value);
	state->executeLine(1);
	state->statementExecuted();
}