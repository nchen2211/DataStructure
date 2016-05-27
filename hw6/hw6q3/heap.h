#include <vector>
#include <algorithm>
#include <math.h>
#include <stdexcept>
#include <iostream>

// parent index of child(i) = floor((i - 1) / d)
// child(i,j) of parent(i) = d * i + 1, ... , d * i + d

  template <typename T>
  class MinHeap {
     public:
       MinHeap (int d);
       ~MinHeap ();

       void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority. */

       bool isEmpty ();
         /* returns true iff there are no elements on the heap. */
       void remove ();
         /* removes the element with smallest priority. */

   private:
    int d_ary;
    std::vector<std::pair<T,int> > vertex;

    int parent_index(int);
    int child_index(int,int);
    void bubbleUp(int);
    void trickleDown(int,int);
    int smallestChild(int);
  };

  template<typename T>
  MinHeap<T>::MinHeap(int d) {

    if (d > 1)
      d_ary = d;
  }

  template<typename T>
  MinHeap<T>::~MinHeap() {

    vertex.clear();
  }

  template<typename T>
  const T& MinHeap<T>::peek() const {

    try {
      return vertex.at(0).first;
    }catch (std::out_of_range) {
      std::cout << "The heap is empty." << std::endl;
    }

    return vertex.at(0).first;
  }

  template<typename T>
  void MinHeap<T>::add(T item, int priority) {

    vertex.push_back(std::make_pair(item,priority));
    bubbleUp(vertex.size()-1);
  }

  template<typename T>
  void MinHeap<T>::remove() {

    try{

      if (vertex.size() > 1)
      {
        typename std::vector<std::pair<T,int> >::iterator it = vertex.end();
        iter_swap(vertex.begin() + 0, vertex.begin() + (vertex.size() - 1));

        vertex.erase(--it); // deleting 
        trickleDown(0,vertex.at(0).second);
      }
      else if (vertex.size() == 1)
      {
        typename std::vector<std::pair<T,int> >::iterator it = vertex.begin();
        vertex.erase(it); // delete root
      }
      
     } catch (std::out_of_range) {
      std::cout << "Nothing to remove. The heap is empty." << std::endl;
    }
      
  }

  template<typename T>
  bool MinHeap<T>::isEmpty() {

    return (vertex.size() == 0);
  }

  template<typename T>
  int MinHeap<T>::parent_index(int i) {

    return (floor(i - 1) / d_ary);
  }

  template<typename T>
  int MinHeap<T>::child_index(int i,int childNum) {

    return ((d_ary * i) + childNum);
  }

  template<typename T>
  void MinHeap<T>::bubbleUp(int pos) {

    if (pos > 0 && vertex.at(pos).second <= vertex.at(parent_index(pos)).second) 
    {
      if (vertex.at(pos).second == vertex.at(parent_index(pos)).second)
         iter_swap(vertex.begin()+pos, vertex.begin()+ (parent_index(pos)+1));  
      else 
         iter_swap(vertex.begin()+pos, vertex.begin()+parent_index(pos));
       
      bubbleUp(parent_index(pos));
    } 

  }

  template<typename T>
  void MinHeap<T>::trickleDown(int pos, int priority) {

    int child = vertex.size();

    if (pos < vertex.size())
    {
      child = smallestChild(pos);

      if (child < vertex.size())
      {
        if (vertex.at(child).second < priority)
        {
          iter_swap(vertex.begin()+child, vertex.begin() + pos);
          trickleDown(child,vertex.at(child).second);
        }

      }

    }

  }

  template<typename T>
  int MinHeap<T>::smallestChild(int parent) {

    int smallestChildIndex = child_index(parent,1); // assume the smallest is the left most child

    int nextChild = 2; // index for next child to be compared to
    int nextChildIndex = child_index(parent,nextChild); 

    while ((nextChild <= d_ary) && (nextChildIndex < vertex.size())) 
    {
      if(vertex.at(nextChild).second < vertex.at(smallestChildIndex).second)
        smallestChildIndex = nextChildIndex;

        nextChild++;
        nextChildIndex = child_index(parent,nextChild);

    }

    return smallestChildIndex;

  }