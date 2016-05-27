// Facile.cpp
#include "lib/Statement.h"
#include "lib/LetStatement.h"
#include "lib/PrintStatement.h"
#include "lib/PrintAllStatement.h"
#include "lib/GotoStatement.h"
#include "lib/AddStatement.h"
#include "lib/SubStatement.h"
#include "lib/MultStatement.h"
#include "lib/DivStatement.h"
#include "lib/IfStatement.h"
#include "lib/GosubStatement.h"
#include "lib/ReturnStatement.h"
#include "lib/EndStatement.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

using namespace std;

void parseProgram(istream& inf, vector<Statement *> & program);
Statement * parseLine(string line);
void interpretProgram(istream& inf, ostream& outf);


int main()
{
    cout << "Enter Facile program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile)
    {
            cout << "Cannot open " << filename << "!" << endl;
            return 1;
    }
    interpretProgram(infile, cout);
}


void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);

	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );

	}
}


Statement * parseLine(string line)
{
	Statement * statement;
	stringstream ss;
	string type;
	string var;
	int val;

	ss << line;
	ss >> type;

	if (!line.empty()) {

		if (type == "LET") {	

			ss >> var;
			ss >> val;
			statement = new LetStatement(var, val);
		}
		else if (type == "PRINT") {

			ss >> var;
			statement = new PrintStatement(var);
		}
		else if (type == "PRINTALL") {

			statement = new PrintAllStatement();
		}
		else if (type == "GOTO") {

			ss >> val;
			statement = new GotoStatement(val);
		}
		else if (type == "ADD") {

			std::string var1;
			stringstream ss1;
			ss >> var;
			ss >> var1;
			ss1 << var1;

			//statement = arithmetic (ss, ss1, var, var1, val);
			if (ss1.peek() >= 'A' && ss1.peek() <= 'Z') {
				ss >> var1;
				statement = new AddStatement(var, var1);
			}
			else {
				istringstream(var1) >> val;
				var1 = " ";
				statement = new AddStatement(var, val);
			}
			
		}
		else if (type == "SUB") {

			std::string var1;
			stringstream ss1;
			ss >> var;
			ss >> var1;
			ss1 << var1;

			if (ss1.peek() >= 'A' && ss1.peek() <= 'Z') {
				ss >> var1;
				statement = new SubStatement(var, var1);
			}
			else {
				istringstream(var1) >> val;
				var1 = " ";
				statement = new SubStatement(var, val);
			}

		}
		else if (type == "MULT") {

			std::string var1;
			stringstream ss1;
			ss >> var;
			ss >> var1;
			ss1 << var1;

			if (ss1.peek() >= 'A' && ss1.peek() <= 'Z') {
				ss >> var1;
				statement = new MultStatement(var, var1);
			}
			else {

				istringstream(var1) >> val;
				var1 = " ";
				statement = new MultStatement(var, val);
			}

		}
		else if (type == "DIV") {

			std::string var1;
			stringstream ss1;
			ss >> var;
			ss >> var1;
			ss1 << var1;

			if (ss1.peek() >= 'A' && ss1.peek() <= 'Z') {
				ss >> var1;
				statement = new DivStatement(var, var1);
			}
			else {
				istringstream(var1) >> val;
				var1 = " ";
				statement = new DivStatement(var, val);
			}
		}
		else if (type == "IF") {

			std::string compSign;
			std::string then;
			int jumpLine;
			ss >> var;
			ss >> compSign;
			ss >> val;
			ss >> then;
			ss >> jumpLine;
			statement = new IfStatement(var, compSign, val, jumpLine); 
		}
		else if (type == "GOSUB") {
			ss >> val;
			statement = new GosubStatement(val);
		}
		else if (type == "RETURN") {

			statement = new ReturnStatement();
		}
		else if (type == "END" || type == ".") {

			statement = new EndStatement();
		}

	}
	
	return statement;

}

void deallocation (vector<Statement*> p, ProgramState *ps) {

	unsigned int x = 0;
	while (x < p.size()){

		delete p[x];
		++x;
	}

	ps->endProgram();
	delete ps;
	ps = NULL;

}

void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement*> program;
	parseProgram(inf, program);

	ProgramState *pstate = new ProgramState (0);
	
	unsigned int i = 1;
	int executedStmt = 0;

	pstate->setFacileLine(program.size());

	while (executedStmt <= pstate->getStatementExecuted())
	{
		// if line > 1000
		if (program.size() >= 1000) 
		{
			outf << "Facile program may not exceed 1000 lines." << endl;
			deallocation(program, pstate);
			break;
		}

		program[i]->execute(pstate, cout);
		++executedStmt;
		i = pstate->executeLine(0);

		// EXCEPTIONS
		// illegal jump instruction 
		if (pstate->outBound()) { 

			outf << "Illegal jump instruction." << endl;
			deallocation(program, pstate);
			break;
		}
		// divided by zero
		if (pstate->divZero()) {

			outf << "Divide by zero exception." << endl;
			deallocation(program, pstate);
			break;
		}
		// RETURN without GOSUB
		if (pstate->getReturnError()) {

			outf << "Nothing to RETURN in the stack." << endl;
			deallocation(program, pstate);
			break;
		}
		
		//if END or .
		if (pstate->getStatementExecuted() == -1) {

			outf << "END OF FILE -- Facile terminated." << endl;
			deallocation(program, pstate);
			break;
		}

	}

}