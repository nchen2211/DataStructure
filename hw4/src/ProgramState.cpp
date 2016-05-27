#include "../lib/ProgramState.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

ProgramState::ProgramState(int numLine)
	: m_numLines(numLine)
{
	Commands = new std::map<std::string, int>();
	m_executedStatement = 0;
	m_divZero = false;
	m_outBound = false;
	m_return = false;
	m_facileLine = 0;
}


ProgramState::ProgramState(const ProgramState& pstate)
{
    Commands = new std::map<std::string, int>();   
    std::map<std::string, int>::iterator it;

    for(it = pstate.Commands->begin( ); it != pstate.Commands->end( ); ++it)  // For each item in RHS
    {
        Commands->insert(std::make_pair(it->first, it->second));
    }

}

void ProgramState::setFacileLine (int size) {

	m_facileLine = size;
}

int ProgramState::getFacileLine() {

	return m_facileLine - 1;

}

int ProgramState::executeLine (int jump_line) {

	m_numLines += jump_line;
	return m_numLines;
}

void ProgramState::statementExecuted() {

	++m_executedStatement;
}

int ProgramState::getStatementExecuted() {

	return m_executedStatement;
}

int ProgramState::gotoLine (int line) {

	int jumpTo = 0;

	if (line < executeLine(0))
		jumpTo = 0 - (executeLine(0) - line);
	else if (line > executeLine(0)) 
		jumpTo = line - executeLine(0);

	return jumpTo;

}

void ProgramState::setValue(std::string str, int val) {

	std::map<std::string, int>::iterator it = Commands->find(str);

	if (it == Commands->end()) { // if it is a new elem
		Commands->insert(std::make_pair(str, val));
	}
	else {
		(*Commands)[str] = val;
	}

}

int ProgramState::display(std::string str) {

	
	std::map<std::string, int>::iterator it = Commands->find(str);
	if (it == Commands->end()) {
		Commands->insert(std::make_pair(str, 0));
		return 0;
	}
	else
		return it->second;
	
}

void ProgramState::displayAll (ostream& outf) {

	if (Commands->empty()){
		outf << " ";
	}
	else {
		std::map<std::string, int>::iterator it;
		for(it = Commands->begin(); it != Commands->end(); ++it)
			outf << it->first << " " << it->second << std::endl;
	}
	
}

void ProgramState::addition(std::string str, std::string str1, const int& val) {

	std::map<std::string, int>::iterator it = Commands->find(str);

	if (it == Commands->end()) {// if 1st var is a new elem 

		if (str1 == " "){ // if var + digit
			Commands->insert(std::make_pair(str, val));
		}
		else {

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end()) { // if 2nd var is new elem 
				Commands->insert(std::make_pair(str, 0));
				Commands->insert(std::make_pair(str1, 0));
			}
			else { // if var + var

				// if 1st var is new, but 2nd var is found
				Commands->insert(std::make_pair(str, it1->second));
			}
		}
	
	}
	else { // if 1st var is found

		if (str1 == " ") { // if var + digit

			int new_val = it->second + val;
			(*Commands)[str] = new_val;
	
		}
		else if (str1 != " ") { // if var + var

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end())  // if 2nd var is a new, but 1st var is found
				Commands->insert(std::make_pair(str1, 0));
			else {

				int new_val = it->second + it1->second;
				(*Commands)[str] = new_val;
			}
		
		}

	}	
	
}

void ProgramState::subtraction(std::string str, std::string str1, const int& val) {

	std::map<std::string, int>::iterator it = Commands->find(str);

	if (it == Commands->end()) {// if 1st var is a new elem 

		if (str1 == " "){ // if var - digit
			Commands->insert(std::make_pair(str, (0 - val)));
		}
		else {

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end()) { // if 2nd var is new elem 
				Commands->insert(std::make_pair(str, 0));
				Commands->insert(std::make_pair(str1, 0));
			}
			else { // if var * var
				// if 1st var is new, but 2nd var is found
				Commands->insert(std::make_pair(str, (0 -it1->second)));
			}
		}
	
	}
	else { // if 1st var is found

		if (str1 == " ") { // if var - digit

			int new_val = it->second - val;
			(*Commands)[str] = new_val;
	
		}
		else if (str1 != " ") { // if var - var

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end())  // if 2nd var is a new, but 1st var is found
				Commands->insert(std::make_pair(str1, 0));
			else {

				int new_val = it->second - it1->second;
				(*Commands)[str] = new_val;
			}
		
		}

	}	

}


void ProgramState::multiplication(std::string str, std::string str1, const int& val) {

	std::map<std::string, int>::iterator it = Commands->find(str);

	if (it == Commands->end()) {// if 1st var is a new elem 

		if (str1 == " "){ // if var * digit
			Commands->insert(std::make_pair(str, 0));
		}
		else {

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end()) { // if 2nd var is new elem 
				Commands->insert(std::make_pair(str, 0));
				Commands->insert(std::make_pair(str1, 0));
			}
			else { // if var * var
				// if 1st var is new, but 2nd var is found
				Commands->insert(std::make_pair(str, 0));
			}
		}
	
	}
	else { // if 1st var is found

		if (str1 == " ") { // if var * digit

			int new_val = it->second * val;
			(*Commands)[str] = new_val;
	
		}
		else if (str1 != " ") { // if var * var

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end())  {// if 2nd var is a new, but 1st var is found
				Commands->insert(std::make_pair(str1, 0));
				(*Commands)[str] = 0;
			}
			else {

				int new_val = it->second * it1->second;
				(*Commands)[str] = new_val;
			}
		
		}

	}	
	
}


void ProgramState::division(std::string str, std::string str1, const int& val) {

	std::map<std::string, int>::iterator it = Commands->find(str);

	if (it == Commands->end()) {// if 1st var is a new elem 

		if (str1 == " "){ // if var / digit
			Commands->insert(std::make_pair(str, 0));
		}
		else {

			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end()) { // if 2nd var is new elem 
				setDivZero();
			}
			else { // if var / var
				// if 1st var is new, but 2nd var is found
				Commands->insert(std::make_pair(str, 0));
			}
		}
	
	}
	else { // if 1st var is found

		if (str1 == " ") { // if var / digit

			int new_val = it->second / val;
			(*Commands)[str] = new_val;
	
		}
		else if (str1 != " ") { // if var / var


			std::map<std::string, int>::iterator it1 = Commands->find(str1);

			if (it1 == Commands->end())  {// if 2nd var is a new, but 1st var is found
				setDivZero();
			}
			else {

				if (it1->second == 0)
					setDivZero();
				else {
					int new_val = it->second / it1->second;
					(*Commands)[str] = new_val;
				}
				
			}
		
		}

	}
	
}

void ProgramState::ifstatement(std::string varStr, std::string compStr, int compVal, int toLine) {

	std::map<std::string, int>::iterator it = Commands->find(varStr);

	if (it == Commands->end()) { // if it is a new elem
		Commands->insert(std::make_pair(varStr, 0));
	}
	
	if(compStr == "<") {

		if (it->second < compVal)
			executeLine(gotoLine(toLine));
		else
			executeLine(1);
	}
	else if(compStr == "<=") {

		if (it->second <= compVal)
			executeLine(gotoLine(toLine));
		else
			executeLine(1);
	}
	else if(compStr == ">") {

		if (it->second > compVal)
			executeLine(gotoLine(toLine));
		else
			executeLine(1);
	}
	else if(compStr == ">=") {

		if (it->second >= compVal)
			executeLine(gotoLine(toLine));
		else
			executeLine(1);
	}
	else if(compStr == "=") {

		if (it->second == compVal)
			executeLine(gotoLine(toLine));
		else
			executeLine(1);
	}
	else if(compStr == "<>") {

		if (it->second != compVal)
			executeLine(gotoLine(toLine));
		else
			executeLine(1); 
	}

}

void ProgramState::gosubStatement(int jumpTo) {

	int afterReturn = executeLine(0)-1;

	//push the line after GOSUB
	stackint.push(afterReturn);
	executeLine(gotoLine(jumpTo));
	
}

void ProgramState::returnStatement() {
 
	if (stackint.empty()) {
		setReturnError();
	}
	else {
		executeLine(gotoLine(stackint.top()));
		stackint.pop();
	}

}

void ProgramState::endProgram() {
	
	m_executedStatement = -1;
	delete Commands;
	Commands = NULL;
}

void ProgramState::setDivZero() {

	m_divZero = true;
}

bool ProgramState::divZero() {

	return m_divZero;
}

void ProgramState::setOutBound() {

	m_outBound = true;
}

bool ProgramState::outBound() {
	
	return m_outBound;
}

void ProgramState::setReturnError() {

	m_return = true;
}

bool ProgramState::getReturnError() {
	
	return m_return;
}


