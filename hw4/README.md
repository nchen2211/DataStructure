Note for hw4

1. PrintStatement and PrintAllStatement execute() return 0 if the key does not exist
2. Uninitialized variable is created as a new variable with value of 0 if it's called by PRINT, IF, ADD, SUB, MULT, DIV (excepetion for a second variable, such as B in DIV A B)
3. I added a function called deallocation(vector<Statement*>, ProgramState*) to deallocate memories

Homework 4 directories:
- All .h files are stored in hw_chrysill/hw4/lib direcoty.
- All .cpp files (but Facile.cpp) are stored in hw_chrysill/hw4/src directory
- All .o and .exe is in hw_chrysill/hw4/exe directory (the directory will be generated through the makefile)
- Facile.cpp, makefile, README.md are stored in hw-chrysill/hw4


        How to compile: 
         1. change the directory to hw_chrysill/hw4
         2. type command: make
         3. Both of the following commands work for executing the program (redirecting output):
         	a) ./exe/hw4     
         	b) ./exe/hw4 > [output filename] 

         	Note: 
         		for a) After type in the command, the program will prompt the user to enter the input file name, then hit Enter.
         		for b) After type in the command, type in the input file name on the terminal, then hit Enter.
