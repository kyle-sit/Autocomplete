#include "DictionaryHashtable.hpp"
#include <unordered_set>

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
  hashTable = new std::unordered_set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  if( (hashTable->insert(word)).second ) {
    return true;
  }
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  if( hashTable->find(word) == hashTable->end() ) {
    return false;
  }
  return true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
  delete hashTable;
}
