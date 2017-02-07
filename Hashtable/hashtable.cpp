#include <iostream>
#include <list>
#include <string>


using namespace std;



class HashEntry {	
public:
	int key;
	int value;
	HashEntry(int key, int value) {	//HashEntry Class for making a new entry
		this->key = key;
		this->value = value;
	}

	int getKey() {	//return key
		return key;
	}

	int getValue() { 	// returns value
		return value;
	}
};

class HashMap {			//Hashmap class
private:
	HashEntry **table;		//table to store key,value pairs
	int TABLE_SIZE;
public:
	HashMap(int TABLE_SIZE) {				//constructor for creating a table 
		table = new HashEntry*[TABLE_SIZE];
		this->TABLE_SIZE = TABLE_SIZE;
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
	}

	int get(int key) {
		int hash = (key % TABLE_SIZE);
		while (table[hash] != NULL && table[hash]->getKey() != key)	//rehashing value if there is collision
			hash = (hash + 1) % TABLE_SIZE;
		if (table[hash] == NULL)
			return -1;
		else
			return table[hash]->getValue();
	}

	void put(int key, int value) {				// inserts element into hashtable
		int hash = (key % TABLE_SIZE);
		while (table[hash] != NULL && table[hash]->getKey() != key)
			hash = (hash + 1) % TABLE_SIZE;
		if (table[hash] != NULL)
			delete table[hash];
		table[hash] = new HashEntry(key, value);
	}
	void rehash() {							// if the table is full, this function will increase the table size
		HashEntry **table1;
		int originalsize = TABLE_SIZE;
		table1 = new HashEntry*[TABLE_SIZE];		// allocate memory for new table and copy the current values;
		for (int i = 0; i < TABLE_SIZE; i++)
			table1[i] = table[i];
		this->TABLE_SIZE = 2 * TABLE_SIZE;	//double the table size;

		table = new HashEntry*[TABLE_SIZE];

		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
		for (int i = 0; i < originalsize; i++)
			if (table1[i] != NULL)
			{
				int val = table1[i]->getValue();			//copy values
				int key = table1[i]->getKey();
				put(key, val);
			}
		for (int i = 0; i < originalsize; i++)				// delete memory for table1
			if (table1[i] != NULL)
				delete table1[i];
		delete[] table1;
	}
	void display() {			//displays the hash table
		int a, b;
		for (int i = 0;i < TABLE_SIZE;i++)
		{
			
			{
				cout << table[i]->getValue();
			}
		}
	}
	~HashMap() {									//destructor
		for (int i = 0; i < TABLE_SIZE; i++)
			if (table[i] != NULL)
				delete table[i];
		delete[] table;
	}
};


int main() {
	
	HashMap a(10);
	a.put(5, 5);
	a.put(6, 5);
	
	cout << endl;
	cout <<a.get(5);
	a.rehash();
	a.display();
	a.put(3, 4);
	cout << a.get(3);
	
	return 0;
}