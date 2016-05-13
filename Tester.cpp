#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include "util.hpp"
#include <iostream>
#include <fstream>

extern void load_dict(DictionaryBST& dict, istream& words);
extern void load_dict(DictionaryHashtable& dict, istream& words);

int main( int argc, char* argv[] ) {
  std::ifstream in;
  in.open(argv[1]);
 
  std::cout << "file opened" << "\n";

  /* initialize hash and insert
  DictionaryHashtable testHash;
  Utils::load_dict(testHash, in);
  
  std::cout << "loaded hash" << "\n";
 
  in.clear();
	in.seekg(0, in.beg); 
  
  // initialize bst and insert
  DictionaryBST testBST;
  Utils::load_dict(testBST, in);
  
  std::cout << "loaded bst" << "\n";
  

  in.clear();
	in.seekg(0, in.beg); */
  
  
  // initialize trie and insert
  DictionaryTrie testTrie;
  Utils::load_dict(testTrie, in);
  
  std::cout << "loaded trie" << "\n";
  
  std::string test;
 
  std::cout << "Enter word:" << "\n";
  while( getline(std::cin,test)) {
  /*
    if( !(testHash.find( test )) ) {
      std::cout << "not found in hash!" << "\n";
      
    }
    else {
      std::cout << "found in hash!" << "\n";
    }
    
    // Test find for bst
    if( !(testBST.find( test )) ) {
      std::cout << "not found in bst!" << "\n";
    }
    else {
      std::cout << "found in bst!" << "\n";
    }*/
  
    // Test find for trie
    if( !(testTrie.find( test )) ) {
      std::cout << "not found in trie!" << "\n";
    }
    else {
      std::cout << "found in trie!" << "\n";
    }
    
    std::cout << "Enter word:" << "\n";
  }
  
  std::cout << "Successful closes" << "\n";
  
  in.close();
  
}
