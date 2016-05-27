// GotoStatement.cpp:
#include "../lib/GotoStatement.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

GotoStatement::GotoStatement(int linenum)
	: m_linenum( linenum )
{}

void GotoStatement::execute(ProgramState * state, std::ostream &outf) {

	if(m_linenum <= 0 || m_linenum > state->getFacileLine()) 
		state->setOutBound();
	else {

		state->executeLine(1);
		state->gotoLine(m_linenum);
		state->statementExecuted();
	}
	
}


