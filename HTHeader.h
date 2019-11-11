#include <list>
#include <string>

using namespace std; 

class HashTable { 
	int buckets;

	list<string> *table; 
public: 
	HashTable(int b);

	void insert_item(string x); 

	void delete_item(string key); 

	int make_hash(string str);

	void display_hash_table(); 

}; 

