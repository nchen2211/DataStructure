
//Program: merge 2 sorted linked list using recursion

#include <iostream>
using namespace std;


struct Node {	
	int value;
	Node *next;
};

void clear (Node*& head) {

	Node* del = head;
	Node* curr;

	while (del != NULL) {
		curr = head;
		head = head->next;
		delete curr;
		del = head;
	}

}

Node* merge (Node*& first, Node*& second) {

	Node* mergeList;

	if (first == NULL) {
		return second;
	}
	else if (second == NULL) {
		return first;
	}
	else if (first->value <= second->value) {
		mergeList = first;
		
		mergeList->next = merge (first->next, second);
	}
	else if (first->value > second->value) {
		mergeList = second;
		mergeList->next = merge (first, second->next);
	}


	first = NULL;
	second = NULL;

  	return mergeList;

  }