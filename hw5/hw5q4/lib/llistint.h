#ifndef LLISTINT_H
#define LLISTINT_H

class LListInt {
 public:
  struct Item {
    int val;
    Item *prev;
    Item *next;
  };

  // def constructor
  LListInt(); 
  ~LListInt();
  LListInt(const LListInt& other);
  int size() const;
  bool empty() const;
  void insert(int pos, const int& val);
  void remove(int pos);
  void set(int pos, const int& val);
  int& get(int pos);
  int const & get(int pos) const;
  void clear();


 private:
  //Returns a pointer to the item at index, pos and NULL for an invalid position
  Item* getNodeAt(int pos) const;

  //Data members
  Item* head_;
  Item* tail_;
  int size_;
};

#endif