#ifndef HASHTABLE_INCLUDED
#define HASHTABLE_INCLUDED

#include "Map.h"
#include <string>

class Hashtable: public Map
{
public:
	Hashtable();
	virtual ~Hashtable();
	virtual void add(const std::string& word);
	virtual void reportAll(std::ostream& output);

private:
	
	void resize();
	int hash(std::string word);
	bool find(std::string word, long long* x);
	long long formula(int* digits);
	double loadFactor(int numElem);
	int quadraticProbing(int hashIndex, int i);

	std::pair<std::string, int>* data;
	int hash_size;
	int array_size;
	int index_array_size;
	double load_factor;
};
#endif

	