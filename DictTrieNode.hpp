#ifndef DICT_TRIE_NODE_HPP
#define DICT_TRIE_NODE_HPP

#define ALPHABET_SIZE 26

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class DictTrieNode {
  friend bool isMoreThan( DictTrieNode* one, DictTrieNode* other );

public:
  DictTrieNode *nodes[ALPHABET_SIZE + 1];
  DictTrieNode *parent;
  DictTrieNode *maxFrequency;
  unsigned int frequency;
  bool leaf;

  DictTrieNode() {
    frequency = 0;
    leaf = false;
    parent = nullptr;
    maxFrequency = nullptr;
  }

  bool operator<(const DictTrieNode& other) const;
};

bool isMoreThan( DictTrieNode* one, DictTrieNode* other );

#endif // DICTTRIENODE_HPP
