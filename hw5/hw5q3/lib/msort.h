#include <vector>
#include <iostream>
#include <math.h>

template <class T>
struct comparatorAsc {
    bool operator()(const T& lhs, const T& rhs) 
    { 
      return lhs < rhs; 
    }
};

template <class T>
struct comparatorDesc {
    bool operator()(const T& lhs, const T& rhs) 
    { 
      return lhs > rhs; 
    }
};


template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp){
	mergeSortHelper(myArray, 0, myArray.size()-1, comp);
}


template <class T, class Comparator>
void mergeSortHelper(std::vector<T> &myArray, int l, int r, Comparator comp){
		
	if (l < r){

		int m = floor ((l+r)/2);
		mergeSortHelper(myArray, l, m, comp);
		mergeSortHelper(myArray, m+1, r, comp);
		merge(myArray, l, r, m, comp);
	}
}

template <class T, class Comparator>
void merge (std::vector<T> &myArray, int l, int r, int m, Comparator comp){

	std::vector<T> temp; 
	int i = l; 
	int j = m+1;

	while (i <= m || j <=r) {
		
		if (i <=m && (j > r || comp(myArray.at(i), myArray.at(j)))) {
			
			temp.push_back(myArray.at(i));
			i++;
		}
		else{

			temp.push_back(myArray.at(j));
			j++;
		}
	}

	for(int k=0; k < r-l+1; k++)
		myArray.at(l+k) = temp.at(k);

}
