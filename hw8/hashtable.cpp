#include "hashtable.h"
#include <cmath>
#include <algorithm>

#define ascii_base 128
#define base 40961
#define digit_size 14

const int _size[] = {11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961};

Hashtable::Hashtable()
	: array_size(_size[0])
{
	// start with 11
	data = new std::pair<std::string,int>[_size[0]];

	hash_size = 0;
	load_factor = 0.0;
	index_array_size = 0;
}

Hashtable::~Hashtable()
{
	delete [] data;
	data = NULL;
}

int Hashtable::hash(std::string word)
{
	char *alphabet;

	// convert tolower
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	
	// string to char array
	alphabet = new char[word.length()];
	word.copy(alphabet,word.length());


	// cast char to int
	int *letter = new int[word.length()];
	unsigned int i=0;
	while (i < word.length())
	{
		letter[i] = alphabet[i];
		++i;
	}

	// math formula I
	i = 0;
	int j = word.size()-1; // start from the last letter
	long long a_formula = 0;

	int rem;
	int w[digit_size] = {0};
	int n = digit_size-1;

	while (j > -1)
	{
		long long power = pow(ascii_base,i);
		a_formula += (power * letter[j]);
		--j;
		++i;
		
		if (i == 8 || j == -1)
		{
			i = 0;
			while (a_formula != 0)
			{
				rem = a_formula % base;
				a_formula = a_formula / base;
				w[n] = rem; // store w value from the back of the int array
				--n;
			}
		}
	}

	delete [] letter;
	delete [] alphabet;

	while (n >= 0) // storing 0 if word less than 28 letters
	{
		w[n] = 0;
		--n;
	}

	// hash formula
	long index = formula(w);
	
	return index;
}

long long Hashtable::formula(int* digits)
{
	long long hash = (34394 * long(digits[0]) + 36706 * long(digits[1]) + 38074 * long(digits[2]) + 16351 * long(digits[3]) + 2623 * long(digits[4])
		+ 10174 * long(digits[5]) + 22339 * long(digits[6]) + 27779 * long(digits[7]) + 36642 * long(digits[8]) + 
		19250 * long(digits[9]) + 36216 * long(digits[10]) + 33514 * long(digits[11]) + 24019 * long(digits[12]) + 
		5552 * long(digits[13])) % array_size;

	return hash;	
}

double Hashtable::loadFactor (int numElem)
{
	return ((double)numElem/(double)array_size);
}

void Hashtable::resize() 
{	
	
	int oldSize = _size[index_array_size];
	int newSize = _size[index_array_size+1];
	++index_array_size;	
	array_size = newSize;	

	std::pair<std::string,int> *old_data = data;
	data = new std::pair<std::string,int> [newSize];
	hash_size = 0;
	
	for (int i=0; i<oldSize; i++)
	{
		if (old_data[i].first != "")
		{
			//re hash
			long long hash_index = hash(old_data[i].first);
			int j = 0;
			while (data[hash_index].first != "")
			{
				hash_index = quadraticProbing(hash_index,j);
				++j;
			}
			data[hash_index] = std::make_pair(old_data[i].first,old_data[i].second);
			++hash_size;

			load_factor = loadFactor(hash_size);
		}
	}

	delete [] old_data;
}

bool Hashtable::find(std::string word, long long* x) 
{
	for (int i=0; i<array_size; i++)
	{
		if (data[i].first == word)
		{
			*x = i;
			return true;
		}
	}
	return false;
} 

void Hashtable::add(const std::string& word)
{
	long long hash_index = hash(word);
	int count;

	if (load_factor > 0.5)
		resize();

	if (! find(word,&hash_index)) // if the word doesn't exist
	{
		count = 1;
		if (data[hash_index].first == "") // if the bucket is available
		{
			data[hash_index] = std::make_pair(word,count);
			++hash_size;
		}	
		else // if collision happens
		{
			int i = 0; 
			while (data[hash_index].first != "")
			{
				hash_index = quadraticProbing(hash_index,i);
				++i;
			}

			count = 1;
			data[hash_index] = std::make_pair(word,count);	
			++hash_size;
		}

		load_factor = loadFactor(hash_size);
	}
	else if (find(word,&hash_index))// word exists, increment the occurence
	{
		data[hash_index].second = data[hash_index].second + 1;
	}
	
}

void Hashtable::reportAll(std::ostream& output)
{
	for(int i=0; i< array_size; i++)
	{
		if (data[i].second != 0)
			output << data[i].first << " " << data[i].second << std::endl;
	}
}

int Hashtable::quadraticProbing(int hashIndex, int i)
{
	int x = hashIndex + pow(i,2);
	return (x % array_size);
}

