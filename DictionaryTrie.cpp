/*
 * Filename: DictionaryTrie.cpp
 * Name: Kyle Sit
 * Date: 5/12/16
 * Description: Contains implementation of DictionaryTrie, DictTrieNode, and
 * comparison classes 
 */
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

/* 
 * Function name: constructor
 * Purpose: create a dicitonary using a multiway trie
 * Return: none
 */
DictionaryTrie::DictionaryTrie(){
  root = new DictTrieNode();
}

/* 
 * Function name: insert
 * Purpose: Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string)
 * Parameters: string - word to insert
 * freq - frequency of that word
 * Return: true or false if insertion is successful
 */
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

/* 
 * Function name: find
 * Purpose: find a word in the dictionary
 * Parameters: string - word to find
 * Return: true or false if find is successful
 */
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

/* 
 * Function name: predictCompletions
 * Purpose: Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 * Parameters: prefix - the start of the word
 *             num_completions - the number of outputs we want
 * Return: vector of strings
 */

std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
                                                unsigned int num_completions) {
  std::vector<std::string> words;

  
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
  
  //Create a max heap for BFS
  std::priority_queue<DictTrieNode*, std::vector<DictTrieNode*>,
                                            DTNodePtrComp2> DTNodeMaxHeap;
  unsigned int numInserted = 0;
 
  //Delegate to submethod
  autoCompletion( numInserted, num_completions, DTNodeMaxHeap, temp );
  
  //Return if nothing
  if( DTNodeMaxHeap.empty() ) {
     return words;
  }
   
  //For loop for putting words into a vector to return 
  //std::vector<std::string>:: iterator it = words.end();
  for( unsigned int index = 0; index < num_completions; index++ ) {
    //--it; 
    words.push_back((DTNodeMaxHeap.top())->nodeWord);
    DTNodeMaxHeap.pop();
  }

  //std::reverse(words.begin(), words.end());

    
  return words;
}

/* 
 * Function name: autoCompletion
 * Purpose: Recursive mthod for searching using a BFS
 * Parameters: numInserted - dummy
 *             num_completions - passed in
 *             heap - our persisting maxheap
 *             current - the node we are currently on
 * Return: none
 */
/* Recursive methods for searching autocompletions */
void DictionaryTrie::autoCompletion( unsigned int & numInserted, 
                     unsigned int num_completions,
                     std::priority_queue<DictTrieNode*, 
                     std::vector<DictTrieNode*>, DTNodePtrComp2> & heap, 
                     DictTrieNode * current ) {
  
  //For loop to go through children
  for( auto node : current->nodes ) {
    if( node != nullptr ) {
      //Recursive call for each child
      autoCompletion( numInserted, num_completions, heap, node );
      //push if its a leaf
      if( node->leaf ) {
        heap.push( node );
      }
    }
  }

  /*
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
    if( BFS.empty() ) {
      return;
    }

    //If our minHeap is full we want to compare popped BFS to popped heap
    if( numInserted == num_completions ) {
      if( BFS.top() > heap.top() ) {
        heap.pop();
        if( BFS.top() != heap.top() ) {
          heap.push(BFS.top());
        }
        for( int index = 0; index < ALPHABET_SIZE + 1; index++ ) {
          if( (current->nodes)[index] != nullptr ) {
            if( (current->nodes)[index]->maxFrequency == BFS.top() ) {
              current = (current->nodes)[index];
              break;
            }
          }
        }
        autoCompletion( numInserted, num_completions, heap, current );
        BFS.pop();
      }
    }
    //Otherwise we just want to insert into heap
    else {
      if( !heap.empty() ) {
        if( BFS.top() != heap.top() ) {
          heap.push(BFS.top());
          numInserted++;
        }
      }
      else {
        heap.push(BFS.top());
        numInserted++;
      }
      for( int index = 0; index < ALPHABET_SIZE + 1; index++ ) {
        if( (current->nodes)[index] != nullptr ) {
          if( (current->nodes)[index]->maxFrequency == BFS.top() ) {
            current = (current->nodes)[index];
            break;
         }
        }
      }
      autoCompletion( numInserted, num_completions, heap, current );
      BFS.pop();
    }
    iterations++;
  }*/
}


/* 
 * Function name: setMaxFrequencies
 * Purpose:

* Traverse back up the word just inserted resetting the maxFrequency node
 * field to appropriate values */
void DictionaryTrie::setMaxFrequencies(DictTrieNode * currentNode) {
	// if we're at root node 
  if (currentNode -> parent == nullptr) {
    return;
  }
	//if no maxFrequency pointer set it to itself
  if (currentNode -> parent -> maxFrequency == nullptr) {
    currentNode -> parent -> maxFrequency = currentNode -> maxFrequency;
    setMaxFrequencies(currentNode -> parent);
  }
  //if parents max freq is less htan, set it to currents max freq
  else if (isMoreThan(currentNode->maxFrequency,currentNode->parent->maxFrequency)) {
    currentNode->parent->maxFrequency = currentNode->maxFrequency;
      setMaxFrequencies(currentNode->parent);
  }
  return;
}

/* 
 * Function name: Destructor
 * Purpose: No memory leaks, call deleteAll which iwll delete all our nodes in
 * MWTrie */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
	delete root;
}

/* 
 * Function name: deleteAll
 * Purpose: uses recursion to delete all nodes in mwtrie */
void DictionaryTrie::deleteAll( DictTrieNode* current ) {
  for( auto node : current->nodes ) {
    if( node != nullptr ) {
      deleteAll( node );
      delete node;
    }
  }
}

/* 
 * Function name: operator < 
 * Purpose: overloaded for minHeap
 * Parameters: other - other node to compare to
 * Return: none
 */
bool DictTrieNode::operator<(const DictTrieNode& other) const {
  if( frequency != other.frequency ) {
    return frequency > other.frequency;
  }
  return false;
}

/* 
 * Function name: operator >
 * Purpose: overloaded for maxheap
 * Parameters: other - other node to compare to
 * Return: none
 */
bool DictTrieNode::operator>(const DictTrieNode& other) const {
  if( frequency != other.frequency ) {
    return frequency < other.frequency;
  }
  return false;
}

/* 
 * Function name: isMoreThan
 * Purpose: comparator method for nodes
 * Parameters: one - first node
 *             other - second node
 * Return: none
 */
bool isMoreThan( DictTrieNode* one, DictTrieNode* other ) {
  return ((one->frequency) > (other->frequency));
}

