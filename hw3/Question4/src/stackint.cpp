#include "../lib/stackint.h"
#include <iostream>

  StackInt::StackInt() 
  {

  //    list.clear();
     
  }

  StackInt::~StackInt() {

    while (!empty()) { 
      pop(); 
    }

  }

  bool StackInt::empty() const {

    if (list.size() == 0) {
      return true;
    }
    else {
       return false;
    }

  }

  void StackInt::push (const int& val) {

    list.insert(list.size(),val);

  }

  int const& StackInt::top() const {

      return list.get(list.size()-1); 
  }

  void StackInt::pop() {

    list.remove(list.size()-1);

  }