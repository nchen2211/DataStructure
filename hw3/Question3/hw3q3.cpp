#include "lib/llistint.h"
#include <iostream>

using namespace std;

int main() {

  LListInt * list = new LListInt();

  int loc = 0;
  for (int i=-0; i < 9; ++i) {
    list->insert(loc,i);
    ++loc;
  }

  cout << "DISPLAYING: Original list after inserting\n";
  for (int i=-0; i < list->size(); ++i) {
    cout << list->get(i) << " ";
  }
  cout <<  endl << endl;

  // testing copy constructor
  LListInt copyList(*list);

  cout << "\nDISPLAYING: Copy constructor list\n";
  for (int i=-0; i < copyList.size(); ++i) {
    cout << copyList.get(i) << " ";
  }
  cout << "\nCOPY LIST SIZE: " << copyList.size() << endl;
  cout << endl << endl;
  
  // testing assignment overloading

  cout << "TESTING ASSIGNMENT OPERATOR OVERLOADING FUNCTION\n";
  LListInt assignList;
  loc = 0;
  for (int i=10; i < 19; ++i) {
    assignList.insert(loc,i);
    ++loc;
  }

  cout << "DISPLAYING: List A \n";
  for (int i=-0; i < 9; ++i) {
    cout << assignList.get(i) << " ";
  }
  cout <<  endl;

  assignList = *list;

  cout << "DISPLAYING: List A after assignment overloading\n";
  for (int i=-0; i < assignList.size(); ++i) {
    cout << assignList.get(i) << " ";
  }
  cout << "\nAssigned list size: " << assignList.size() << endl;
  cout <<  endl << endl;

  // testing addition overloading
  loc = 0;
  for (int i=10; i < 19; ++i) {
    copyList.set(loc,i);
    ++loc;
  }

  cout << "TESTING CONCATENTATION OPERATOR OVERLOADING FUNCTION\n";
  cout << "DISPLAYING: List B\n";
  for (int i=-0; i < copyList.size(); ++i) {
    cout << copyList.get(i) << " ";
  }
  cout << "\nDISPLAYING: List C\n";
  for (int i=-0; i < list->size(); ++i) {
    cout << list->get(i) << " ";
  }

  LListInt appendedList;

  appendedList = copyList + *list;

  cout << "\nDISPLAYING: Appended list\n";
  for (int i=-0; i < appendedList.size(); ++i) {
    cout << appendedList.get(i) << " ";
  }
  cout << "\nAppended list size: " << appendedList.size() << endl << endl;


  cout << "TESTING ACCESS OPERATOR OVERLOADING FUNCTION\n";  
  int element;
  element = (*list)[3];
  cout << "Element is: " << element << endl;


   // Clean up memory.
  delete list;
  list = NULL;

}