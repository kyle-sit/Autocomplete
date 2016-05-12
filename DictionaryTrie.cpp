#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <string>
#include <iostream>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  root = new DictTrieNode();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // Use temporary node to traverse tree
  DictTrieNode * temp = root;
 
  /* Loop through the characters of the string and add to tree
  for( std::string::iterator it = word.begin(); it != word.end(); ++it) {
    // Special case for spaces
    if( (int)(*it) == SPACE ) {
      if( (temp->nodes)[ALPHABET_SIZE] == nullptr ) {
         (temp->nodes)[ALPHABET_SIZE] = new DictTrieNode();
         ((temp->nodes)[ALPHABET_SIZE])->parent = temp;  
      }
      temp = (temp->nodes)[ALPHABET_SIZE];
    }
    // Create new node on heap for letter if it is not already in the tree
    else { 
      if( (temp->nodes)[(int)(*it) - (int)'a'] == nullptr ) {
        (temp->nodes)[(int)(*it) - (int)'a'] = new DictTrieNode();
        ((temp->nodes)[(int)(*it) - (int)'a'])->parent = temp;  
      }
      // Move to the next node in the string
      temp = (temp->nodes)[(int)(*it) - (int)'a'];
    }
  }*/
  
  // Loop through the characters of the string and add to tree
  for( size_t it = 0; it != word.length(); ++it) {
    // Special case for spaces
    if( (int)(word[it]) == SPACE ) {
      if( (temp->nodes)[ALPHABET_SIZE] == nullptr ) {
         (temp->nodes)[ALPHABET_SIZE] = new DictTrieNode();
         ((temp->nodes)[ALPHABET_SIZE])->parent = temp;  
      }
      temp = (temp->nodes)[ALPHABET_SIZE];
    }
    // Create new node on heap for letter if it is not already in the tree
    else { 
      if( (temp->nodes)[(int)(word[it]) - (int)'a'] == nullptr ) {
        (temp->nodes)[(int)(word[it]) - (int)'a'] = new DictTrieNode();
        ((temp->nodes)[(int)(word[it]) - (int)'a'])->parent = temp;  
      
      }
      // Move to the next node in the string
      temp = (temp->nodes)[(int)(word[it]) - (int)'a'];
    }
  }

  // Check if word already exists
  if( temp->leaf == true ) {
    return false;
  }
  // Set node as a leaf and set its frequency
  temp->leaf = true;
  temp->frequency = freq;
  temp->nodeWord += word;
  //Set max frequencies of nodes, current node will hold max freq of itself
  if( temp->maxFrequency == nullptr ) {
    temp->maxFrequency = temp;
    setMaxFrequencies(temp);
  }
  else {
    if( freq >= temp->maxFrequency->frequency ) {
      temp->maxFrequency = temp;
      setMaxFrequencies(temp);
    }
  }
  
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  // Use temporary node to traverse tree
  DictTrieNode * temp = root;
  
  // Loop through the characters of the string and add to tree
  for( std::string::iterator it = word.begin(); it != word.end(); ++it) {
    // Special case for spaces
    if( (int)(*it) == SPACE ) {
      if( (temp->nodes)[ALPHABET_SIZE] == nullptr ) {
        return false;
      }
      temp = (temp->nodes)[ALPHABET_SIZE];
    }
    else {
      // Create new node on heap for letter if it is not already in the tree
      if( (temp->nodes)[(int)(*it) - (int)'a'] == nullptr ) {
         return false;
      }
      // Move to the next node in the string
      temp = (temp->nodes)[(int)(*it) - (int)'a'];
    }
  }

  return temp->leaf; 
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/* Traverse back up the word just inserted resetting the maxFrequency node
 * field to appropriate values */
void DictionaryTrie::setMaxFrequencies(DictTrieNode * currentNode) {

  if (currentNode -> parent == nullptr) {
    return;
  }

  if (currentNode -> parent -> maxFrequency == nullptr) {
    currentNode -> parent -> maxFrequency = currentNode -> maxFrequency;
    setMaxFrequencies(currentNode -> parent);
  }

  else if (isMoreThan(currentNode->maxFrequency,currentNode->parent->maxFrequency)) {
    currentNode->parent->maxFrequency = currentNode->maxFrequency;
      setMaxFrequencies(currentNode->parent);
  }
  return;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}

/* Overloaded operator for DictTrieNode */
bool DictTrieNode::operator<(const DictTrieNode& other) const {
  if( frequency != other.frequency ) {
    return frequency > other.frequency;
  }
  return false;
}

/* Overloaded operator for DictTrieNode */
bool DictTrieNode::operator>(const DictTrieNode& other) const {
  if( frequency != other.frequency ) {
    return frequency < other.frequency;
  }
  return false;
}

/* Comparator method */
bool isMoreThan( DictTrieNode* one, DictTrieNode* other ) {
  return ((one->frequency) > (other->frequency));
}

