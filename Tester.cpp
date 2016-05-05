#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include "util.hpp"
#include <iostream>
#include <fstream>

void load_dict(DictionaryBST& dict, istream& words);
void load_dict(DictionaryHashtable& dict, istream& words);

int main( int argc, char * const * argv ) {
  /* construct test hashtable */
  DictionaryHashtable testHash;
  
  std::ifstream in;
  
  in.open(argv[1]);
  
  Utils::load_dict(testHash, in);
  
  DictionaryBST testBST;
  
  Utils::load_dict(testBST, in);
  
  std::string test;
  
  while( getline(std::cin,test)) {
    if( !(testHash.find( test )) ) {
      return -1;
    }
    else {
      std::cout << "found!";
    }
    if( !(testBST.find( test )) ) {
      return -1;
    }
    else {
      std::cout << "found!";
    }
  }
  
  
  std::cout << "Successful closes";
  
  
  in.close();
  
}
