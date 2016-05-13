/**
 * Filename: DictionaryTrie.hpp
 * Name: Kyle Sit
 * Date: 4/21/16
 * Description: Contains implementation of HCNode methods 
 *
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <queue>

#define ALPHABET_SIZE 26
#define SPACE 32



/** A class, instances of which are nodes in an DictionaryTrie.
*/
class DictTrieNode {
	friend bool isMoreThan( DictTrieNode* one, DictTrieNode* other );

  public:
    DictTrieNode *nodes[ALPHABET_SIZE + 1] = {nullptr};
    DictTrieNode *parent;
    DictTrieNode *maxFrequency;
    std::string nodeWord;
    unsigned int frequency;
    std::string completedWord = "";
    bool leaf;

    DictTrieNode() {
      frequency = 0;
      leaf = false;
      parent = nullptr;
      maxFrequency = nullptr;
      nodeWord = "";
      /*for( int i = 0; i < ALPHABET_SIZE + 1; i++ ) {
        nodes[i] = nullptr;
      }*/
    }

    bool operator<(const DictTrieNode& other) const;
    bool operator>(const DictTrieNode& other) const;
};

  /* Comparator for node pointers */
  bool isMoreThan( DictTrieNode* one, DictTrieNode* other );

class DTNodePtrComp {
public:
    bool operator()(DictTrieNode*& lhs, DictTrieNode*& rhs) const {
        return *lhs < *rhs;
    }
};

class DTNodePtrComp2 {
public:
    bool operator()(DictTrieNode*& lhs, DictTrieNode*& rhs) const {
        return *rhs < *lhs;
    }
};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Set the maximumFrequency node field of each node up the word after
   * being inserted
   */
  void setMaxFrequencies(DictTrieNode * currentNode);

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
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Recursive method for finding autocompletions */
  void autoCompletion( unsigned int & numInserted,unsigned int num_completions,
                       std::priority_queue<DictTrieNode*, 
                       std::vector<DictTrieNode*>, DTNodePtrComp2> & heap, 
                       DictTrieNode * current );
  
  /* Implemented in destructor */
  void deleteAll( DictTrieNode* current );
  
  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here
  DictTrieNode *root;


};

#endif // DICTIONARY_TRIE_HPP
