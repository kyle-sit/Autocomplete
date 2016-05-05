#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include "util.hpp"
#include <iostream>

int main( int argc, char argv[] ) {
  /* construct test hashtable */
  DictionaryHashtable testHash;
  
  ifstream in;
  
  in.open(argv[1]);
  
  load_dict(testHash, in);
  
  DictionaryBST testBST;
  
  load_dict(testBST, in);
  
  std::string test;
  
  while( getline(cin,test)) {
    if( !(testHash.find( test )) ) {
      return -1;
    }
    else {
      cout << "found!";
    }
    if( !(testBST.find( test )) ) {
      return -1;
    }
    else {
      cout << "found!";
    }
  }
  
  delete(testHash);
  delete(testBST);
  
  cout << "Successful closes";
  
  
  in.close();
  
}
