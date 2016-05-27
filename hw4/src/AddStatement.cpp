// AddStatement.cpp:
#include "../lib/AddStatement.h"
#include <iostream>

using namespace std;

AddStatement::AddStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{
	m_variableName1 = " ";
}

AddStatement::AddStatement(std::string variableName, std::string variableName1)
	: m_variableName( variableName ), m_variableName1( variableName1 )
{}

void AddStatement::execute(ProgramState * state, ostream &outf)
{	
	if (m_variableName1 != " ") 
		state->addition(m_variableName, m_variableName1, 0);
	
	else
		state->addition(m_variableName, " ", m_value);

	state->executeLine(1);
	state->statementExecuted();
}