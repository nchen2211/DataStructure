#include "lib/stackint.h"
#include <iostream>


int main() {

	StackInt *StackList = new StackInt();

	if (StackList->empty()){
		std::cout << "SUCCESS: Stack is initally empty\n";
	} else {
		std::cout << "FAILED:  Stack is not initally empty\n";
	}


	std::cout << "TESTING PUSH\n";
	for(int i = 88; i < 93; i++) {

		StackList->push(i);
		std::cout << "pushing: " << i << std::endl;
	}

	if (!StackList->empty()) {
		std::cout << "SUCCESS:  Element(s) were successfully inserted into the stack\n"; 
	} else {
		std::cout << "SUCCESS:  Element(s) were not inserted into the stack\n"; 
	}


	std::cout << "TESTING TOP\n";
	if(StackList->top() == 92) {
		std::cout << "SUCCESS:  The top element is correct\n"; 
	} else {
		std::cout << "FAILED:  The top element is incorrect\n"; 
	}
	

	std::cout << "TESTING REMOVE\n";
	while (!StackList->empty()){

		std::cout << "DISPLAYING: Current top: " << StackList->top() << std::endl;
		StackList->pop();
	}

	if(StackList->empty()) {
		std::cout << "SUCCESS: Stack is emptied. All element(s) were popped.\n";
	} else {
		std::cout << "FAILED:  Stack is not emptied yet\n";
	}


	// the following is to test the destructor if 
	//it pops all the element in stack and all memories are deallocated
	StackInt *StackList1 = new StackInt();

	std::cout << "TESTING PUSH\n";

	for(int i = 15; i < 18; i++) {

		StackList1->push(i);
		std::cout << "pushing: " << i << std::endl;
	}

	StackList1->pop();
	StackList1->pop();

	std::cout << "REMAINING ELEMENT IN THE STACK (to test memory leak after calling a destructor)\n";
	if(StackList1->top() == 15) {
		std::cout << "SUCCESS: One element remained in the stack\n";
	} else {
		std::cout << "FAILED: More than one element remained in the stack\n";
	}

	delete StackList;
	StackList = NULL;

	delete StackList1;
	StackList1 = NULL;
	
	return 0;

}