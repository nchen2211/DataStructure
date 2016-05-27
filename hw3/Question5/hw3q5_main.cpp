#include "lib/stackint.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

const int OPEN_PAREN = -1;
const int SHIFT_R = -3;
const int SHIFT_L = -4;
const int ADD = -5;
const int MULT = -6;

using namespace std; 


int main(int argc, char* argv[])
{	

	if(argc < 2){
		cerr<< "Please provide an input file." << endl;
		return 1;
	}

	ifstream inputFile (argv[1]);

	if (!inputFile.is_open())
		cout<< "The file is not open \n";
	else {
		
		string line;
		StackInt stackExp;
		string malf;
		int openCount, closeCount, addCount, multCount;

		while (getline(inputFile,line)) {

			malf = " ";
			openCount = 0; closeCount = 0; addCount = 0; multCount = 0;
			char c;

			for (unsigned int i=0; i<line.length(); ++i) {

				c = line.at(i);
			
				if (c != ' ') { //ignoring white space

					if (c == '(') {
						stackExp.push(OPEN_PAREN);
						++openCount;
					}
					else if (c == '<') {
						stackExp.push(SHIFT_L);
					}
					else if (c == '>') {
						stackExp.push(SHIFT_R);
					}	
					else if (c == '+') {
						++addCount;
						stackExp.push(ADD);
					}	
					else if (c == '*') {
						++multCount;
						stackExp.push(MULT);
					}
					else if (c == ')') {

						//evaluating expression
						int mult_10 = 1;
						int operand_checker = 0;
					
						int count_ADD = 0; 
						int count_MULT = 0;

						long temp = 0;
						long num = 0;
						long result = 0;

						int add_in_paren = 0;
						int mult_in_paren = 0;

						++closeCount;

						if (openCount < closeCount)
							malf = "Malformed";
						else if (openCount >= closeCount) {

							while (stackExp.top() != OPEN_PAREN) {

								if (stackExp.top() < 0) {

									if (stackExp.top() == ADD) {

										++count_ADD;
										++add_in_paren;
									}
									else if (stackExp.top() == MULT) {
										
										++count_MULT;
										++mult_in_paren;
									}

									stackExp.pop(); //if operators
								}
								else { // if top() is a digit

									//processing operand with mult of 10
									temp = 0;

									while (stackExp.top() >= 0) {
									
										temp += (stackExp.top() * mult_10);	
										mult_10 *= 10;
											
										stackExp.pop();
									}

									++operand_checker;
								
									if (operand_checker == 1) {
										num = temp;
									}
									else if (operand_checker == 2) {
										result = temp;
									}
									
									//double or half the operand
									if (stackExp.top () == SHIFT_L  || stackExp.top () == SHIFT_R) {

										while (stackExp.top () != ADD && stackExp.top() != MULT && stackExp.top() != OPEN_PAREN) {

											if (stackExp.top() == SHIFT_L) {
									
												if (operand_checker == 1) 
													num *= 2;
												else if (operand_checker == 2)
													result *= 2;
												
											}
											else if (stackExp.top() == SHIFT_R) {

												if (operand_checker == 1)
													num /= 2;
												else if (operand_checker == 2)
													result /= 2;	
											}

											stackExp.pop(); // pop SR / SL

										} // end while < >

									} // end if for < >


									// processing arithmetic
									if (count_ADD == 1) {
										result = num + result;
										count_ADD = 0;
										num = result;
										operand_checker = 1;
									}
									else if (count_MULT == 1) {
										result = num * result;
										count_MULT = 0;
										num = result;
										operand_checker = 1;
									}
									else
										result = num;


									//check Malformed within the parentheses
									if (add_in_paren > 0 && mult_in_paren > 0)
										malf = "Malformed";

								}

							// resetting mult_10 and operand_checker

								mult_10 = 1; 

							} // end until OPEN_PAREN

							if (stackExp.top() == OPEN_PAREN)
								stackExp.pop(); // popping OPEN PAREN


							stackExp.push(result);	

						}	

						if (count_ADD > 0 || count_MULT > 0)
							malf = "Malformed";
						
					}
					else { // if numbers

						int num = c - '0'; // "converting" char to int
						stackExp.push(num);
					}

				} // end if (white space)

				if (i == line.length() - 1) { //when it reaches the end of string

					int last_operand = stackExp.top();
					int mult_ten = 1;
					
					stackExp.pop();

					while (!stackExp.empty()) {

						if (stackExp.top() == SHIFT_L) 
							last_operand *= 2;
						else if (stackExp.top() == SHIFT_R)
							last_operand /= 2;
						else if (stackExp.top() >= 0) {
							mult_ten *= 10;
							last_operand += (stackExp.top() * mult_ten);
							
						}
						else if (addCount > openCount && addCount > closeCount) {
							malf = "Malformed";
						}
						else if (multCount > openCount && multCount > closeCount) {
							malf = "Malformed";
						}
						else if (stackExp.top() == OPEN_PAREN) 
							malf = "Malformed";

						stackExp.pop();
					}

					if (malf == "Malformed") 
						cout << malf << endl;
					else
						cout << last_operand << endl;
				}

			} // end for loop per line


		} //end while loop 

		cout << endl;

	} // end else 
		
	return 0;
}
