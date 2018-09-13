/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
/*
	private:
		void rehash();
		int hash_function(KEYTYPE key);

	public:
		bool insert(KEYTYPE key, VALTYPE val);
		bool contains(KEYTYPE key);
		int remove(KEYTYPE key);
		VALTYPE & find(KEYTYPE key);
		int size();            // Elements currently in table
		bool empty();          // Is the hash empty?
		float load_factor();   // Return current load factor
		void clear();          // Empty out the table
		int bucket_count();    // Total number of buckets in table
*/

template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
	private:

		/**
		 *  Rehash the table into a larger table when the load factor is too large
		 */
		void rehash() {
			std::vector<std::list<VALTYPE>> hold = hash_table;
			int i = 0;
		/*	while (i < hash_table.capacity()){
				hold.push_back(hash_table[i]);
				i++;
			} */
			hash_table.clear();
			hash_table.resize(findprime(hash_table.capacity() * 2));
			i = 0;
			Tsize = 0;
			while (i < hold.capacity()){
				if(!hold[i].empty()){
				//	cout << hold[i].back().myword << endl;
					insert(hold[i].back().myword, hold[i].back());
					hold[i].pop_back();
				}
				else{
					hold[i].clear();
					i++;
				}
			}
		}

		/* For rehash, returns next prime number */
		int findprime(int prime){
			int n = prime + 1;
			bool found = false;
			if(isprime(n))
			found = true;
			while (!found){
				n += 2;
				if(isprime(n))
				found = true;
			}
			return n;
		}

		/* For rehash, gives tests if number is prime */
		bool isprime(int n){
			for(int i = 2; i <= n/2; i++){
				if(n % i == 0)
				return false;
			}
			return true;
		}


		/**
		 *  Function that takes the key (a string or int) and returns the hash key
		 *   This function needs to be implemented for several types it could be used with!
		 */
		/* Returns key for an int in hash table */
		int hash_function(int key) {
			// cout << " Hashing with int type keys." << endl;
			return key % hash_table.capacity();
		}

		/* Returns key for a string in hash table */
		int hash_function(string key) {
			// cout << " Hashing with string type keys." << endl;
			int sum = 0;
			string hold = lowercase(key);
			for (int i = 0; i < hold.length(); i++){
				sum += (int)hold[i];
			}
			return sum % hash_table.capacity();
		}

		/* If key is an int instead of string runs comparison */
		bool cmpCont(int key, int num){
			if (num == key)
				return true;
			else{
				return false;
			}
		}

		/* compare strings, convert them to lowercase to avoid
			 capitals causing issues.*/
		bool cmpCont(string key, string word){
			string hold = lowercase(word);
			string cmp = lowercase(key);
			if (hold == cmp)
				return true;
			else{
				return false;
			}
		}

		//std::list<VALTYPE>* cmpRem()
	public:
		// Variables:
		std::vector<std::list<VALTYPE>> hash_table;
		int Tsize = 0;


		/**
		 *  Basic constructor
		 */
		Hashtable( int startingSize = 101 )
		{
			hash_table.resize(startingSize);
		}

		/**
		 *  Add an element to the hash table
		 */
		bool insert(KEYTYPE key, VALTYPE val) {
			int spot = hash_function(key);
			hash_table[spot].push_front(val);
			Tsize++;
			if(load_factor() >= 1.0)
			rehash();
			return contains(key);
		}

		/**
		 *  Return whether a given key is present in the hash table
		 */
		bool contains(KEYTYPE key) {
			int spot = hash_function(key);
			string place = "";
			std::list<VALTYPE> hold = hash_table.at(spot);
		  auto iterator = hold.begin();
			for(; iterator != hold.end(); ++iterator){
				place = iterator->myword;
				if(cmpCont(key, place)){
					return true;
				}
			}
			return false;
		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed
		 */
		int remove(KEYTYPE key) {
			int ret = 0;
			string place = "";
			int spot = hash_function(key);
			std::list<VALTYPE> *hold = &hash_table[spot];
		  auto iterator = hold->begin();
			for(int i = 0; i < hold->size(); i++){
				if(iterator->myword != "")
				place = iterator->myword;
				if(cmpCont(key, place)){
					hold->erase(iterator);
					ret++;
					Tsize--;
				}
				iterator++;
			}
			return ret;
		}

		/**
		 *  Searches the hash and returns a pointer
		 *   Pointer to Word if found, or nullptr if nothing matches
	 	*/
		VALTYPE *find(KEYTYPE key){
			int spot = hash_function(key);
			string place = "";
			std::list<VALTYPE> *hold = &hash_table[spot];
			auto iterator = hold->begin();
			for(int i = 0; i < hold->size(); i++){
				if(iterator->myword != "")
				place = iterator->myword;
				if(cmpCont(key, place)){
					return &(*iterator);
				}
			}
			return nullptr;
		}


		/**
		 *  Return current number of elements in hash table
		 */
		int size() {
			return Tsize;
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 */
		bool empty() {
			for (int i = 0; i < hash_table.size(); i++){
				if(!hash_table.at(i).empty())
				return false;
			}
			return true;
		}

		/**
		 *  Calculates the current load factor for the hash
		 */
		float load_factor() {
			//return _hash.load_factor();
			double ret = (double)size() / (double)bucket_count();
 			return ret;
		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 */
		int bucket_count() {
			return hash_table.size();
		}

		string lowercase(string lower){
			string ret = "";
			for(int i = 0; i < lower.length(); i++){
				if(lower[i] == ' '){}
				else if(lower[i] >= 65 && lower[i] <= 90)
					ret += lower[i] + 32;
				else
				ret += lower[i];
			}
			return ret;
		}

		/**
		 *  Deletes all elements in the hash
		 */
		void clear() {
			for (int i = 0; i < hash_table.size(); i++){
						Tsize -= hash_table[i].size();
						hash_table[i].clear();
			}
		}

		/* Not actually necessary just allows
			 for manual call of rehash function */
		void prehash(){
			rehash();
		}

};



#endif
