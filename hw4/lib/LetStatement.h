// LetStatement.h

#ifndef LET_STATEMENT_INCLUDED
#define LET_STATEMENT_INCLUDED
 
#include "Statement.h"
#include "ProgramState.h"

class LetStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;


public:
	LetStatement(std::string variableName, int value);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



