#include <iostream>
#include <string>

using namespace std;

template <typename K,typename V>
class Hashnode {
private:
	K key;
	V value;
public:
	

	Hashnode(K key, V value) {
		this->key = key;
		this->value = value;
	}
	int getkey() {
		return key;
	}
	int getvalue() {
		return value;
	}
	int setkey(int key) {
		this->key = key
	}
};


template <typename K, typename V>
class HashMap {
public:
	void print();
	HashMap(int size);
	void insert(K key, V value);
	int get(K key);
	~HashMap();
private:
	Hashnode<K,V> **table;
	int size;
};
template<typename K, typename V>
HashMap<K, V>::~HashMap() {
	for (int i = 0;i < size;i++)
	{
		delete table[i];
	}
	delete[] table;
}
template<typename K, typename V>
HashMap<K, V>::HashMap(int size)
{
	this->size = size;
	table = new Hashnode<K, V> *[size];
	for (int i = 0;i < size;i++)
	{
		table[i] =	NULL;
	}
}
template <typename K, typename V>
void HashMap<K,V>::insert(K key, V value) {
		int hash = key % size;
		while (table[hash] != NULL && table[hash]->getkey() != key) {
			int hash2 = (hash * size - 1) % size;
			hash = (hash + hash2) % size;
		}
		table[hash] = new Hashnode<K, V>(key, value);
}
template <typename K, typename V>
int HashMap<K, V>::get(K key) {
	int hash = key % size;
	while (table[hash] != NULL && table[hash]->getkey() != key) {
		int hash2 = (hash * size - 1) % size;
		hash = (hash + hash2) % size;
	}
	return table[hash]->getvalue();
}



template <typename K, typename V>
void HashMap<K, V>::print() {
	for (int i = 0;i < size;i++)
	{
		if (table[i] != NULL)
			cout << table[i]->getvalue()<< endl;
		else
			cout << "NULL" << endl;
	}
}

int main(){
	HashMap<int,int> b(10);
	b.insert(5, 10);
	b.insert(8, 7);
	b.print();
	cout << b.get(5);

}