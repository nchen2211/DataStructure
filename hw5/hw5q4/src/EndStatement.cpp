#include "../lib/EndStatement.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

void EndStatement::execute(ProgramState *state, ostream &outf) {

	state->endProgram();
	state->setEndProgram(1);
}