/*
 * Filename: DictionaryHashtable.cpp
 * Name: Kyle Sit, Louis Leung
 * Date: 5/12/16
 * Description: Contains methods for constructing a Dictionary using hashtables
 */
#include "util.hpp"
#include "DictionaryHashtable.hpp"
#include <unordered_set>

/* 
 * Function name: constructor
 * Purpose: create a new dictionary using a hashset back end
 * Return: none
 */
DictionaryHashtable::DictionaryHashtable(){
  hashTable = new std::unordered_set<std::string>();
}

/* 
 * Function name: insert
 * Purpose: insert a word into the dictionary
 * Parameters: string - word to insert
 * Return: true or false if insertion is successful
 */
bool DictionaryHashtable::insert(std::string word)
{
  if( (hashTable->insert(word)).second ) {
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
bool DictionaryHashtable::find(std::string word) const
{
  if( hashTable->find(word) == hashTable->end() ) {
    return false;
  }
  return true;
}

/* 
 * Function name: destructor
 * Purpose: deallocate the memory of our tree
 * Return: none
 */
DictionaryHashtable::~DictionaryHashtable(){
  delete hashTable;
}
