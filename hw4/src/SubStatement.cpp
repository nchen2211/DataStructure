// SubStatement.cpp:
#include "../lib/SubStatement.h"
#include <iostream>

using namespace std;

SubStatement::SubStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{
	m_variableName1 = " ";
}


SubStatement::SubStatement(std::string variableName, std::string variableName1)
	: m_variableName( variableName ), m_variableName1( variableName1 )
{}

void SubStatement::execute(ProgramState * state, ostream &outf)
{	
	if (m_variableName1 != " ") 
		state->subtraction(m_variableName, m_variableName1, 0);
	else
		state->subtraction(m_variableName, " ", m_value);

	state->executeLine(1);
	state->statementExecuted();
}