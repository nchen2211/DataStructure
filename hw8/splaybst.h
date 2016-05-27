#ifndef SPLAYBST_H
#define SPLAYBST_H

#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Map.h"

class SplayNode {
public:
	SplayNode(const std::string & k, const int & v, SplayNode *p)
    : _item(k, v)
    // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }

    ~SplayNode(){}
    std::pair<const std::string , int> const& getItem () const
    	{ return _item; }
  
	std::pair<const std::string , int>& getItem ()
		{ return _item; }

	const std::string& getKey () const
		{ return _item.first; }

	const int& getValue () const
		{ return _item.second; }

	SplayNode* getParent() const
		{ return _parent; }

	SplayNode *getLeft () const
    	{ return _left; }
  
    SplayNode *getRight () const
    	{ return _right; }


	void setParent (SplayNode *p)
		{ _parent = p; }

	void setLeft (SplayNode *l)
		{ _left = l; }

	void setRight (SplayNode *r)
		{ _right = r; }

	void setValue (const int &v)
		{ _item.second = v; }

protected:
  std::pair<const std::string, int> _item;
  SplayNode *_left, *_right, *_parent;

};

/* -----------------------------------------------------
 * Splay Tree
 ------------------------------------------------------*/

class SplayTree : public Map
{
public:
  
  SplayTree() { root = NULL; }
  ~SplayTree() { deleteAll (root); }

  virtual void add(const std::string& word);
  virtual void reportAll(std::ostream& output);
  void tolower(std::string word);

  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

 class iterator {
  public:

    // Initialize the internal members of the iterator
    iterator(SplayNode* ptr)
    	{ curr = ptr; }
    
    std::pair<const std::string,int>& operator*() // 
     	{ return curr->getItem(); }
    
    std::pair<const std::string,int>* operator->() 
      	{ return &(curr->getItem()); }
     
    // Checks if 'this' iterator's internals have the same value as 'rhs'
    bool operator==(const iterator& rhs) const
      	{ return (curr == rhs.curr); }
    
    // Checks if 'this' iterator's internals have a different value as 'rhs'  
    bool operator!=(const iterator& rhs) const
      	{ return (curr != rhs.curr); }

    // Advances the iterator's location using an in-order sequencing 
    iterator& operator++();
    
    
  protected:
    SplayNode* curr;

  }; // end iterator

	iterator begin(); 
	iterator end();

 protected:
 	SplayNode* root;
 	SplayNode* internalFind(const std::string& k) const;
 	void printRoot (SplayNode *r) const;
	void deleteAll (SplayNode *r);
	

private:

	SplayNode* zig(SplayNode* parent);
	SplayNode* zag(SplayNode* parent);
	SplayNode* zigzig(SplayNode* grandparent);
	SplayNode* zagzag(SplayNode* grandparent);
	SplayNode* zigzag(SplayNode* grandparent);
	SplayNode* zagzig(SplayNode* grandparent);

	void setGreatGrandParent(SplayNode* grandparent,SplayNode* temp_gparent);
	void splay(SplayNode* curr, SplayNode* parent);


};

#endif