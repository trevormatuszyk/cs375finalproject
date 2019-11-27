#include <list>
#include <string>

using namespace std;

class HashTable {
	int buckets;
	list<string> *table;
	int hash_method;
	int coll_res;

public:
	HashTable(int b, int hash_method, int coll_res);

	void insert_item(string x);

	void delete_item(string key);

	int make_hash(string str);

	void display_hash_table();

	int multMethod(int key);

	int linear_mod_collisions;
	int quadratic_mod_collisions;

	int linear_mul_collisions;
	int quadratic_mul_collisions;

};
