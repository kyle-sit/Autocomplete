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
  myBST = new std::set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
  if( (myBST->insert(word)).second ) {
    return true;
  }
  return false;
}
	
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  if( myBST->find(word) == myBST->end() ) {
    return false;
  }
  return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
	delete(myBST);
}
