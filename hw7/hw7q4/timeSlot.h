#ifndef TimeSlot_H
#define TimeSlot_H
#include <vector>
#include <string>
#include <iostream> 
#include <istream> 
#include <fstream>
#include "avlbst.h"

class TimeSlot{

public:
	TimeSlot();
	~TimeSlot();
	void readFile(std::istream&);
	bool isValid(int, int);
	bool scheduling(int, int); //backtracking function
	
private:	
	int totalExam;
    int totalStudent;
    int totalSlot;

	int **scheduleTable;
	std::vector<int> course;
    AVLTree<int, int> avltree;
};

#endif