#include "splaybst.h"
#include <algorithm>

SplayTree::iterator& SplayTree::iterator::operator++()
{
    if (curr->getRight() != NULL)
    {
        curr = curr->getRight();

        while(curr->getLeft() != NULL)
          curr = curr->getLeft();
    }
    else if (curr->getRight() == NULL)
    {
        SplayNode* parent = curr->getParent();

        while(parent != NULL && curr == parent->getRight())
        {
            curr = parent;
            parent = curr->getParent();
        }

        curr = parent;
    }

  return *this;
}

SplayTree::iterator SplayTree::begin()
{
	SplayNode *curr_node = root;

	if (curr_node != NULL) 
	{
		while (curr_node->getLeft() != NULL)
		curr_node = curr_node->getLeft();
	}

	iterator it(curr_node);
	return it;
}

SplayTree::iterator SplayTree::end()
{
	SplayNode *curr_node = root;

    if (curr_node != NULL) 
    {
      while (curr_node->getRight() != NULL)
        curr_node = curr_node->getRight();
    }

    curr_node = curr_node->getRight(); // NULL node after the last node
    iterator it(curr_node);
    return it;
}

SplayNode* SplayTree::internalFind(const std::string& k) const 
{
	SplayNode *curr = root;
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

void SplayTree::printRoot (SplayNode *r) const
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

void SplayTree::deleteAll(SplayNode* r)
{
	if (r != NULL)
	{
		deleteAll (r->getLeft());
		deleteAll (r->getRight());
		delete r;
	}	
}

void SplayTree::tolower(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	add(word);
}

void SplayTree::add(const std::string& word)
{
	SplayNode* new_node = NULL;
	if (root == NULL) // if the tree is empty
	{
		new_node = new SplayNode(word,1,NULL);
		root = new_node;
		new_node->setParent(NULL);
	}
	else
	{
		if (internalFind(word) != NULL) // if word exists in the tree
		{
			SplayNode* existingWord = internalFind(word);

			if (existingWord == root)
				existingWord->setValue(existingWord->getValue() + 1);
			else
			{
				SplayNode* parent = existingWord->getParent();
				splay(existingWord, parent);
				existingWord->setValue(existingWord->getValue() + 1);
			}
		}
		else if (internalFind(word) == NULL) // if it's a new word
		{
			// insert the word and splay the tree
			// ########### Binary Tree insertion ##############
			SplayNode* parent = NULL;
			SplayNode* curr = NULL;

			curr = this->root;

			while (curr != NULL)
			{
				if (word < curr->getKey())
				{
					parent = curr;
					curr = curr->getLeft();
				}
				else if (word >= curr->getKey())
				{
					parent = curr;
					curr = curr->getRight();
				}
			}

			new_node = new SplayNode(word,1,parent);	

			if (new_node->getKey() < parent->getKey())
				parent->setLeft(new_node);
			else
				parent->setRight(new_node);
			
			curr = new_node;

			// splaying
			splay(curr,parent);
		}
	}
}

void SplayTree::reportAll(std::ostream& output)
{
	 iterator it = begin();
     for (; it != end(); ++it)
        output << it->first << " " << it->second << std::endl;
}

SplayNode* SplayTree::zig(SplayNode* parent)
{
	// left child
	SplayNode* temp = parent;

	root = parent->getLeft();
	root->setParent(NULL);

	if (root->getRight() != NULL) // setting T1 to be the left child of new child
	{
		temp->setLeft(root->getRight());
		root->getRight()->setParent(temp);
		root->setRight(NULL);
	}
	else
		temp->setLeft(NULL); // Don't forget this

	temp->setParent(root);
	root->setRight(temp);

	return root;
}

SplayNode* SplayTree::zag(SplayNode* parent)
{
	// right child
	SplayNode* temp = parent;
	root = parent->getRight();
	root->setParent(NULL);

	if (root->getLeft() != NULL) // setting T1 to be the right child of the new child
	{
		temp->setRight(root->getLeft());
		root->getLeft()->setParent(temp);
		root->setLeft(NULL);
	}
	else
		temp->setRight(NULL); 

	// set new root left child to former parent
	root->setLeft(temp);
	temp->setParent(root);

	return root;
}

SplayNode* SplayTree::zigzig(SplayNode* grandparent)
{
	SplayNode* temp_gparent = grandparent;
	SplayNode* parent = grandparent->getLeft();
	
	// child is now the grandparent
	grandparent = parent->getLeft();

	// setting up new grandparent to great grandparent
	setGreatGrandParent(grandparent,temp_gparent);

	// set T2 from parent to old_grandparent
	if (parent->getRight() != NULL) // if T2  != NULL
	{
		temp_gparent->setLeft(parent->getRight());
		parent->getRight()->setParent(temp_gparent);
	}
	else
		temp_gparent->setLeft(NULL);

	// set T1 from new grandparent (former child) to parent
	if (grandparent->getRight() != NULL) // if T1 != NULL
	{
		parent->setLeft(grandparent->getRight());
		grandparent->getRight()->setParent(parent);
	}
	else
		parent->setLeft(NULL);

	// set new grandparent (former child) right child to parent
	grandparent->setRight(parent);
	parent->setParent(grandparent);

	// set parent right child to former grandparent 
	parent->setRight(temp_gparent);
	temp_gparent->setParent(parent);

	return grandparent;
}

SplayNode* SplayTree::zagzag(SplayNode* grandparent)
{
	SplayNode* temp_gparent = grandparent;
	SplayNode* parent = grandparent->getRight();
	
	// child is now the grandparent
	grandparent = parent->getRight();

	// setting up new grandparent to great grandparent
	setGreatGrandParent(grandparent,temp_gparent);

	// set T1 from parent to old_grandparent
	if (parent->getLeft() != NULL) // if T1  != NULL
	{
		temp_gparent->setRight(parent->getLeft());
		parent->getLeft()->setParent(temp_gparent);
	}
	else
		temp_gparent->setRight(NULL);

	// set T2 from new grandparent (former child) to parent
	if (grandparent->getLeft() != NULL) // if T2 != NULL
	{
		parent->setRight(grandparent->getLeft());
		grandparent->getLeft()->setParent(parent);
	}
	else
		parent->setRight(NULL);

	// set new grandparent (former child) left child to parent
	grandparent->setLeft(parent);
	parent->setParent(grandparent);

	// set parent left child to former grandparent 
	parent->setLeft(temp_gparent);
	temp_gparent->setParent(parent);

	return grandparent;
}

SplayNode* SplayTree::zigzag(SplayNode* grandparent)
{
	SplayNode* temp_gparent = grandparent;
	SplayNode* parent = grandparent->getLeft();

	// child is now the grandparent
	grandparent = parent->getRight();

	// setting up new grandparent to great grandparent
	setGreatGrandParent(grandparent,temp_gparent);
	
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

	return grandparent;
}

SplayNode* SplayTree::zagzig(SplayNode* grandparent)
{
	SplayNode* temp_gparent = grandparent;
	SplayNode* parent = grandparent->getRight();

	// child is now the grandparent
	grandparent = parent->getLeft();

	// setting up new grandparent to great grandparent
	setGreatGrandParent(grandparent,temp_gparent);
	
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

	return grandparent;
}

void SplayTree::setGreatGrandParent(SplayNode* grandparent,SplayNode* temp_gparent)
{
	if (temp_gparent->getParent() != NULL)
	{
		SplayNode* greatgrandparent = temp_gparent->getParent();
		grandparent->setParent(greatgrandparent);

		// setting great grandparent child to new grandparent
		if (greatgrandparent->getLeft() == temp_gparent)
			greatgrandparent->setLeft(grandparent);
		else if (greatgrandparent->getRight() ==  temp_gparent)
			greatgrandparent->setRight(grandparent);
	}	
	else 
	{
		grandparent->setParent(NULL);
		root = grandparent;
	}
}

void SplayTree::splay(SplayNode* curr, SplayNode* parent)
{
	/* case 1: if parent is root
	   case 2: if parent is not root (grandparent(s) exists)*/
	
	while (curr->getParent() != NULL)
	{
		if(parent->getParent() == NULL) // case 1
		{
			if (curr->getParent()->getLeft() == curr)
				curr = zig(parent);
			else if (curr->getParent()->getRight() == curr)
				curr = zag(parent);
		}
		else if (parent->getParent() != NULL) // case 2
		{
			SplayNode* grandparent = parent->getParent();
			
			if (grandparent->getLeft() == parent && parent->getLeft() == curr)
				curr = zigzig(grandparent);
			else if (grandparent->getRight() == parent && parent->getRight() == curr)
				curr = zagzag(grandparent);
			else if (grandparent->getLeft() == parent && parent->getRight() == curr)
				curr = zigzag(grandparent);	
			else if (grandparent->getRight() == parent && parent->getLeft() == curr)
				curr = zagzig(grandparent);
		}

		parent = curr->getParent();
	}
}



