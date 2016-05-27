#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_compSign;
	int m_compareValue;
	int m_gotoLine;

public:
	IfStatement(std::string variableName, std::string compSign, 
		int compareValue, int gotoLine);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif