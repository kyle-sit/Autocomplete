#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "util.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2) {
		std::cout << "Invalid number of arguments.\n" 
		     << "Usage: ./main <input filename>.\n";
		return -1;
  }

  std::ifstream in;
  in.open(argv[1], std::ios::binary);

  if (!in.is_open()) 
  {
		std::cout<< "Invalid input file. No file was opened. Please try again.\n";
		return -1;
  }
	
  //Check for empty file
	in.seekg(0, std::ios_base::end); 
	unsigned int len = in.tellg();
	if(len==0) 
	{
		std::cout << "The file is empty. \n";
		return -1;
	}

	//Resets the stream to beginning of file
	in.seekg(0, std::ios_base::beg); 

  /************************** main implementation ************************/
  
  // Test Hashtable dictionary 
  DictionaryTrie dictT;
  std::string prefix;
  unsigned int num = 0;
  unsigned int index = 0;
  std::cout << "Constructed the dictionaries." << "\n";
  
  // Load the dictionary for TST, then reset the stream
  Utils::load_dict(dictT, in);
  std::cout << "Finished loading dictionaries." << "\n";
  
  std::cout << "Please enter the prefix to be completed: ";
  std::cin >> prefix;
  std::cout << "Please enter the amount of desired completions: ";
  std::cin >> num;

  std::vector<std::string> predictions = dictT.predictCompletions(prefix, num);

  std::cout << "The following are the predicted completions:" << std::endl;
  
  while (index < predictions.size()) {
    if (index == predictions.size()-1) {
      std::cout << predictions[index] << std::endl;
      break;
    }
    std::cout << predictions[index] << ", ";
    index++;
  }

  // Close the file if it is open
  if (in.is_open())
  {
    in.close();
  }

  return 0;
}
