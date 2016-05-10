#ifndef DICTTRIENODE_HPP
#define DICTTRIENODE_HPP

#define ALPHABET_SIZE 26

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class DictTrieNode {

public:
  DictTrieNode *nodes[ALPHABET_SIZE + 1];
  int frequency;
  bool leaf;

  DictTrieNode() {
    frequency = 0;
    leaf = false;
  }

};

#endif // DICTTRIENODE_HPP
