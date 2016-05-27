/*
 * avlbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 * 2016-03-31  Cote      Modify for AVL Trees
 */
#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"
#include <cmath>

template <class KeyType, class ValueType>
class AVLNode : public Node<KeyType, ValueType>
{
public:
  AVLNode (KeyType k, ValueType v, AVLNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { height = 0; }
  
  virtual ~AVLNode () {}
  
  int getHeight () const
    { return height; }
  
  void setHeight (int h)
    { height = h; }
  
  virtual AVLNode<KeyType, ValueType> *getParent () const
    { return (AVLNode<KeyType,ValueType>*) this->_parent; }
  
  virtual AVLNode<KeyType, ValueType> *getLeft () const
    { return (AVLNode<KeyType,ValueType>*) this->_left; }
  
  virtual AVLNode<KeyType, ValueType> *getRight () const
    { return (AVLNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  int height;
};

/* -----------------------------------------------------
 * AVL Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class AVLTree : public BinarySearchTree<KeyType, ValueType>
{
public:
    AVLTree() {};
    void insert (const std::pair<const KeyType, ValueType>& new_item);
    void remove (const KeyType &toRemove);

  private:
    // balancing functions
    bool determine_higherChild(Node<KeyType,ValueType>* curr);
    Node<KeyType,ValueType>* LL_rotation(Node<KeyType,ValueType>* parent);
    Node<KeyType,ValueType>* RR_rotation(Node<KeyType,ValueType>* parent);
    Node<KeyType,ValueType>* RL_rotation(Node<KeyType,ValueType>* grandparent);
    Node<KeyType,ValueType>* LR_rotation(Node<KeyType,ValueType>* grandparent);
    void updateHeight(Node<KeyType,ValueType>* node);
    Node<KeyType,ValueType>* childDirection(Node<KeyType,ValueType>* node);
    int heightDiff (Node<KeyType,ValueType>* curr_node);
    void update(Node<KeyType,ValueType>* node);
    void setParent(Node<KeyType,ValueType>* newParent, Node<KeyType,ValueType>* stored_grandparent, Node<KeyType,ValueType>* to_remove);
};

#endif

template <class KeyType, class ValueType>
void AVLTree<KeyType,ValueType>::insert(const std::pair<const KeyType, ValueType>& new_item)
{
    Node<KeyType,ValueType>* new_node;
    
    // ################ inserting a new element using bst insert #####################
    if (this->root == NULL)
    {
        new_node = new AVLNode<KeyType,ValueType>(new_item.first,new_item.second,NULL); 
        static_cast<AVLNode<KeyType,ValueType>*>(new_node)->setHeight(1);
        this->root = new_node; 
        new_node->setParent(NULL);
    }
    else 
    { 
        if (!this->internalFind(new_item.first))
        {
            Node<KeyType,ValueType>* parent;
            Node<KeyType,ValueType>* curr;
            
            curr = this->root;

            while (curr != NULL)
            {
                if (new_item.first < curr->getKey())
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

            AVLNode<KeyType,ValueType>* avlParent = static_cast<AVLNode<KeyType,ValueType>*>(parent);
            new_node = new AVLNode<KeyType,ValueType>(new_item.first,new_item.second, avlParent); 
            
            // set current to the new node added to the tree
            curr = new_node;
            static_cast<AVLNode<KeyType,ValueType>*>(new_node)->setHeight(1);

           // h = static_cast<AVLNode<KeyType,ValueType>*>(new_node)->getHeight();

            if (new_node->getKey() < avlParent->getKey())
                avlParent->setLeft(new_node);
            else
                avlParent->setRight(new_node);

                 std::cout << "inserting: " << new_node->getKey() <<std::endl;

            // ############################# AVL Balancing #########################
            while (curr->getParent() != NULL) // while curr hasn't reached the root
            {
                // updating parent & grandparent(s) heights
                if (curr->getParent() != NULL)  
                {
                    int childHeight = static_cast<AVLNode<KeyType,ValueType>*>(curr)->getHeight();

                    curr = curr->getParent();
                    static_cast<AVLNode<KeyType,ValueType>*>(curr)->setHeight(childHeight+1);
                }

                int h_diff = heightDiff(curr); // comparing children heights

                // if unbalance, rotate
                if (h_diff > 1)
                {
                    Node<KeyType,ValueType>* child; // y node
                    if (determine_higherChild(curr))
                        child = curr->getLeft();
                    else
                        child = curr->getRight();

                    Node<KeyType,ValueType> *grandChild; // x node
                    if (determine_higherChild(child))
                        grandChild = child->getLeft();
                    else
                        grandChild = child->getRight();
                   
                    // curr is pointing to grandparent (z) where the unbalance height occurs 
                    if (curr->getLeft() == child && child->getLeft() == grandChild)
                        curr = LL_rotation(child);
                    else if (curr->getRight() == child && child->getRight() == grandChild)
                        curr = RR_rotation(child);
                    else if (curr->getRight() == child && child->getLeft() == grandChild)
                        curr = RL_rotation(curr);
                    else if (curr->getLeft() == child && child->getRight() == grandChild)
                        curr = LR_rotation(curr);
                }
            } // end while
        }
        else
          std::cout << "Duplicated element!" << std::endl;
    }
}

template <class KeyType, class ValueType>
void AVLTree<KeyType,ValueType>::remove(const KeyType &toRemove)
{
    Node<KeyType,ValueType>* curr = this->internalFind(toRemove);

    if (curr == NULL)
        std::cout << "Element does not exist" <<std::endl;
    else 
    {
        Node<KeyType,ValueType>* to_remove = curr;

        while (curr->getParent() != NULL || to_remove == this->root)
        {
            if (to_remove == NULL)
                curr = curr->getParent();

            if (to_remove != NULL)
            {
                // removing: if leaf
                if (to_remove->getLeft() == NULL && to_remove->getRight() == NULL) 
                {
                    Node<KeyType,ValueType>* stored_curr = NULL;
                    if (to_remove != this->root)
                    {
                        if (curr->getParent() != NULL)  
                            curr = curr->getParent();

                        if (curr->getLeft() == to_remove) // if to_remove is the left child
                        {
                            if (curr->getRight() == NULL) // if right child doesn't exist
                                static_cast<AVLNode<KeyType,ValueType>*>(curr)->setHeight(1);
                            
                             curr->setLeft(NULL);
                        }
                        else if (curr->getRight() == to_remove) // if to_remove is the right child
                        {
                            if (curr->getLeft() == NULL) // if the left child doesn't exist
                                static_cast<AVLNode<KeyType,ValueType>*>(curr)->setHeight(1);

                            curr->setRight(NULL);
                            to_remove->setParent(NULL);
                        }

                        stored_curr = curr;

                        delete to_remove;
                        to_remove = NULL; // deleting to_remove

                        // updating height
                        update(curr);
                        curr = stored_curr;
                      }
                      else if (to_remove == this->root)
                      {
                          delete this->root;
                          this->root = NULL;
                          std::cout << "The AVL tree is now empty" << std::endl;
                      }
                        
                }
                // removing: if parent with 1 child
                else if (to_remove->getRight() == NULL || to_remove->getLeft() == NULL)
                {
                    Node<KeyType,ValueType>* child = childDirection(to_remove);

                    // if to_remove is not the root
                    if (to_remove->getParent() != NULL)
                    {
                        Node<KeyType,ValueType>* grandparent = to_remove->getParent();
                       
                        if (grandparent->getLeft() == to_remove)
                            grandparent->setLeft(child);
                        else if (grandparent->getRight() == to_remove)
                            grandparent->setRight(child);

                        child->setParent(grandparent);
                    }
                    else if (to_remove->getParent() == NULL) // if to_remove is the root
                    {
                        child->setParent(NULL);
                        this->root = child;
                        static_cast<AVLNode<KeyType,ValueType>*>(child)->setHeight(1);
                    }

                    // updating height
                    update(child);
                    curr = child;

                    delete to_remove;
                    to_remove = NULL;

                } // end parent with 1 child
                // removing: if parent with 2 children
                else if (to_remove->getLeft() != NULL && to_remove->getRight() != NULL)
                {
                    // find with largest element in its left subtree
                    Node<KeyType,ValueType>* newParent = to_remove->getLeft();
                    Node<KeyType,ValueType>* stored_parent = NULL; 
                    Node<KeyType,ValueType>* stored_grandparent = NULL;

                    //if (to_remove->getParent() != NULL) // if to_remove != root
                    //{
                        if (to_remove->getParent() != NULL)
                            stored_grandparent = to_remove->getParent();

                        while (newParent->getRight() != NULL)
                            newParent = newParent->getRight(); // go to the right most child


                        if (newParent->getParent() != to_remove)
                        {
                            stored_parent = newParent->getParent();
                            stored_parent->setRight(NULL);


                            // if newparent have a left child
                            if (newParent->getLeft() != NULL) 
                            {
                                newParent->getLeft()->setParent(stored_parent);
                                stored_parent->setRight(newParent->getLeft());
                            }

                            if (to_remove == this->root)
                            {
                                newParent->setParent(NULL);
                                this->root = newParent;
                            }

                            newParent->setLeft(to_remove->getLeft());
                            newParent->setRight(to_remove->getRight());
                            
                            to_remove->getLeft()->setParent(newParent);
                            to_remove->getRight()->setParent(newParent); 
                          
                            setParent(newParent,stored_grandparent,to_remove);
                            update(stored_parent);

                            curr = stored_parent;

                            delete to_remove;
                            to_remove = NULL;
                        }
                        // if the new parent is exactly the largest elem in to_remove left subtree
                        else if (newParent->getParent() == to_remove) 
                        {
                            Node<KeyType,ValueType>* temp_child = NULL;
                            Node<KeyType,ValueType>* temp_newParent = newParent;

                            if (to_remove->getRight() != NULL)
                            {
                                temp_child = to_remove->getRight();
                                temp_child->setParent(newParent);
                                newParent->setRight(temp_child);
                                
                                to_remove->setRight(NULL);
                                to_remove->setParent(NULL);
                            }

                            if (to_remove == this->root)
                            {
                                newParent->setParent(NULL);
                                this->root = newParent;
                            }

                            setParent(newParent,stored_grandparent,to_remove);
                
                            // determining the starting point where to update height
                            if (temp_newParent->getLeft() != NULL)
                                update(temp_newParent->getLeft());
                            else if(temp_newParent->getRight() != NULL)
                                update(temp_newParent->getRight());
                            else if (static_cast<AVLNode<KeyType,ValueType>*>(temp_newParent)->getHeight() == 1)
                            {
                                if (stored_parent->getRight() != NULL)
                                {
                                    update(stored_parent->getRight());
                                }
                                else if (stored_parent->getRight() == NULL)
                                    update(newParent);
                            }

                            curr = newParent;

                            delete to_remove;
                            to_remove = NULL;
                        }
                } // end parent with 2 children

            } // end to_remove != NULL

             // ############################# AVL Balancing #########################
            int h_diff = heightDiff(curr);

            if (h_diff > 1)
            {
                Node<KeyType,ValueType>* child; // y node
                if (determine_higherChild(curr))
                    child = curr->getLeft();
                else
                    child = curr->getRight();

                Node<KeyType,ValueType> *grandChild; // x node
                if (determine_higherChild(child))
                    grandChild = child->getLeft();
                else
                    grandChild = child->getRight();

                // curr is pointing to grandparent (z) where the unbalance height occurs 
                if (curr->getLeft() == child && child->getLeft() == grandChild)
                    curr = LL_rotation(child);
                else if (curr->getRight() == child && child->getRight() == grandChild)
                    curr = RR_rotation(child);
                else if (curr->getRight() == child && child->getLeft() == grandChild)
                    curr = RL_rotation(curr);
                else if (curr->getLeft() == child && child->getRight() == grandChild)
                    curr = LR_rotation(curr);
            }

            updateHeight(curr);

        } // end while

    } // end if the element exists
   
}

template <class KeyType, class ValueType>
int AVLTree<KeyType,ValueType>::heightDiff (Node<KeyType,ValueType>* curr_node)
{
    int l,r;

    if (curr_node->getLeft() != NULL && curr_node->getRight() == NULL)
    {
        r = 0;
        l = static_cast<AVLNode<KeyType,ValueType>*>(curr_node)->getLeft()->getHeight();
    }
    else if (curr_node->getLeft() == NULL && curr_node->getRight() != NULL)
    {
        l = 0;
        r = static_cast<AVLNode<KeyType,ValueType>*>(curr_node)->getRight()->getHeight();
    }
    else if (curr_node->getLeft() != NULL && curr_node->getRight() != NULL)
    {
        l = static_cast<AVLNode<KeyType,ValueType>*>(curr_node)->getLeft()->getHeight();
        r = static_cast<AVLNode<KeyType,ValueType>*>(curr_node)->getRight()->getHeight();
    }
    else if (curr_node->getLeft() == NULL && curr_node->getRight() == NULL)
    {
        l = r = 0;
    }

    return (abs(l-r));
}

template <class KeyType, class ValueType>
bool AVLTree<KeyType,ValueType>::determine_higherChild(Node<KeyType,ValueType>* curr)
{
  // return true if left child have larger height

    int leftChildHeight, rightChildHeight;

    if (curr->getLeft() != NULL)
        leftChildHeight = static_cast<AVLNode<KeyType,ValueType>*>(curr->getLeft())->getHeight();
    else
        leftChildHeight = 0;

    if (curr->getRight() != NULL)
        rightChildHeight = static_cast<AVLNode<KeyType,ValueType>*>(curr->getRight())->getHeight();
    else
        rightChildHeight = 0;

    if (leftChildHeight > rightChildHeight)
        return true;
    else if (leftChildHeight < rightChildHeight)
        return false;
    else if (leftChildHeight == rightChildHeight) // choose single rotation
    {
        if (curr->getParent() != NULL)
        {
            if (curr->getParent()->getLeft() == curr) // if curr is left child of its parent
                return true;
            else if (curr->getParent()->getRight() == curr)
                return false;
        }
        else
            return true;      
    }

    return true;
}

template <class KeyType, class ValueType>
void AVLTree<KeyType,ValueType>::updateHeight(Node<KeyType,ValueType>* node)
{
    if (node->getLeft() == NULL && node->getRight() == NULL)
        static_cast<AVLNode<KeyType,ValueType>*> (node)->setHeight(1);
    else
    {
        int height;
        if (determine_higherChild(node)) 
            height = static_cast<AVLNode<KeyType,ValueType>*> (node->getLeft())->getHeight();  
        else
            height = static_cast<AVLNode<KeyType,ValueType>*> (node->getRight())->getHeight();

        static_cast<AVLNode<KeyType,ValueType>*> (node)->setHeight(height+1);
    }
}

template <class KeyType, class ValueType>
Node<KeyType,ValueType>* AVLTree<KeyType,ValueType>::LL_rotation(Node<KeyType,ValueType> *parent)
{
    Node<KeyType,ValueType>* grandparent = parent->getParent();
    Node<KeyType,ValueType>* greatgrandparent = NULL;

    // storing great grandparent
    if (grandparent->getParent() != NULL) 
        greatgrandparent = grandparent->getParent();

    // updating the new parent's parent
    if (greatgrandparent == NULL) // if new parent is the new root
    {
        parent->setParent(NULL);
        this->root = parent;
    }
    else // if greatgrandparent exists
    {
        parent->setParent(greatgrandparent);

        if (greatgrandparent->getLeft() == grandparent)
            greatgrandparent->setLeft(parent);
        else if (greatgrandparent->getRight() == grandparent)
            greatgrandparent->setRight(parent);
    }
     
    // setting T2 to the new parent
    if (parent->getRight() != NULL)
    {
        grandparent->setLeft(parent->getRight());
        parent->getRight()->setParent(grandparent);
    }
    else
        grandparent->setLeft(NULL);


    // setting the right child of new parent
    parent->setRight(grandparent);
    grandparent->setParent(parent);


    // update new height of the right child of new parent (which was the former grandparent)
    updateHeight(grandparent);
    updateHeight(parent);
    updateHeight(parent->getLeft());

    return parent;
} 

template <class KeyType, class ValueType>
Node<KeyType,ValueType>* AVLTree<KeyType,ValueType>::RR_rotation(Node<KeyType,ValueType>* parent)
{
    Node<KeyType,ValueType>* grandparent = parent->getParent();
    Node<KeyType,ValueType>* greatgrandparent = NULL;

    // storing great grandparent
    if (grandparent->getParent() != NULL) 
        greatgrandparent = grandparent->getParent();

    // updating the new parent's parent
    if (greatgrandparent == NULL) // if new parent is the new root
    {
        parent->setParent(NULL);
        this->root = parent;
    }
    else // if greatgrandparent exists
    {
        parent->setParent(greatgrandparent);

        if (greatgrandparent->getLeft() == grandparent)
            greatgrandparent->setLeft(parent);
        else if (greatgrandparent->getRight() == grandparent)
            greatgrandparent->setRight(parent);
    }
    
    // setting T1 to the new parent
    if (parent->getLeft() != NULL)
    {
        grandparent->setRight(parent->getLeft());
        parent->getLeft()->setParent(grandparent);
    }
    else 
        grandparent->setRight(NULL);

    // setting the left child of new parent
    parent->setLeft(grandparent);
    grandparent->setParent(parent);

    // update new height of the right child of new parent (which was the former grandparent)
    updateHeight(grandparent);
    updateHeight(parent);
    updateHeight(parent->getRight());

    return parent;
}

template <class KeyType, class ValueType>
Node<KeyType,ValueType>* AVLTree<KeyType,ValueType>::RL_rotation(Node<KeyType,ValueType> *grandparent)
{
    Node<KeyType,ValueType>* temp_gparent = grandparent;
    Node<KeyType,ValueType>* parent = grandparent->getRight();
    Node<KeyType,ValueType>* greatgrandparent = NULL;

    // child is now the grandparent
    grandparent = parent->getLeft();

    if (temp_gparent->getParent() != NULL)
        greatgrandparent = temp_gparent->getParent();

    // setting up new grandparent to great grandparent
    if (greatgrandparent == NULL) // if new parent is the new root
    {
        grandparent->setParent(NULL);
        this->root = grandparent;
    }
    else // if greatgrandparent exists
    {
        grandparent->setParent(greatgrandparent);

        if (greatgrandparent->getLeft() == temp_gparent)
            greatgrandparent->setLeft(grandparent);
        else if (greatgrandparent->getRight() == temp_gparent)
            greatgrandparent->setRight(grandparent);
    }
  
    // set T1 from new grandparent's left child as old grandparent's right child
    if (grandparent->getLeft() != NULL)
    {
        temp_gparent->setRight(grandparent->getLeft());
        grandparent->getLeft()->setParent(temp_gparent);
    }
    else
        temp_gparent->setRight(NULL);

    // set T2 from new grandparent's right child as parent's left child
    if (grandparent->getRight() != NULL)
    {
        parent->setLeft(grandparent->getRight());
        grandparent->getRight()->setParent(parent);
    }
    else
        parent->setLeft(NULL);

    // set new grandparent's left child
    grandparent->setLeft(temp_gparent);
    temp_gparent->setParent(grandparent);

    // set new grandparent's right child
    grandparent->setRight(parent);
    parent->setParent(grandparent);

    // updating height new left child
    updateHeight(temp_gparent);
    // updating height new right child
    updateHeight(parent);
    // updating new parent height
    updateHeight(grandparent);
 
    return grandparent;
}


template <class KeyType, class ValueType>
Node<KeyType,ValueType>* AVLTree<KeyType,ValueType>::LR_rotation(Node<KeyType,ValueType> *grandparent)
{
    Node<KeyType,ValueType>* temp_gparent = grandparent;
    Node<KeyType,ValueType>* parent = grandparent->getLeft();
    Node<KeyType,ValueType>* greatgrandparent = NULL;

    // child is now the grandparent
    grandparent = parent->getRight();

    if (temp_gparent->getParent() != NULL)
        greatgrandparent = temp_gparent->getParent();

    // setting up new grandparent to great grandparent
    if (greatgrandparent == NULL) // if new parent is the new root
    {
        grandparent->setParent(NULL);
        this->root = grandparent;
    }
    else // if greatgrandparent exists
    {
        grandparent->setParent(greatgrandparent);

        if (greatgrandparent->getLeft() == temp_gparent)
            greatgrandparent->setLeft(grandparent);
        else if (greatgrandparent->getRight() == temp_gparent)
            greatgrandparent->setRight(grandparent);
    }
  
    // set T1 from new grandparent's left child as parent's right child
    if (grandparent->getLeft() != NULL)
    {
        parent->setRight(grandparent->getLeft());
        grandparent->getLeft()->setParent(parent);
    }
    else
        parent->setRight(NULL);

    // set T2 from new grandparent's right child as old grandparent's left child
    if (grandparent->getRight() != NULL)
    {
        temp_gparent->setLeft(grandparent->getRight());
        grandparent->getRight()->setParent(temp_gparent);
    }
    else
        temp_gparent->setLeft(NULL);

    // set new grandparent's left child
    grandparent->setLeft(parent);
    parent->setParent(grandparent);

    // set new grandparent's right child
    grandparent->setRight(temp_gparent);
    temp_gparent->setParent(grandparent);

    // updating height new left child
    updateHeight(parent);
    // updating height new right child
    updateHeight(temp_gparent);
    // updating new parent height
    updateHeight(grandparent);
  
    return grandparent;
}

template <class KeyType, class ValueType>
Node<KeyType,ValueType>* AVLTree<KeyType,ValueType>::childDirection(Node<KeyType,ValueType>* node)
{
    Node<KeyType,ValueType>* child;
    if (node->getLeft() != NULL) // if to_remove child is left
      child = node->getLeft();
    else if (node->getRight() != NULL) // if to_remove child is right
      child = node->getRight();

    return child;
}

template <class KeyType, class ValueType>
void AVLTree<KeyType,ValueType>::update(Node<KeyType,ValueType>* node)
{
    while (node->getParent() != NULL)
    {
        node = node->getParent();

        int h;
        if (determine_higherChild(node))
            h =  static_cast<AVLNode<KeyType,ValueType>*>(node->getLeft())->getHeight();
        else
            h =  static_cast<AVLNode<KeyType,ValueType>*>(node->getRight())->getHeight();
      
        static_cast<AVLNode<KeyType,ValueType>*>(node)->setHeight(h+1);
    }
}

template <class KeyType, class ValueType>
void AVLTree<KeyType,ValueType>::setParent(Node<KeyType,ValueType>* newParent, Node<KeyType,ValueType>* stored_grandparent, Node<KeyType,ValueType>* to_remove)
{
    if (stored_grandparent != NULL)
    {
        newParent->setParent(stored_grandparent);

        if(stored_grandparent->getLeft() == to_remove)
            stored_grandparent->setLeft(newParent);
        else if(stored_grandparent->getRight() == to_remove)
            stored_grandparent->setRight(newParent);
    }  
}