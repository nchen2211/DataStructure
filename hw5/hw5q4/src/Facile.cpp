// Facile.cpp
#include "../lib/Facile.h"

Facile::Facile() 
{}


string Facile::intToString(int num)
{
     ostringstream ss;
     ss << num;
     return ss.str();
}


void Facile::parseProgram(istream &inf, LoadWindow &loadwindow, vector<Statement*> &program)
{
	program.push_back(NULL);
	string line;
	int lineIndicator = 1;

	while(!inf.eof())
	{
		getline(inf, line);
		string lineInd = intToString(lineIndicator);
		loadwindow.storeStatement(line,lineInd);
		lineIndicator++;
		program.push_back(parseLine(line));
	}
	//pstate = new ProgramState (1);
	loadwindow.displayStatement();
}


Statement * Facile::parseLine(string line)
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


void Facile::deallocation (vector<Statement*> &program, ProgramState *pstate) 
{
	unsigned int x = 0;
	while (x < program.size()){

		delete program[x];
		++x;
	}

	pstate->endProgram();
	delete pstate;
	pstate = NULL;
}

void Facile::interpretProgramHelper(istream& inf, LoadWindow &loadwindow, vector<Statement*> &program) 
{
	parseProgram(inf, loadwindow, program);
}

void Facile::QtInterpret(vector<Statement*> &program, ProgramState *pstate, int line)
{
	program[line]->execute(pstate,cout);
}

void Facile::interpretProgram(istream& inf, ostream& outf, LoadWindow &loadwindow, vector<Statement*> &program, ProgramState *pstate)
{
	interpretProgramHelper(inf,loadwindow, program);
	
	int executedStmt = 0;

	// this is for jumpline in GOTO, GOSUB, IF
	pstate->setFacileLine(program.size());

	while (executedStmt <= pstate->getStatementExecuted())
	{
		// if line > 1000
		if (program.size() >= 1001) 
		{
			outf << "Facile program may not exceed 1000 lines." << endl;
			//deallocation(program, pstate);
			break;
		}

		cout << "Execute line: " << pstate->executeLine(0) << endl;
		program[pstate->executeLine(0)]->execute(pstate, cout);
		//loadwindow.currLine(pstate->executeLine(0));
		++executedStmt;
		//i = pstate->executeLine(0);

		//cout << "Execute line: " << i << endl;
	
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

			deallocation(program, pstate);
			break;
			//executedStmt = 0;
		}

	}

}