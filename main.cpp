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

	this->linear_mod_collisions = 0;
	this->quadratic_mod_collisions = 0;

	this->linear_mul_collisions = 0;
	this->quadratic_mul_collisions = 0;

	this->linear_rad_collisions = 0;
	this->quadratic_rad_collisions = 0;
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
		case 3: hash = radixMethod(num, buckets);
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
				if(hash_method == 1){
					//cout << "linear mod collision: " << quadratic_mul_collisions << endl;
					linear_mod_collisions++;
				}
				else if(hash_method == 2){
					//cout << "linear mul collision: " << quadratic_mul_collisions << endl;
					linear_mul_collisions++;
				}
				else if(hash_method == 3){
  					//cout << "linear rad collision: " << quadratic_rad_collisions << endl;
					linear_rad_collisions++;
				}
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
				if(hash_method == 1){
					//cout << "quad mod collision: " << quadratic_mul_collisions << endl;
					quadratic_mod_collisions++;
				}
				else if(hash_method == 2){
					//cout << "quad mul collision: " << quadratic_mul_collisions << endl;
					quadratic_mul_collisions++;
				}
				else if(hash_method == 3){
					//cout << "quad rad collision: " << quadratic_rad_collisions << endl;
					quadratic_rad_collisions++;
				}
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

vector<string> read_data(string file_name){
	vector<string> strings;
	ifstream input(file_name);

	for(string line; getline(input, line); ){

		strings.push_back(line);
	}
	input.close();
	return strings;
}

int HashTable::multMethod(int key) {
	double a = (sqrt(5) - 1) / 2;
	int hash = (int) floor(buckets * (((double) key * a) - floor((double) key * a)));
	return hash;
}


int HashTable::radixMethod(int key, int buckets) {
	int newBase = 8;
	int remainder = 1;
	int dec = 1;
	int hash = key;
	while (key != 0) {
		remainder = key % newBase;
		key /= newBase;
		hash += remainder * dec;
		dec *= 10;
	}
	hash = hash % buckets;
	return hash;
}


int main(int argc, char *argv[]) {

	if(argc != 3){
		cout << "run with prg_name file_name bucket_padding" << endl;
		exit(1);
	}

	vector<string> names = read_data(argv[1]);

	clock_t tStart = clock();

	int val = atoi(argv[2]);

	HashTable divHT_chain(names.size()+val, 1, 1);

	for(int i=0; i<names.size(); i++){
		divHT_chain.insert_item(names[i]);
	}
	//divHT_chain.display_hash_table();

	cout << "Chaining Time Mod Method taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << endl;

	tStart = clock();
	HashTable divHT_linear(names.size()+val, 1, 2);

	for(int i=0; i<names.size(); i++){
		divHT_linear.insert_item(names[i]);
	}
	//divHT_linear.display_hash_table();

	cout << "Linear Probing Mod Method Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << "Linear Probing Mod Method Collisions: " << divHT_linear.linear_mod_collisions << endl;
	cout << endl;

	tStart = clock();
	HashTable divHT_quadratic(names.size()+val, 1, 3);

	for(int i=0; i<names.size(); i++){
		divHT_quadratic.insert_item(names[i]);
	}
	//divHT_quadratic.display_hash_table();

	cout << "Quadratic Probing Mod Method Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << "Quadratic Probing Mod Method Collisions: " << divHT_quadratic.quadratic_mod_collisions << endl;
	cout << endl;


	tStart = clock();

	HashTable divMT_chain(names.size()+val, 2, 1);

	for(int i=0; i<names.size(); i++){
		divMT_chain.insert_item(names[i]);
	}
	//divHT_chain.display_hash_table();

	cout << "Chaining Time Mult Method taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << endl;

	tStart = clock();
	HashTable divMT_linear(names.size()+val, 2, 2);

	for(int i=0; i<names.size(); i++){
		divMT_linear.insert_item(names[i]);
	}
	//divHT_linear.display_hash_table();

	cout << "Linear Probing Mult Method Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << "Linear Probing Mult Method Collisions: " << divMT_linear.linear_mul_collisions << endl;
	cout << endl;

	tStart = clock();
	HashTable divMT_quadratic(names.size()+val, 2, 3);

	for(int i=0; i<names.size(); i++){
		divMT_quadratic.insert_item(names[i]);
	}
	//divHT_quadratic.display_hash_table();

	cout << "Quadratic Probing Mult Method Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << "Quadratic Probing Mult Method Collisions: " << divMT_quadratic.quadratic_mul_collisions << endl;
	cout << endl;

	tStart = clock();

	HashTable radMT_chain(names.size()+val, 3 , 1);

	for(int i=0; i<names.size(); i++){
		radMT_chain.insert_item(names[i]);
	}
	//radMT_chain.display_hash_table();

	cout << "Chaining Time Radix Method taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << endl;

	tStart = clock();
	HashTable radMT_linear(names.size() + val, 3, 2);

	for (int i = 0; i < names.size(); i++) {
		radMT_linear.insert_item(names[i]);
	}

	//radMT_chain.display_hash_table();

	cout << "Linear Probing Radix Method Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << "Linear Probing Radix Method Collisions: " << radMT_linear.linear_rad_collisions << endl;
	cout << endl;

	tStart = clock();
	HashTable radMT_quadratic(names.size()+val, 3, 3);

	for(int i=0; i<names.size(); i++){
		radMT_quadratic.insert_item(names[i]);
	}
	//radMT_quadratic.display_hash_table();

	cout << "Quadratic Probing Radix Method Time taken: " <<  (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
	cout << "Quadratic Probing Radix Method Collisions: " << radMT_quadratic.quadratic_rad_collisions << endl;
	cout << endl;
	return 0;
}
