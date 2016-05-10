#include "DictTrieNode.hpp"

using namespace std;

bool DictTrieNode::operator<(const DictTrieNode& other) const {
  if( frequency != other.frequency ) {
    return frequency > other.frequency;
  }
  return false;
}

bool isMoreThan( DictTrieNode* one, DictTrieNode* other ) {
  return (one->frequency) > (other->frequency);
}
