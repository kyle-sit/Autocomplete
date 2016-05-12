#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <string>
#include <vector>
#include <queue>
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
  for( unsigned int it = 0; it < word.length(); ++it) {
    // Special case for spaces
    if( (int)(word[it]) == SPACE ) {
      if( (temp->nodes)[ALPHABET_SIZE] == nullptr ) {
        return false;
      }
      temp = (temp->nodes)[ALPHABET_SIZE];
    }
    else {
      // Create new node on heap for letter if it is not already in the tree
      if( (temp->nodes)[(int)(word[it]) - (int)'a'] == nullptr ) {
         return false;
      }
      // Move to the next node in the string
      temp = (temp->nodes)[(int)(word[it]) - (int)'a'];
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

std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
                                                unsigned int num_completions) {
  std::vector<std::string> words(num_completions);

  DictTrieNode * temp = root;
   
  // Loop through the characters of the string and add to tree
  for( unsigned int it = 0; it < prefix.length(); ++it) {
    // Special case for spaces
    if( (int)(prefix[it]) == SPACE ) {
      if( (temp->nodes)[ALPHABET_SIZE] == nullptr ) {
        return words;
      }
      temp = (temp->nodes)[ALPHABET_SIZE];
    }
    else {
    // Create new node on heap for letter if it is not already in the tree
      if( (temp->nodes)[(int)(prefix[it]) - (int)'a'] == nullptr ) {
         return words;
      }
      // Move to the next node in the string
      temp = (temp->nodes)[(int)(prefix[it]) - (int)'a'];
    }
  }
   
  std::priority_queue<DictTrieNode*, std::vector<DictTrieNode*>,
                                            DTNodePtrComp> DTNodeMinHeap;
  unsigned int numInserted = 0;
 
  autoCompletion( numInserted, num_completions, DTNodeMinHeap, temp );
 
  if( DTNodeMinHeap.empty() ) {
     return words;
  }
   
  std::vector<std::string>:: iterator it = words.end();
  for( unsigned int index = 0; index < num_completions; index++ ) {
    --it;
    words.insert(it, (DTNodeMinHeap.top())->nodeWord);
    DTNodeMinHeap.pop();
  }
    
  return words;
}

/* Recursive methods for searching autocompletions */
void DictionaryTrie::autoCompletion( unsigned int & numInserted, 
                     unsigned int num_completions,
                     std::priority_queue<DictTrieNode*, 
                     std::vector<DictTrieNode*>, DTNodePtrComp> & heap, 
                     DictTrieNode * current ) {
  //Create temporary maxHeap in order to store Breadth first search and
  //populate it
  std::priority_queue<DictTrieNode*, std::vector<DictTrieNode*>,
                                                           DTNodePtrComp2> BFS;
  for( auto node : current->nodes ) {
    if( node != nullptr ) {
      BFS.push( node->maxFrequency );
    }
  }
  
  //If our BFS is empty and had no nodes then we return
  if( BFS.empty() ) {
    return;
  }
  
  //Pop from maxHeap as many times as num_completions and use in dif situations
  unsigned int iterations = 0;
  while( iterations < num_completions ) {
    
    //If our minHeap is full we want to compare popped BFS to popped heap
    if( numInserted == num_completions ) {
      if( BFS.top() > heap.top() ) {
        heap.pop();
        heap.push(BFS.top());
        autoCompletion( numInserted, num_completions, heap, BFS.top() );
        BFS.pop();
      }
    }
    //Otherwise we just want to insert into heap
    else {
      heap.push(BFS.top());
      numInserted++;
      autoCompletion( numInserted, num_completions, heap, BFS.top() );
      BFS.pop();
    }
    iterations++;
  }
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

