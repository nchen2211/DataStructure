#include "lib/llistint.h"
#include "gtest/gtest.h"
#include <iostream>
using namespace std;

TEST (LLtest, CopyConstructor) {

	LListInt *list = new LListInt();

	int loc = 0;
	for (int i=-0; i < 9; ++i) {
	  list->insert(loc,i);
	  ++loc;
	}

	LListInt copyList (*list);
	//testing deep copy
	EXPECT_EQ(copyList.get(0),0);
	EXPECT_EQ(copyList.get(8),8);
	EXPECT_EQ(copyList.get(3),3);

	EXPECT_EQ(copyList.size(),9);

	delete list;
	list = NULL;
}

TEST (LLtest, AssignmentOperator) {

	LListInt *list1 = new LListInt();
	LListInt *list2 = new LListInt();

	// test assign to an empty list
	int loc = 0;
	for (int i=-0; i < 6; ++i) {
	  list1->insert(loc,i);
	  ++loc;
	}

	*list2 = *list1;
	EXPECT_EQ(list2->size(), 6);


	// test assign if size of 'this' < size of 'other'
	LListInt list3;
	loc = 0;

	for (int i=10; i < 19; ++i) {
	  list3.insert(loc,i);
	  ++loc;
	}

	*list1 = list3;
	EXPECT_EQ(list1->size(), 9);

	EXPECT_EQ(list1->get(0),10);
	EXPECT_EQ(list1->get(8),18);
	EXPECT_EQ(list1->get(5),15);


	// test assign if size of 'this' > size of 'other'
	list2->remove(0);
	list2->remove(1);
	list2->remove(3);

	*list2 = *list1;

	EXPECT_EQ(list2->size(), 9);

	EXPECT_EQ(list2->get(0),10);
	EXPECT_EQ(list2->get(8),18);
	EXPECT_EQ(list2->get(2),12);

	delete list1;
	list1 = NULL;

	delete list2;
	list2 = NULL;

}


TEST (LLtest, AppendingOperator) {

	LListInt listA;
	LListInt listB;

	int loc = 0;
	for (int i=-0; i < 3; ++i) {
	  listA.insert(loc,i);
	  ++loc;
	}
	// 0 1 2
	loc = 0;
	for (int i=10; i < 15; ++i) {
	  listB.insert(loc,i);
	  ++loc;
	}

	LListInt appendedList;
	appendedList = listB + listA;

	EXPECT_EQ(appendedList.size(),8);

	EXPECT_EQ(appendedList.get(0),10);
	EXPECT_EQ(appendedList.get(7),2);
	EXPECT_EQ(appendedList.get(2),12);
	EXPECT_EQ(appendedList.get(5),0);

	// testing appending a list with an empty list
	LListInt emptyList;

	emptyList = listA + emptyList;

	EXPECT_EQ(emptyList.size(),3);

	EXPECT_EQ(emptyList.get(0),0);
	EXPECT_EQ(emptyList.get(1),1);
	EXPECT_EQ(emptyList.get(2),2);
	
}

TEST (LLtest, accessOperator) { 

  LListInt * list = new LListInt();

	int loc = 0;
	for (int i=-0; i < 9; ++i) {
	  list->insert(loc,i);
	  ++loc;
	}

  int element;
  element = (*list)[3];
  
  EXPECT_EQ(element,3);

  delete list;
  list = NULL;

}