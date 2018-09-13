/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
 */

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>

class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store


	/* Parse and return values for command,
		 word, and definition to run the dictionary */
	void parse(string src, string &comm, string &word, string &def){
		int count = 0;
		for (int i = 0; i < src.length(); i++){
			if(src[i] == ' ' && count <= 1)
			count++;
			else if (count == 0)
			comm += src[i];
			else if (count == 1)
			word += src[i];
			else if (count > 1)
			def += src[i];
		}
		comm.erase(remove(comm.begin(), comm.end(), '"'), comm.end());
		word.erase(remove(word.begin(), word.end(), '"'), word.end());
		def.erase(remove(def.begin(), def.end(), '"'), def.end());
		//cout << "Word = " << word << endl << "Def = " << def << endl;
	}


	/* Function to parse json file and insert any thing inside */
	void LoadJSON(string filename){
		ifstream myfile(filename);
		string word = "";
		Word var;
		//int count = 0;
		if(myfile.is_open()){
		getline(myfile, word);
		getline(myfile, word);
		while(!myfile.eof()){
			int count = 14;
			string hold = "";
			getline(myfile, word);
			if(word.length() > 14){
			for(int i = 14; i < word.length(); i++){
				count++;
				if(word[i] == '"'){
					break;
				}
				else{
				hold += word[i];
			}
			}
			var.myword = hold;
			hold = "";
			count += 17;
			while(count < word.length()){
				if(word[count + 1] == '}'){
					break;
				}
				else{
				hold += word[count];
				count++;
			}
		}
		var.definition = hold;
		_dict.insert(var.myword, var);
	}
	}
}
	else{cout << "Not open" << endl;}
}

  /* Function to parse json file and remove any thing inside */
	void UnloadJSON(string filename){
		ifstream myfile(filename);
		string word = "";
		Word var;
		if(myfile.is_open()){
		getline(myfile, word);
		getline(myfile, word);
		while(!myfile.eof()){
			int count = 14;
			string hold = "";
			getline(myfile, word);
			if(word.length() > 14){
			for(int i = 14; i < word.length(); i++){
				count++;
				if(word[i] == '"'){
					break;
				}
				else{
				hold += word[i];
			}
			}
			_dict.remove(hold);
		}
	}
	}
	else{cout << "Not open" << endl;}
}

		/* 3 Parts, command, word, definition */
	void parseline( string line ) {
		string cmmd = "", word = "", def = "";
		parse(line, cmmd, word, def);
		Word var(word, def);
		// Specifically added for debugging rehash function, but good for testing
		// in run_ui() if interested for grading. simple way to get rehash called.
		if(cmmd == "rehash")
		_dict.prehash();
		if(cmmd == "add"){
			Word *some = _dict.find(word);
			if (some == nullptr)
			_dict.insert(word, var);
			else{
			some->definition = def;
		}
		some = _dict.find(word);
	//	cout << "ADD WORD: " << some->to_string() << endl;
		}
		else if(cmmd == "help"){
			cout << "add   “word”   “definition”"
			<< " ->   Add   (or   update!)   a   word   and   it’s   definition.   Must   handle   quotes "
			<< endl << "remove   “word” ->   Remove   a   given   word.   Must   handle   quotes" << endl
			<< "define   “word” ->   Define   a   word   by   printing   out   it’s   definition   or   “unknown   word” "
			<< endl << "load   “filename” ->   Load   in   a   JSON   file   of   dictionary   words"
			<< endl << "unload “filename” ->   Remove   words   from   a   given   JSON   file   of   dictionary   words"
			<< endl <<"size ->   Print   out   current   number   of   words   in   the   dictionary"
			<< endl <<"clear ->   Remove   ALL   words   from   the   dictionary"
			<< endl << "print [#words] ->   Print   out   all   words,   unless   user   gives   a   maximum   number"
			<< endl << "random ->   Print   out   a   single   word   chosen   randomly   from   the   dictionary"
			<< endl << "quit ->   Quit   the   user   interface   and   shut   down" << endl;
		}
		else if(cmmd == "remove"){
			_dict.remove(word);
		}
		else if(cmmd == "define"){
			Word * found;
			found = _dict.find(word);
			if(found != nullptr){
				//cout << "Word = " << found->myword << endl << "Def = " << found->definition << endl;
				cout << "Found: " << found->to_string() << endl;
			}
			else{
				cout << "Word not found" << endl;
			}

		}
		else if(cmmd == "load"){
			LoadJSON(word);
		}
		else if(cmmd == "unload"){
			UnloadJSON(word);
		}
		else if(cmmd == "size")
			cout << "Size = " << _dict.size();
		else if(cmmd == "clear"){
			_dict.clear();
			cout << "Dictionary Cleared";
		}
		else if(cmmd == "print"){
	  //**********************************************************
			int i = 0;
			std::list<Word> thing;
			if(word == ""){
			while(i < _dict.bucket_count()){
				if(!_dict.hash_table[i].empty()){
					thing = _dict.hash_table[i];
					while(!thing.empty()){
						cout << thing.back().myword << endl;
						thing.pop_back();
					}
				}
				i++;
			}
		}
			else{
				int n = stoi(word), count = 0;
				while(count < n && i < _dict.bucket_count()){
					if(!_dict.hash_table[i].empty()){
						thing = _dict.hash_table[i];
						while(count < n && !thing.empty()){
							cout << thing.back().myword << endl;
							if(thing.back().myword != "")
							count++;
							thing.pop_back();
						}
					}
					i++;
				}
			}
		}
		//***********************************************************
		else if(cmmd == "random"){
			std::random_device rd;
			int ran = 0, count = 0;
			std::list<Word> thing;
			while(_dict.hash_table[ran].empty()){
			ran = rd() % _dict.bucket_count();
		}
		thing = _dict.hash_table[ran];
		ran = rd() % _dict.hash_table[ran].size();
		while(count < ran){
			thing.pop_back();
			count++;
		}
		cout << "Random Word: " << thing.back().myword << endl << "Definition: " << thing.back().definition;
		}
		else if(cmmd == "quit"){
			exit(0);
		}
		cout << endl;
	}

	public:
		Dictionary()	// Default constructor
		 { }

		 string lowercase(string lower){
			 string ret = "", hold = "";
			 for(int i = 0; i < lower.length(); i++){
				 if(lower[i] >= 65 && lower[i] <= 90)
					 ret += lower[i] + 32;
				 else
				 ret += lower[i];
			 }
			 return ret;
		 }
	/**
	 *  Run the main dictionary user interface
	 */
	void run_ui() {
		// print out header
	//	cout << "+------------------------------------------+" << endl;
	//	cout << "|-- Welcome to the best dictionary evar! --|" << endl;
	//	cout << "+------------------------------------------+" << endl;

		string instr;
	//	cout << " Enter command (^D or EOF quits): ";

		// read in user input until eof
		while (getline(cin, instr)) {
		//	cout << endl << " --debug-- Entered command: " << instr << endl;
			parseline(instr);
			// call function based on line contents
			// print results

			// cout << "Enter command: ";
		}
		cout << endl;
	}

};



#endif
