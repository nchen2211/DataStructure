#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class SubStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_variableName1;
	int m_value;

public:
	SubStatement(std::string variableName, int value);
	SubStatement(std::string variableName, std::string variableName1);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif