Note for hw5

Debugger Window:
1. Default QListWidget highlighter is used for the visual cue to let the user know which line of code the interpreter has halted on.
2. [bp] is used for the visual cue to let the user know which
lines currently have breakpoints.
3. Choosing the same line where a breakpoint exists will remove the existing breakpoint
3. When debugger start, both QListWidgets set the starting point at row 0 by default.
4. Step and Next take the user to line 1 when there is no breakpoint placed anywhere.

5. When exception is encountered (ie: illegal jump condition, etc.), the program resets.

Value Window:
1. The variable and value is swapped when sorted by value


Homework 5 directories:
- Problem 1 is located in hw_chrysill/hw5
- Problem 3 is located in hw_chrysill/hw5/hw5q3
- Problem 4 is located in hw_chrysill/hw5/hw5q4

Problem 3

- .h file is stored in hw_chrysill/hw5/hw5q3/lib directory.
- hw5q3.cpp is stored in hw-chrysill/hw5/hw5q3

		How to compile problem 3: 
         1. change the directory to hw_chrysill/hw5/hw5q3
         2. type command: make	

Problem 4

- All .h files are stored in hw_chrysill/hw5/hw5q4/lib directory.
- All .cpp files (but Facile.cpp) are stored in hw_chrysill/hw5/hw5q4/src directory
- main.cpp is stored in hw-chrysill/hw5/hw5q4
- .pro file is generated already

        How to compile problem 4: 
         1. change the directory to hw_chrysill/hw5/hw5q4
         2. type command: qmake
         				  make	 