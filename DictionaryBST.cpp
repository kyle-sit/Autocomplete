/*
 * Filename: DictionaryBST.cpp
 * Name: Kyle Sit, Louis Leung
 * Date: 5/12/16
 * Description: Contains methods to construct a BST to store a dictionary 
 */

#include "util.hpp"
#include "DictionaryBST.hpp"
#include <set>
#include <iostream>
#include <string>

/* 
 * Function name: constructor
 * Purpose: Create a Dictionary that uses a BST back end
 * Return: none
 */
DictionaryBST::DictionaryBST(){
  /* constructs a set as our BST */
  myBST = new std::set<std::string>();
}

/* 
 * Function name: insert
 * Purpose: insert a word into the dictionary
 * Parameters: string - word to insert
 * Return: true or false if insertion is successful
 */
bool DictionaryBST::insert(std::string word)
{
  if( (myBST->insert(word)).second ) {
    return true;
  }
  return false;
}


/* 
 * Function name: find
 * Purpose: find a word into the dictionary
 * Parameters: string - word to find
 * Return: true or false if find is successful
 */
bool DictionaryBST::find(std::string word) const
{
  if( myBST->find(word) == myBST->end() ) {
    return false;
  }
  return true;
}

/* 
 * Function name: destructor
 * Purpose: deallocate memory for the tree
 * Return: none
 */
DictionaryBST::~DictionaryBST(){
	delete(myBST);
}
