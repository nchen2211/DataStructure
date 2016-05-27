#include "lib/msort.h"
#include <stdlib.h> 

int main(){

	std::vector<int> vect;
	comparatorAsc<int> comp;

	int rand_num;

	std::cout << "Sorting Integers" << std::endl;
	std::cout << "Before sorting" << std::endl;
	for(int i = 0; i < 10; i++){
		rand_num = rand() % 100 + 1;
		vect.push_back(rand_num);
		std::cout << vect.at(i) << " ";
	}

	mergeSort(vect, comp);
	std::cout << "\n\nAfter sorting- ascending" << std::endl;
	for(int i = 0; i < 10; i++){
		std::cout << vect.at(i) << " ";
	}

	comparatorDesc<int> comp0;
	mergeSort(vect, comp0);
	std::cout << "\n\nAfter sorting- ascending" << std::endl;
	for(int i = 0; i < 10; i++){
		std::cout << vect.at(i) << " ";
	}

	std::cout << "\n\nSorting Alphabets" << std::endl;
	std::cout << "Before sorting" << std::endl;
	std::string name[] = {"HERMIONE", "SEVERUS", "FRED", 
                   "ALBUS", "GEORGE", "GINNY", 
                   "MINERVA", "BILL", "HARRY", 
                   "SIRIUS", "DOLORES", "GRINDELWALD", "LUNA", "HORACE"};
	
	std::vector<std::string> vect1;
	comparatorAsc<std::string> comp1;

	for (int i = 0; i< 14; i++) { 
		vect1.push_back(name[i]);
		std::cout << vect1.at(i) << " ";
    }

    mergeSort(vect1,comp1);

    std::cout << "\n\nAfter sorting - ascending" << std::endl;
	for(int i = 0; i < 14; i++){
		std::cout << vect1.at(i) << " ";
	}

	std::vector<std::string> vect2;
	comparatorDesc<std::string> comp2;

	for (int i = 0; i< 14; i++) { 
		vect2.push_back(name[i]);
		std::cout << vect2.at(i) << " ";
    }

    mergeSort(vect2,comp2);

    std::cout << "\n\nAfter sorting - descending" << std::endl;
	for(int i = 0; i < 14; i++){
		std::cout << vect2.at(i) << " ";
	}


}