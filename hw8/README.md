Problem 6:

1. What large input cases did you use?

	Answer: 
	Shakespeare's Hamlet, Harry Potter and The Sorcerer's Stone, The Complete Sherlock Holmes, War and Peace

2. Which implementation ran faster? How much faster was it?

	Answer: 
	Running Shakespeare's Hamlet on VM, splay tree runs in 0.091205 seconds, hashtable runs in 4.21293 seconds.
	Splay tree runs faster than hashtable by 4.1217 seconds

	Running Harry Potter and The Sorcerer's Stone on VM, splay tree runs in 0.189475 seconds, hashtable runs in 16.9831 seconds.
	Splay tree runs faster than hashtable by 16.7936 seconds

3. Why do you think that one was faster? Was it because of the chosen input or is there a guarantee made that affects this?

	Answer:
	The reason is splay tree runs faster is because its insert and lookup costs O(log n). Although hashtable theoretically supposed to run in constant runtime O(1), the time it takes to resize the array size and to generate a hash number through the hash function are expensive. 

	It was not because of the chosen input. Instead, splay tree is guaranteeuaranteed to run in O(log n) for insert, lookup, and remove.

4. How do you think the running time would compare to the two if you were to implement your Map in the following fashions? Briefly justify each, although you do not need to quantify how much slower/faster with any specificity.

	Unsorted List

	Answer:

	Lookup: its runtime will be more expensive than both splay tree and hashtable because it needs to compare each element starts from index 0 all the way to where the key is.

	Insert: inserting costs in constant time. Faster than splay tree. 

	Report All: it will cost very expensive if we want to output it in the alphabetical order like we did for the splay tree. If it is not in alphabetical order, it will run the same as hashtable reportAll

	Sorted list

	Answer:

	Lookup: if it's array list, its runtime will be O(log n) by using binary search. If it's a linked list, its worst runtime will be O(n), which is more expensive than splay tree and hashtable.

	Insert: inserting costs in constant time for both array list or linked list since the new key will be added at the end of the list. It is faster than splay tree, but as fast as inserting in hashtable


	Binary search tree, non-rotating variety

	Answer: 

	Lookup: its worst runtime will be O(n), just like a linked list. It runs slower than lookup in splay tree and hashtable.

	Insert: inserting costs O(log n) time. It runs faster than  inserting in splay tree (amortized log n), but slower than inserting in hashtable O(1).


	Binary search tree with AVL balancing
	
	Answer:

	Lookup: it runs as fast as splay tree O(log n), but it runs slower than lookup runtime in hashtable.

	Insert: inserting in AVL tree costs O(log n) faster than  inserting in splay treev (amortized log n). But the constant for AVL is much larger, so splay tree is better to perform on a small subset of data. Inseerting in AVL is slower than inserting in hashtable. Keeping track of the height costs O(log n). Rotation cost O(1), so it has a very little affect to the runtime. 


Problem 4 Note:
	1. Output is outputed on a .txt file called splaytree_output.txt
	2. Iterator class form hw7 is used for reportAll function

Problem 5 Note:
	1. Output is outputed on a .txt file called hashtable_output.txt

Homework 8 directory:
	- Problem 4 & 5 is located in hw_chrysill/hw8

Problem 4 & 5

        How to compile problem 4 & 5: 
         1. Change the directory to hw_chrysill/hw8
         2. Open makefile, change the .cpp filename (it was originally written as main.cpp)
         3. The target executable is named zipf
         3. Type terminal command: make 
         4. Type terminal command: ./exe/zipf [input option (4 for splay tree, 5 for hashtable)] [input file name]
         5. An output file with name (splaytree_output.txt or hashtable_output.txt) is generated depending on your option (4 or 5)