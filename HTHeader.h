#include <list>
#include <string>

using namespace std;

class HashTable {
	int buckets;

	list<string> *table;

	int func;
public:
	HashTable(int b, int func);

	void insert_item(string x);

	void delete_item(string key);

	int make_hash(string str);

	void display_hash_table();

};
