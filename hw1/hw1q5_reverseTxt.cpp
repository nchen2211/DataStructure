
//Project: Reversing text using dynamic memory allocation 

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int revText(ifstream& file)
{
	int size;

	if(!file.is_open())
		cout<< "The file is not open \n";
	else
	{
		string line;
		int i = 0;
		if(getline(file, line)) //we just want to read the first line for the total # of words
			stringstream(line) >> size;	

		string* revTxt = NULL;
		revTxt = new string[size];

		while(file >> line) //going through the .txt
		{
			revTxt[i] = line;
			i++;
		}

		for(i = size - 1; i >= 0; i--) {
			cout<<revTxt[i]<<endl;
		}

		delete [] revTxt;
		revTxt = NULL;

	}
	
	return 0;
}

int main(int argc, char* argv[])
{	
	if(argc < 2){
		cerr<< "Please provide an input file." << endl;
		return 1;
	}

	ifstream inputFile (argv[1]);

	revText(inputFile);

	return 0;
}


