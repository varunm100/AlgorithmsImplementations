#include <iostream>

using namespace std;

template <class E, class K>

class HashTable {
	public:
		HashTable(int divisor = 11);
		~HashTable() {delete [] ht;
			delete [] empty;}
			int Search(const K &k, E &e) const;
			HashTable<E,K>& Insert(const E& e);
			void Output();
			void OutputWithBlankSpots();
			void deleteFromAsVal(E e);
	private:
			int hSearch(const K& k) const;
			int D;
			E *ht;
			int *empty;
};

template <class E, class K>
HashTable<E,K>::HashTable(int divisor)
{
	D = divisor;
	ht = new E [D];
	empty = new int [D];
 
	for (int i = 0; i < D; i++)
		empty[i] = 1;
}
template <class E, class K>
int HashTable<E,K>::hSearch(const K& k) const
{
	int i = k % D;  
	int j = i;     
	do {
		if (empty[j] || ht[j] == k) return j;
		j = (j + 1) % D;
	} while (j != i);
	return j;
}

template <class E, class K>
void HashTable<E,K>::deleteFromAsVal(E e)
{
	int b=hSearch(e);
	if( !empty[b] && ht[b]==e)
	{
		ht[b]=0;
		empty[b]=1;
	}
	else
		cout<<"element not found!!!";
 
}
template <class E, class K>
int HashTable<E,K>::Search(const K& k, E& e) const
{
	int b = hSearch(k);
	if (empty[b] || ht[b] != k) return 0;
	e = ht[b];
	return 1;
}

template <class E, class K>
HashTable<E,K>& HashTable<E,K>::Insert(const E& e)
{
	K k = e;
	int b = hSearch(k);
	if (empty[b]) {empty[b] = 0;
		ht[b] = e;
		return *this;
 
	}
	if (ht[b] == k) { 
		cout<< "ERROR ERROR"; 
		return *this; 
	}
	cout<<"Sorry but this table is filled to the MAXX";
	return *this;
}
 
template <class E, class K>

void HashTable<E,K>::Output()
{
	for (int i = 0; i< D; i++) {
		if (empty[i]) {
			cout << "";
		} else {
			cout << " " << ht[i]<<"";
		}
	}
	cout << endl;
}

template <class E, class K>

void HashTable<E,K>::OutputWithBlankSpots()
{
	for (int i = 0; i< D; i++) {
		if (empty[i]) {
			cout << " NULL";
		} else {
			cout << " " << ht[i]<<"";
		}
	}
	cout << endl;
}


class element {
	friend int main();
	public:
		operator long() const {
			return key;
		}
	private:
		int data;
		long key;
};

int main() {
	int HashTableSize = 17;
	HashTable <int,int> TestingHashTable(HashTableSize);
	TestingHashTable.Insert(10);
	TestingHashTable.Insert(100);
	TestingHashTable.Insert(40);
	TestingHashTable.Insert(70);
	TestingHashTable.Insert(14);
	TestingHashTable.Insert(22);
	TestingHashTable.Insert(11);
	TestingHashTable.Insert(345);
	TestingHashTable.Insert(23);
	TestingHashTable.Insert(1);

	TestingHashTable.Output();
	TestingHashTable.OutputWithBlankSpots();
	TestingHashTable.deleteFromAsVal(10);
	TestingHashTable.Output();
	TestingHashTable.OutputWithBlankSpots();
	TestingHashTable.deleteFromAsVal(100);
	TestingHashTable.Output();
	TestingHashTable.OutputWithBlankSpots();
	TestingHashTable.deleteFromAsVal(40);
	TestingHashTable.Output();
	TestingHashTable.OutputWithBlankSpots();
	return 0;
}