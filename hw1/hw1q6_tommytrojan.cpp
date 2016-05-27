
//Project: Memory allocation/deallocation of 3D array 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int main(int argc, char* argv[])
{
  if(argc < 2) {
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int floors;
  int *floorsizes;
  string ***trojans;
  string curr;
 
  input >> floors;
  trojans = new string**[floors];

  //keep track of how many people are on each floor.
  floorsizes = new int[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
  }

  int line = 0;

  while(getline(input, curr)) {

	  stringstream ss;
	  ss << curr;
	  ss >> curr;

	  if (curr == "MOVEIN") {

		  int i,k;
		  int x;
		  int count = 0;
		  
		  //conditions for command errors 
		  while (!ss.fail()) {
		  	ss >> x;
		  	if(count == 0) {
		  		i = x;
		  	}
		  	else if (count == 1) {
		  		k = x;
		  	}
		  	count++;
		  }

		  if(count != 3) {
		  		output << "Error - incorrect MOVEIN command" << endl;
		  		i = 0; k = 0;
		  }
		  else if (count == 3) {

		  		if (i < 0 || i > floors - 1) {
		  			output<< "Error - floor " << i << " does not exist" << endl;
		  		}
		  		else if (floorsizes[i] > 0) {
		  			output<< "Error - floor " << i << " is not empty" << endl;
		  		}
		  		else {

		  			floorsizes[i] = k; 
		  			trojans[i] = new string* [k];
		  			output << k << " students move in to level " << i << endl;

		  			//point all potential student possession to NULL
		  			for (int n = 0; n < k; n++) {
		  				trojans[i][n] = NULL; 
		  			}
			  	}		
		  	}
		} //end MOVEIN

		else if (curr == "MOVEOUT") {

 	  	  int i, x;
 	  	  int count = 0;

 	  	  //conditions for command errors
		  while (!ss.fail()) {
		  	ss >> x;
		  	if(count == 0) {
		  		i = x;
		  	}
		  	count++;
		  }
 	  	 
 	  	  if(count != 2) {
 	  	  		output << "Error - incorrect MOVEOUT command" << endl;
 	  	  }
 	  	  else {
 	  	  		if(i < 0 || i > floors - 1) {
		  			output<< "Error - floor " << i << " does not exist" << endl;
 	  	  		}
		  		else if(floorsizes[i] == 0) {
		  			output<< "Error - floor " << i << " is empty" << endl;
		  		}
		  		else {

		  			//deleting trojans floorsizes & their possessions
		  			for(int n = 0; n < floorsizes[i]; n++) {
		  				delete [] trojans[i][n];
		  			}

		  			delete trojans[i];
		  			trojans[i] = NULL; // set i-th level to NULL
		  			
		  			output << floorsizes[i] << " students move out from level " << i << endl;
		  			floorsizes[i] = 0;
		  		}
 	  	  	}
	 	 } //end MOVEOUT

		  else if (curr == "OBTAIN") {

		  	int i,j,k,x;
		  	string poss;
		  	int count = 0;

		  	ss >> i;
		  	ss >> j;
		  	ss >> k;
	 		
			if (ss.fail()) {
				output << "Error - incorrect OBTAIN command" << endl;
			}
			else {

		 	 	if (i < 0 || i > floors - 1) {
			  	output << "Error - floor " << i << " does not exist" << endl;
				}
				else if (j < 0 || j > floorsizes[i]) {
					output << "There is no student " << j << " on " << i << " floor" << endl;
				}
				else if (trojans[i][j] != NULL) {
					output << "Student " << j << " on " << i << " floor already has possessions" << endl;
				}
				else {

					int numPoss = -1;
					//allocating memory for possession
					trojans[i][j] = new string [k+1];

					//assigning possessions to a specific student

					for (int n = 0; n <= k; n++) {
						ss >> poss;
						trojans[i][j][n] = poss;
						numPoss++;

						if(n == k) {
							trojans[i][j][n] = "end possessions"; //to idicate the last possession
						}

					}

					output << "Student " << j << " on " << i << " have " << numPoss << " possessions" << endl;
		  		}
		  	}
		  	
		  } //end OBTAIN

		  else if (curr == "OUTPUT") {

		  	int i,j,x;
		  	int n = 0;
		  	int count = 0;

		  	//conditions for command error
		  	while (!ss.fail()) {
			  	ss >> x;
			  	if (count == 0) {
			  		i = x;
			  	}
			  	else if (count == 1) {
			  		j = x;
			  	}
			  	count++;
		 	 }

		  	if (count != 3) {
		  		output << "Error - incorrect OUTPUT command" << endl;
	 	  	}
	 	  	else if (count == 3) {

		 	  	if (i < 0 || i > floors - 1) {
				  	output << "Error - floor " << i << " does not exist" << endl;
				}
				else if (j < 0 || j > floorsizes[i]) {
					output << "There is no student " << j << " on floor " << i << endl;
				}
				else if (trojans[i][j] == NULL) {
					output << "Student " << j << " on floor " << i << " does not have any possessions" << endl;
				}
				else {
					output << "The possessions of student " << j << " from floor " << i << endl;	
					while (trojans[i][j][n] != "end possessions") {
						output << trojans[i][j][n] << endl;
						n++;
					}
				}
			}

		}// end OUTPUT	 
		else if(line == 0); 
		else {
		  	output << "Error - incorrect command" << endl;
		}

		line++;
 
 	} // end while loop

 //deleting i-th floorsizes
 for(int i = 0; i < floors; i++) {
	 for(int n = 0; n < floorsizes[i]; n++) {
		delete [] trojans[i][n];
	}

	delete[] trojans[i];
	trojans [i] = NULL;
	
 }

 // delete 3D array
 delete[] trojans;
 trojans = NULL;

 delete[] floorsizes;
 floorsizes = NULL;
 
 return 0;
	
} // end main