// GosubStatement.cpp:
#include "../lib/GosubStatement.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

GosubStatement::GosubStatement(int linenum)
	: m_linenum( linenum )
{}

void GosubStatement::execute(ProgramState * state, std::ostream &outf) {
	
	if(m_linenum <= 0 || m_linenum > state->getFacileLine()) 
		state->setOutBound();
	else {
		state->setJump(1); 
		state->setGosub(1);
		state->setQtLine(m_linenum);

		state->executeLine(1); //push the line after GOSUB
		state->gosubStatement(m_linenum);
		state->statementExecuted();
	}
			
}


