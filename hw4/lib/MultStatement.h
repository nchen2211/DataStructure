#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class MultStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_variableName1;

	int m_value;

public:
	MultStatement(std::string variableName, int value);
	MultStatement(std::string variableName, std::string variableName1);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif