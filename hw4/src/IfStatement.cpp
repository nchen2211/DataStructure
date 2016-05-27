// IfStatement.cpp:
#include "../lib/IfStatement.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

IfStatement::IfStatement(std::string variableName, std::string compSign, int compareValue, int gotoLine)
	: m_variableName( variableName ), m_compSign( compSign ), m_compareValue ( compareValue ), m_gotoLine (gotoLine)
{}

void IfStatement::execute(ProgramState * state, ostream &outf)
{	

	if(m_gotoLine <= 0 || m_gotoLine > state->getFacileLine()) 
		state->setOutBound();
	else {
		state->ifstatement(m_variableName, m_compSign, m_compareValue, m_gotoLine);
		state->statementExecuted();
	}
	
}