/* Names: Louis Leung, Kyle Sit
 * Date: 5/12/16
 * File Description: Explores running time of find in all of our dictionary
 * classes 
 */

#include "util.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryTrie.hpp"
#include <iostream>
#include <fstream>

#define AVERAGE_LOOP 50
#define NUM_ARGS 5
#define BASE 10

using namespace std;

int main(int argc, char * argv[]) {

	if (argc != NUM_ARGS) {
		cerr << "Arg 1: minimum size \nArg 2: step size \nArg 3: numIterations \n";
		cerr << "Arg 4: dicitonary file \n";
		return -1;
	}

	char * endptr;
	int minSize = strtol(argv[1], &endptr, BASE);
	int stepSize = strtol(argv[2],&endptr, BASE);
	int numIterations = strtol(argv[3], &endptr, BASE);

	std::string dictFile = argv[4];

	std::string throwAway;
	int numLines = 0;

	int totalTime;
	int averagedTime;

	int success;

	Timer t;

	ifstream in;
	in.open(dictFile, std::ios::binary);

  /* count number of lines in the dict file */
	while (getline(in, throwAway)) {
		numLines++;
  }

	/* reset file pointer to beginning */

	in.clear();
	in.seekg(0, in.beg);

	
	cout << "DictionaryTrie\n";

	for (int i = 0; i < numIterations; i++) {
		DictionaryTrie myDictTrie;
		Utils::load_dict(myDictTrie, in, minSize + i*stepSize);

		/* report error if number of lines in Dict is less than 
		 * how many we want to lines we wnat to read in */

		t.begin_timer();
		for (int j = 0; j < AVERAGE_LOOP; j++) {
			success = myDictTrie.find("this string wont be inside");
		}
		/*
		if (success) {
			cerr << "Found\n";
		}
		else {
			cerr << "Not Found\n";
		}
		*/
		totalTime = t.end_timer();
		averagedTime = totalTime/AVERAGE_LOOP;

		cout << (minSize + i*stepSize) << "\t" << averagedTime << endl;

	}

	in.clear();
	in.seekg(0, in.beg);

	
	cout << "DictionaryBST\n";

	for (int i = 0; i < numIterations; i++) {
		DictionaryBST myDictBST;
		Utils::load_dict(myDictBST, in, minSize + i*stepSize);

		/* report error if number of lines in Dict is less than 
		 * how many we want to lines we wnat to read in */

		t.begin_timer();
		for (int j = 0; j < AVERAGE_LOOP; j++) {
			success = myDictBST.find("this string wont be inside");
		}
		/*
		if (success) {
			cerr << "Found\n";
		}
		else {
			cerr << "Not Found\n";
		}
		*/

		totalTime = t.end_timer();
		averagedTime = totalTime/AVERAGE_LOOP;

		cout << (minSize + i*stepSize) << "\t" << averagedTime << endl;

	}

	in.clear();
	in.seekg(0, in.beg);

	
	cout << "DictionaryHashtable\n";

	for (int i = 0; i < numIterations; i++) {
		DictionaryHashtable myDictHash;
		Utils::load_dict(myDictHash, in, minSize + i*stepSize);

		/* report error if number of lines in Dict is less than 
		 * how many we want to lines we wnat to read in */

		t.begin_timer();
		for (int j = 0; j < AVERAGE_LOOP; j++) {
			success = myDictHash.find("this string wont be inside");
		}
		/*
		if (success) {
			cerr << "Found\n";
		}
		else {
			cerr << "Not Found\n";
		}
		*/
		totalTime = t.end_timer();
		averagedTime = totalTime/AVERAGE_LOOP;

		cout << (minSize + i*stepSize) << "\t" << averagedTime << endl;

	}
	return 1;
}

	
