#include "../lib/llistint.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
  
   Item *temp;//

   //insert at front
   if(loc == 0) {

      temp = new Item;
      temp->val = val;

      if (head_ == NULL && tail_ == NULL) {  //if the list is empty  

        temp->prev = NULL;
        head_ = temp;
        tail_ = temp;
        tail_->next = NULL;

      }
      else { // if the 

        temp->prev = NULL;
        head_->prev = temp;
        temp->next = head_;
        head_ = temp;

      }

      size_++;
   }
   // insert from back
   else if (loc == size_) {

      temp = new Item;
      temp->val = val;
      temp->next = NULL;

      tail_->next = temp;
      temp->prev = tail_; //delete this
      tail_ = temp;
      size_++;
   }

   else {

      Item* nodeDest = getNodeAt(loc);

      if (nodeDest == NULL) {
        cout << "ERROR: Invalid position: no location " << loc << " in the list" << endl;
      }
      else {

          temp = new Item;
          temp->val = val;  
          Item* curr = head_;

          while (curr->next != nodeDest) {
            curr = curr->next;
          }

          //update left pointer
          curr->next = temp;
          temp->prev = curr;

          //update right pointer
          temp->next = nodeDest;
          nodeDest->prev = temp;

          size_++;
      }
    
    }
       
} // end insert function

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  Item *temp;

  if (loc == 0) { //remove head
    
    if (head_ == tail_) { //if the list only have 1 elem

         temp = head_;
         head_ = NULL;
         tail_ = NULL;

    }
    else { // if the list have more than 1 elem

      temp = head_;
      head_ = head_->next; 
      head_->prev = NULL;

    }

    size_--;
    delete temp;
   
  }
  else if (loc == size_ - 1) { //removing tail
    
    temp = tail_;
    tail_ = tail_->prev;
    tail_->next = NULL;
    delete temp;


    size_--;
  }
  else {

    Item *nodeDest = getNodeAt(loc);

    if (nodeDest == NULL) {

      cout << "Invalid position: no location " << loc << " in the list" << endl;
    }
    else {

      temp = head_;
      Item *del;

      while (temp->next != nodeDest) {
        temp = temp->next;
      }

      del = temp->next;
      temp->next = del->next;
      del->next->prev = temp;

      size_--;

      delete del;
      
    }

  }

}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
     cout << "The stack is empty\n";
  }

  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{

  if(loc < 0 || loc >= size()) {

    return NULL;
  }
  else {

    int counter = 0;
    Item* nodeAt = head_;

    while(counter != loc) {
      nodeAt = nodeAt->next;
      counter++;
    }

    return nodeAt;

  }

}
