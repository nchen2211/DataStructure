#ifndef FACILE_INCLUDED
#define FACILE_INCLUDED
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "GotoStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "IfStatement.h"
#include "GosubStatement.h"
#include "ReturnStatement.h"
#include "EndStatement.h"
#include "LoadWindow.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

using namespace std;

class Facile {

public:

	Facile();
	string intToString (int num);
	void parseProgram(istream& inf, LoadWindow &loadwindow, vector<Statement*> &program);
	Statement * parseLine(string line);
	void deallocation (vector<Statement*> &program, ProgramState *pstate);
	void interpretProgram(istream& inf, ostream& outf, LoadWindow &loadwindow, vector<Statement*> &program,  ProgramState *pstate);
	void interpretProgramHelper(istream& inf,LoadWindow &loadwindow, vector<Statement*> &program);
	void QtInterpret(vector<Statement*> &program, ProgramState *pstate, int line);

private:
	int f_execute;
};

#endif