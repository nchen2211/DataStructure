#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include "stackint.h"
#include <map>
#include <string>
#include <fstream>
#include <vector>

class ProgramState
{
public:
	// constructor & copy constructor
	ProgramState(int numLines);
	ProgramState(const ProgramState&);

	// total number of line 
	void setFacileLine (int);
	int getFacileLine();

	// used in GOTO and show the line that will be executed next
	int executeLine(int);
	int gotoLine(int);

	// executed line
	void statementExecuted();
	int getStatementExecuted();

	// used in SET, PRINT, PRINTALL
	void setValue(std::string, int);
	int display(std::string);
	void displayAll(std::ostream& outf);

	// used in arithmetics operation
	void addition(std::string, std::string, int);
	void subtraction(std::string, std::string, const int&);
	void multiplication(std::string, std::string, const int&);
	void division(std::string, std::string, const int&);

	//used in IF, GOSUB, RETURN
	//utility for IF
	void ifcondition(int);
	void ifstatement(std::string, std::string, int, int);
	void gosubStatement(int);
	void returnStatement();
	
	// used in END
	void endProgram();

	// condition to terminate program
	void setDivZero();
	bool divZero();
	void setOutBound();
	bool outBound();
	void setReturnError();
	bool getReturnError();

	//Qt
	void setQtLine(int);
	int getQtLine();
	void setJump(int);
	int getJump();
	void mapDeallocation();

	// to know when to reset
	void setEndProgram(int);
	int getEndProgram();

	// gosub & return
	void setGosub(int);
	int getGosub();
	void setReturn(int);
	int getReturn();

	int inStack();

	// exception notification
	void setErrorWin(int);
	int getErrorWin();

	void storeToValueWindow(std::vector<std::pair<std::string,int> > &mapValues, std::vector<std::pair<int, std::string> > &swap_mapValues);

private:
	int m_numLines;
	int m_executedStatement;
	bool m_divZero;
	bool m_outBound;
	bool m_return;
	int m_facileLine;

	StackInt stackint;
	std::map<std::string, int> *Commands;

	//Qt
	int q_executeLine;
	int q_jump;
	int q_gosub;
	int q_return;
	int q_stacktop;
	int q_end;
	int q_error;
};	

#endif



