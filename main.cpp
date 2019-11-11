#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "HTHeader.h"


HashTable::HashTable(int b, int func){
	this->buckets = b;
	table = new list<string>[buckets];
	this->func = func;
}


int HashTable::make_hash(string str){

	int num = 0;

	for(int i=0; i<str.size(); i++){
		//cout << (int)str[i] << endl;
		num += (int)str[i];
	}

	switch (func) {
		case '1': int hash = num % buckets;
							break;
		case '2': int hash = multMethod(num);
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

}


void HashTable::insert_item(string name) {
	int index = make_hash(name);
	table[index].push_back(name);
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

HashTable::multMethod(int key) {
	double a = (sqrt(5) - 1) / 2;
	int hash = (int) floor(buckets * (((double) key * a) - floor((double) key * a)));
}


int main(int argc, char *argv[]) {

	vector<string> names = read_data();

	HashTable divHT(names.size(), 1);

	for(int i=0; i<names.size(); i++){
		divHT.insert_item(names[i]);
	}
	divHT.display_hash_table();

	HashTable multHT(names.size(), 2);
	for (int i=0; i<names.size(); i++) {
		multHT.insert_item(names[i]);
	}
	multHT.display_hash_table();


	return 0;
}
