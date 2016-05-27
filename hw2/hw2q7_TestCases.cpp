
//Program: llistint class test cases (doubly linked list)
#include "llistint.h"
#include <iostream>

using namespace std;

int main() {

  LListInt * list = new LListInt();

  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }
  
  // Testing insert function
  cout << "\nTesting insert function\n";
  list->insert(0,1);
  list->insert(1,5);
  list->insert(2,7);


  if (list->get(0) == 1 && list->get(1) == 5 && list->get(2) == 7) {
    cout << "SUCCESS: Elements 1, 5, 7 are successfully inserted to the list." << endl;
  } else {
    cout << "FAIL: Insertion failed." << endl;
  }

  cout << "DISPLAYING: List after insertion \n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;
  
  //Inserting head
  list->insert(0,0);
  if (list->get(0) == 0) {
    cout << "SUCCESS: Inserting element from the front of the list" << endl;
  } else {
    cout << "FAIL: Failed to insert element from the front of the list." << endl;
  }

  cout << "DISPLAYING: List after inserting from the front of the list \n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }

  cout << endl << endl;

  //Inserting tail
  list->insert(list->size(),8);
  if (list->get(list->size()-1) == 8) {
  cout << "SUCCESS: Inserting element from the back of the list" << endl;
  } else {
    cout << "FAIL: Failed to insert element from the back of the list." << endl;
  }

  cout << "DISPLAYING: List after inserting from the back of the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //Inserting elements in certain positions" << endl;
  
  list->insert(2,2);
  if (list->get(2) == 2) {
  cout << "SUCCESS: Inserting element on position 2 in the list" << endl;
  } else {
    cout << "FAIL: Failed to insert element on postion 2 in the list." << endl;
  }

  cout << "DISPLAYING: List after inserting element on position 2 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //0 1 2 4 5 7 8

  list->insert(3,4);
  if (list->get(3) == 4) {
  cout << "SUCCESS: Inserting element on position 3 in the list" << endl;
  } else {
    cout << "FAIL: Failed to insert element on postion 3 in the list." << endl;
  }

  cout << "DISPLAYING: List after inserting element on position 3 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl<< endl;

  //0 1 2 4 5 6 7 8

  list->insert(5,6);
  if (list->get(5) == 6) {
  cout << "SUCCESS: Inserting element on position 5 in the list" << endl;
  } else {
    cout << "FAIL: Failed to insert element on postion 5 in the list." << endl;
  }

  cout << "DISPLAYING: List after inserting element on position 5 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //0 1 2 3 4 5 6 7 8
  list->insert(3,3);
  if (list->get(3) == 3) {
  cout << "SUCCESS: Inserting element on position 3 in the list" << endl;
  } else {
    cout << "FAIL: Failed to insert element on postion 3 in the list." << endl;
  }

  cout << "DISPLAYING: List after inserting element on position 3 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;
  int x = list->size();

  //Testing invalid location insertion
  list->insert(-1,5);
  list->insert(10,9);

  if (list->size() == x) {
  cout << "SUCCESS: Invalid insertion did not alter the list." << endl;
  } else {
    cout << "FAIL: Invalid insertion altered the list." << endl;
  }

   cout << "DISPLAYING: List after attempting to insert in invalid position of the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }

  cout << "\n\nTesting remove function \n";

  //"Removing head\n";
  list->remove(0);
  if (list->get(0) == 1) {
    cout << "SUCCESS: Removing element from the front of the list" << endl;
  } else {
    cout << "FAIL: Failed to remove element from the front of the list." << endl;
  }

  cout << "DISPLAYING: List after removing element from the front of the list \n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //Removing tail
  list->remove(list->size() - 1);
  if (list->get(list->size()-1) == 7) {
    cout << "SUCCESS: Removing element from the back of the list" << endl;
  } else {
    cout << "FAIL: Failed to remove element from the back of the list." << endl;
  }

  cout << "DISPLAYING: List after removing element from the back of the list \n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //1 2 3 4 5 6 7
  //Removing elements in certain positions\n";
  list->remove(2); //remove 3
  if(list->get(2) == 3) {
  cout << "SUCCESS: Removing element on position 2 in the list" << endl;
  } else {
    cout << "FAIL: Failed to remove element on postion 2 in the list." << endl;
  }

  cout << "DISPLAYING: List after removing element on position 2 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  // 1 2 4 5 6 7
  list->remove(4); //remove 6
  if(list->get(4) == 7) {
  cout << "SUCCESS: Removing element on position 4 in the list" << endl;
  } else {
    cout << "FAIL: Failed to remove element on postion 4 in the list." << endl;
  }

  cout << "DISPLAYING: List after removing element on position 4 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //1 2 4 5 7
  list->remove(1); //remove 2
  if (list->get(1) == 4) {
  cout << "SUCCESS: Removing element on position 1 in the list" << endl;
  } else {
    cout << "FAIL: Failed to remove element on postion 1 in the list." << endl;
  }

  cout << "DISPLAYING: List after removing element on position 1 in the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  // 1 4 5 7
  //Testing invalid location for removal
  list->remove(-1);
  list->remove(4);

  x = list->size();

  if (list->size() == x) {
  cout << "SUCCESS: Invalid removal did not alter the list." << endl;
  } else {
    cout << "FAIL: Invalid removal altered the list." << endl;
  }

  cout << "DISPLAYING: List after attempting to remove element in invalid position of the list\n";
  for (int i=-0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl << endl;

  //Removing the rest of the element in the list

  for (int i=0; i<x; i++) {
    list->remove(0);
  }

  if (list->size() == 0) {
  cout << "SUCCESS: Removing the rest of the elements from the list" << endl;
  } else {
    cout << "FAIL: The list is not empty" << endl;
  }

  cout << "DISPLAYING: The list after removing \n";
  for (int i=0; i < list->size(); i++) {
    cout << list->get(i) << " ";
  }
  cout << endl;

  if (list->empty()) {
    cout << "SUCCESS: List is now empty." << endl;
  } else {
    cout << "FAIL: List is not empty." << endl;
  }

  // Clean up memory.
  delete list;
  list = NULL;

}
