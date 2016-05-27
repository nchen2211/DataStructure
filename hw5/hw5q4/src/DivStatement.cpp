// DivStatement.cpp:
#include "../lib/DivStatement.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

DivStatement::DivStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{
	m_variableName1 = " ";
}


DivStatement::DivStatement(std::string variableName, std::string variableName1)
	: m_variableName( variableName ), m_variableName1( variableName1 )
{}

void DivStatement::execute(ProgramState * state, ostream &outf)
{	

	if (m_variableName1 != " ") 
		state->division(m_variableName, m_variableName1, 0);
	else {

		if (m_value == 0) 
			state->setDivZero();	
		else
			state->division(m_variableName, " ", m_value);
	}

	state->executeLine(1);
	state->statementExecuted();
}