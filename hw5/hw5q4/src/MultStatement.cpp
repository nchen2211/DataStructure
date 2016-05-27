// MultStatement.cpp:
#include "../lib/MultStatement.h"
#include <iostream>

using namespace std;

MultStatement::MultStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{
	m_variableName1 = " ";
}

MultStatement::MultStatement(std::string variableName, std::string variableName1)
	: m_variableName( variableName ), m_variableName1( variableName1 )
{}

void MultStatement::execute(ProgramState * state, ostream &outf)
{	
	
	if (m_variableName1 != " ") 
		state->multiplication(m_variableName, m_variableName1, 0);
	else
		state->multiplication(m_variableName, " ", m_value);

	state->executeLine(1);
	state->statementExecuted();
}