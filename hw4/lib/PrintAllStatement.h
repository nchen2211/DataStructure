#ifndef PRINTALL_STATEMENT_INCLUDED
#define PRINTALL_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class PrintAllStatement: public Statement
{
private:
	std::string m_variableName;
	
public:

	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

