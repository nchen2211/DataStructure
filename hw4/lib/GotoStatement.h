#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class GotoStatement: public Statement
{
private:
	int m_linenum;
	
public:
	GotoStatement(int);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

