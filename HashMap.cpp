#include <bits/stdc++.h>
#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

//Constructor for the hashmap. //when creating the
//map, make sure you initialize the values to
//NULL so you know whether that index has a key
//in it or is set to NULL
// ****here you’re just looping through the map of hashNodes (a pointer to an array of
//pointers to hashNodes) and initializing the array to NULL

hashMap::hashMap(bool hash1, bool coll1) {
	mapSize = 101;
	numKeys = 0;
	hashfn = hash1;
	collfn= coll1;
	map = new hashNode*[mapSize];
	for(int i = 0; i < mapSize; ++i){
		map[i] = NULL;
	}
}

//
int hashMap::hashFunc(string k){
	return k.length() % mapSize;
}

//Adds the string (v) while iterating over the key and checks to see if the key is empty or not
void hashMap::addKeyValue(string k, string v) {
	int key = hashFunc(k);
	for(int i = 0; i < mapSize; ++i){

		//if(key== NULL){

		//}
	}

}

//Finds the key in the hashmap. No loops or 50% grade deduction. Besides, finding in hashing is O(1) not O(n) ya noob!
int hashMap::getIndex(string k) {
	int key = 0;
	int ascii = 0;
	for(int i = 0; i < k.length(); ++i){
			ascii += (int)(k[i]) - 48;
	}
	if((float)numKeys/mapSize == 0.7){
		reHash();
	}
	if(hashfn == true){
		calcHash1(k);
	}
	else if(hashfn== false){
		calcHash2(k);
	}
	else if(collfn == true){
		coll1(ascii,key, k);
	}
	else if(collfn == false){
		coll2(ascii,key, k);
	}
	else{
		key = NULL;
	}


	return key;
}

//This function hits different. This one opts to find the length of the string, then iterates over the mapsize and the string length as well while
//modding over the mapSize to get the hash.
int hashMap::calcHash2(string k){
	int conversion = 0;
	int length = k.length();
	for(int j = 0; j < mapSize; ++j){
		for(int i = length - 1; i > 0; --i){
			conversion = (13 * conversion + ((int)k[i][length-i-1])) % mapSize;
		}
	}
	return conversion;
}


//Goes over each character, converts it to ascii and mods it by the map size
int hashMap::calcHash1(string k){
	int conversion = 0;
	for(int i = 0; i < k.length(); ++i){
		conversion += (int)(k[i]) - 48;
	}
	conversion = conversion % mapSize;
	return conversion;
}

//Binary search must be used here
void hashMap::getClosestPrime() {
	int closePrime = 0;
	int number = calcHash1(first);
	mapSize = mapSize * 2;
	int middle = currSize / 2;


	for(int i = 2; i < 9; ++i){
		if((number % i) != 0 && (number != i)){
			closePrime = number;
		}
	}
	mapSize = closePrime;
}

//Rehashes the array via copying the old values in the new data then deleting the old value
void hashMap::reHash() {
	int existSize = mapSize;
	existSize*= 2;
	hashNode **temp = map;
	map = new hashNode *[existSize];
	while(temp!=NULL){
		getIndex(temp->first);
	}

	delete [] map;
}

//Probing starts here, this one is a quadratic probing
int hashMap::coll1(int h, int i, string k) {
	int collide = 0;
	int convert = 0;
	for(int j = 0; j < k.length(); ++j){
		convert += (int)k[j] - 48;
	}
	convert = convert % mapSize;

	for(int a = 0; a < i; ++a){
		h = (h + (int)pow(i, i)) % mapSize;
		if(h == convert){
			collide = h;
		}
		else if(h == 0){
			k = h[i];
			collide = i;
		}
		else{
			collide = -1;
		}
	}

	return collide;

}
//Other methods for probing collisions, in this case linear probing is used
int hashMap::coll2(int h, int i, string k) {
	int collide = 0;
	int convert = 0;
	for(int j = 0; j < k.length(); ++j){
		convert += (int)k[j] - 48;
	}
		convert = convert % mapSize;

		for(int a = 0; a < i; ++a){
			h = (int)(h + pow(i, i)) % mapSize;

			if(h == convert){
				k[a] = h[a];
				collide = a;
			}
			else if(h == 0){
				k[a] = h[a];
				collide = i;
			}
			else{
				collide = -1;
			}
		}


}



//Prints out the map
void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


