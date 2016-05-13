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
		DictionaryTrie * myDictTrie = new DictionaryTrie();
		Utils::load_dict(*myDictTrie, in, minSize + i*stepSize);

		if (numLines < (minSize + i*stepSize)) {
			cerr << "WARNING: Trying to read more lines than available";
		}

		/* report error if number of lines in Dict is less than 
		 * how many we want to lines we wnat to read in */

		t.begin_timer();
		for (int j = 0; j < AVERAGE_LOOP; j++) {
			myDictTrie->find("this string wont be inside");
			myDictTrie->find("thi string wont be inside");
			myDictTrie->find("th string wont be inside");
			myDictTrie->find("t string wont be inside");
			myDictTrie->find("t strin wont be inside");
			myDictTrie->find("t stri wont be inside");
			myDictTrie->find("t str wont be inside");
			myDictTrie->find("t st wont be inside");
			myDictTrie->find("t s wont be inside");
			myDictTrie->find("t string won be inside");
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

		delete(myDictTrie);

	}

	in.clear();
	in.seekg(0, in.beg);

	
	cout << "DictionaryBST\n";

	for (int i = 0; i < numIterations; i++) {
		DictionaryBST * myDictBST = new DictionaryBST();
		Utils::load_dict(*myDictBST, in, minSize + i*stepSize);

		if (numLines < (minSize + i*stepSize)) {

			cerr << "WARNING: Trying to read more lines than available";
		}

		/* report error if number of lines in Dict is less than 
		 * how many we want to lines we wnat to read in */

		t.begin_timer();
		for (int j = 0; j < AVERAGE_LOOP; j++) {
			myDictBST->find("this string wont be inside");
			myDictBST->find("thi string wont be inside");
			myDictBST->find("th string wont be inside");
			myDictBST->find("t string wont be inside");
			myDictBST->find("t strin wont be inside");
			myDictBST->find("t stri wont be inside");
			myDictBST->find("t str wont be inside");
			myDictBST->find("t st wont be inside");
			myDictBST->find("t s wont be inside");
			myDictBST->find("t string won be inside");
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

		delete(myDictBST);

	}

	in.clear();
	in.seekg(0, in.beg);

	
	cout << "DictionaryHashtable\n";

	for (int i = 0; i < numIterations; i++) {
		DictionaryHashtable * myDictHash = new DictionaryHashtable();
		Utils::load_dict(*myDictHash, in, minSize + i*stepSize);

		if (numLines < (minSize + i*stepSize)) {
			cerr << "WARNING: Trying to read more lines than available";
		}

		/* report error if number of lines in Dict is less than 
		 * how many we want to lines we wnat to read in */

		t.begin_timer();
		for (int j = 0; j < AVERAGE_LOOP; j++) {
			myDictHash->find("this string wont be inside");
			myDictHash->find("thi string wont be inside");
			myDictHash->find("th string wont be inside");
			myDictHash->find("t string wont be inside");
			myDictHash->find("t strin wont be inside");
			myDictHash->find("t stri wont be inside");
			myDictHash->find("t str wont be inside");
			myDictHash->find("t st wont be inside");
			myDictHash->find("t s wont be inside");
			myDictHash->find("t string won be inside");
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
		
		delete(myDictHash);
	}
	return 1;
}

	
