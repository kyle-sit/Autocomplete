/*
 * Authors: Louis Leung, Kyle Sit
 */


#include "util.hpp"
#include "DictionaryBST.hpp"
#include <set>
#include <iostream>
#include <string>

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
  /* constructs a set as our BST */
  myBST = new std::set<std::string>;
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	/* used to hold return pair of iterator pointing to elem
	 * and bool of successful insert */
	std::pair<std::set<std::string>::iterator,bool> ret;
	/*insert and return true if inserted */
  myBST->insert(word);
	return (ret.second);
}
	
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	std::set<std::string>::iterator it;
	it = myBST->find(word);
	if (it == myBST->end()) {
		return false;
	}
	else {
		return true;
	}	
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
	delete(myBST);
}
