// Huffman decoder
// Author: Philip Ewing


#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 2 ) {
		cout << "ERROR - Proper syntax:  decoder.exe filename.huf"<<endl;
		return 0;
	}
	string filename = argv[1];
	int filenameSize = filename.size();
	if (filenameSize < 5 || filename.substr(filenameSize-4) != ".huf") {
		cout << "ERROR - Can only decode .huf files" <<endl;
		return 0;
	}

	ifstream iFile(filename);
	ofstream oFole(filename.substr(0, filenameSize - 4) + ".txt");

	if (!iFile.is_open()) {
		cout << "ERROR - Unable to open file" << endl;
		return 0;
	}

	string treePath = "";
	char ch;
	int l = 0;
	int r = 0;
	int c = 0;
	bool doneTreePath = false;
	Hnode * top = NULL;

	while (iFile.get(ch)) {
		if (!doneTreePath) {
			switch (ch) {
				case 'L':
					l++;
					break;
				case 'R':
					r++;
					break;
				case 'C':
					c++;
					treePath += ch;
					iFile.get(ch);
					break;
				default:
					cout << "ERROR - Graph not properly formatted";
					cout<< l<<r<<c;
					return 0;
			}
			treePath += ch;
			if (l == r && c == l+1) {
					doneTreePath = true;
					cout << treePath;
			}
		}
		else {

		}
	}


	// bool postC;



	return 0;
}
