#include "hashtable.h"
#include "splaybst.h"
#include <fstream>
#include <sstream>
#include <ctime>

int main(int argc, char* argv[])
{	
	if(argc < 2) {
		std::cerr << "Please provide an option followed by an input file." << std::endl;
		return 1;
	}

    char* option(argv[1]);
	std::ifstream infile (argv[2]);
    
	if (!infile) {
        std::cerr << "Cannot open " << infile << "!" << std::endl;
        return 1;
    }

    std::stringstream ss;
    std::string word;
    std::ofstream output;
    
    clock_t start;
    double duration;
    start = clock();
   
    if (*option == '4')
    {
        SplayTree splaytree;

        while (infile >> word)
            splaytree.tolower(word);

        output.open ("splaytree_output.txt");
        splaytree.reportAll(output);
        output.close();

    }
    else if (*option == '5')
    {
        Hashtable *hashtable = new Hashtable;

        while (infile >> word)
            hashtable->add(word);

        output.open ("hashtable_output.txt");
        hashtable->reportAll(output);
        output.close();
        
        delete hashtable;
        hashtable = NULL;
    }

   duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
   std::cout << duration << std::endl;
   
    return 0;

}