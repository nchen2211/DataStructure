#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

//using namespace std;

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
    { return _item.first; }
  
  const ValueType & getValue () const
    { return _item.second; }
  
  /* the next three functions are virtual because for AVL-Trees,
     we'll want to use AVL nodes, and for those, the
     getParent, getLeft, and getRight functions should return 
     AVL nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;

};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  // constructor
  BinarySearchTree () { root = NULL; }

  // destructor
  ~BinarySearchTree () { deleteAll (root); }
  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

  // delete this after
  void insert(Node<KeyType,ValueType>* new_node)
  {
      if (root == NULL)
      {
          new_node = new Node<KeyType,ValueType>(new_node->getKey(),new_node->getValue(),NULL);
          root = new_node;
      }
      else 
      {
          Node<KeyType,ValueType>* parent;
          Node<KeyType,ValueType>* curr;
          curr = root;
          while (curr != NULL)
          {
              if (new_node->getKey() < curr->getKey())
              {
                  parent = curr;
                  curr = curr->getLeft();
              }
              else 
              {
                  parent = curr;
                  curr = curr->getRight();
              }
          }

          new_node = new Node<KeyType,ValueType>(new_node->getKey(), new_node->getValue(),parent);
          new_node->setLeft(NULL);
          new_node->setRight(NULL);

          if (new_node->getKey() < parent->getKey())
              parent->setLeft(new_node);
          else
              parent->setRight(new_node);
      }
  }

  class iterator {
  public:

    // Initialize the internal members of the iterator
    iterator(Node<KeyType,ValueType>* ptr)
    {
      curr = ptr;
    }
    
    std::pair<const KeyType,ValueType>& operator*() 
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
     
    // Checks if 'this' iterator's internals have the same value as 'rhs'
    bool operator==(const iterator& rhs) const
    {
        return (curr == rhs.curr);
    }
    
    // Checks if 'this' iterator's internals have a different value as 'rhs'  
    bool operator!=(const iterator& rhs) const
    {
        return (curr != rhs.curr);
    }

    // Advances the iterator's location using an in-order sequencing 
    iterator& operator++() 
    {
        if (curr->getRight() != NULL)
        {
            curr = curr->getRight();

            while(curr->getLeft() != NULL)
              curr = curr->getLeft();
        }
        else if (curr->getRight() == NULL)
        {
            Node<KeyType, ValueType>* parent = curr->getParent();

            while(parent != NULL && curr == parent->getRight())
            {
                curr = parent;
                parent = curr->getParent();
            }

            curr = parent;
        }

      return *this;
    }
    
  protected:
    Node<KeyType, ValueType>* curr;

  }; // end iterator
  
  // Returns an iterator to the "smallest" item in the tree
  // It stores the beginning of the iterator
  iterator begin() 
  {
    Node<KeyType, ValueType> *curr_node = root;
    iterator it(curr_node);

    if (root == NULL)
      std::cerr << "The tree is empty" << std::endl;
    else 
    {
        if (curr_node != NULL) 
        {
          while (curr_node->getLeft() != NULL)
            curr_node = curr_node->getLeft();
        }

        it = curr_node;
        return it;
    }

    return it;
  }

  // Returns an iterator whose value means INVALID
  // Itertator that denotes the position after the last node in the tree
  iterator end() 
  {
    Node<KeyType, ValueType> *curr_node = root;

    if (curr_node != NULL) 
    {
      while (curr_node->getRight() != NULL)
        curr_node = curr_node->getRight();
    }

    curr_node = curr_node->getRight(); // NULL node after the last node
    iterator it(curr_node);
    return it;
  }
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) 
    {
      if (curr->getKey() == k) {
	       return curr;
      } 
      else if (k < curr->getKey()) {
	       curr = curr->getLeft();
      } 
      else {
	       curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  // Helper function to print the tree's contents
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
    {
    	std::cout << "[";
    	printRoot (r->getLeft());
    	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
    	printRoot (r->getRight());
    	std::cout << "]";
    }
  }
  
  // Helper function to delete all the items
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
    {
    	deleteAll (r->getLeft());
    	deleteAll (r->getRight());
    	delete r;
    }
  }

};

#endif