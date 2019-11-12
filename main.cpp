#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "HTHeader.h"


HashTable::HashTable(int b, int hash_method, int coll_res){
	this->buckets = b;
	table = new list<string>[buckets];
	this->hash_method = hash_method;
	this->coll_res = coll_res;
}


int HashTable::make_hash(string str){

	int num = 0;

	for(int i=0; i<str.size(); i++){
		num += (int)str[i];
	}
	int hash = 0;

	switch (hash_method) {
		case 1: hash = num % buckets;
							break;
		case 2: hash = multMethod(num);
							break;
	}
	return hash;
}

void HashTable::display_hash_table(){

	list<string>::iterator it;

	for(int i=0; i<buckets; i++){
		int bucket_size = 0;
		cout << "Bucket " << i << ":\t";
		for (it = table[i].begin(); it != table[i].end(); it++){
			bucket_size++;
			if(bucket_size == table[i].size()){
				cout << *it;
			}
			else{
				cout << *it << "-->";
			}

		}
		cout << endl;

	}
	cout << " " << endl;

}


void HashTable::insert_item(string name) {
	int index = make_hash(name);
	

	switch (coll_res) {
		case 1: //chaining
			table[index].push_back(name); 
			break;

		case 2: //linear probing
			
			if(table[index].empty()){
				table[index].push_back(name); 
			}
			else{
				int tmp_index = index;
				while(tmp_index != buckets-1){
					if(table[tmp_index].empty()){
						table[tmp_index].push_back(name);
						break;
					}
					else{
						tmp_index++;
						continue;
					}
				}
			}
			break;
		case 3: //quadratic probing
			
			if(table[index].empty()){
				table[index].push_back(name); 
			}

			else{
				int tmp_index = index;
				int counter = 1;
				while(tmp_index != buckets-1){
					if(table[tmp_index].empty()){
						table[tmp_index].push_back(name);
						break;
					}
					else{
						tmp_index += (counter*counter);
						tmp_index = tmp_index % buckets;
						counter++;
						continue;
					}
				}
			}
			break;
	}


}

vector<string> read_data(){
	vector<string> names;
	ifstream input("names.txt");

	for(string line; getline(input, line); ){

		names.push_back(line);
	}
	input.close();
	return names;
}

int HashTable::multMethod(int key) {
	double a = (sqrt(5) - 1) / 2;
	int hash = (int) floor(buckets * (((double) key * a) - floor((double) key * a)));
	return hash;
}


int main(int argc, char *argv[]) {

	vector<string> names = read_data();


	clock_t tStart = clock();

	HashTable divHT_chain(names.size(), 1, 1);

	for(int i=0; i<names.size(); i++){
		divHT_chain.insert_item(names[i]);
	}
	//divHT_chain.display_hash_table();

	cout << "Chaining Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;


	tStart = clock();
	HashTable divHT_linear(names.size(), 1, 2);

	for(int i=0; i<names.size(); i++){
		divHT_linear.insert_item(names[i]);
	}
	//divHT_linear.display_hash_table();

	cout << "Linear Probing Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;


	tStart = clock();
	HashTable divHT_quadratic(names.size(), 1, 3);

	for(int i=0; i<names.size(); i++){
		divHT_quadratic.insert_item(names[i]);
	}
	//divHT_quadratic.display_hash_table();

	cout << "Quadratic Probing Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;


	return 0;
}
