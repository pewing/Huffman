// Huffman decoder
// Author: Philip Ewing


#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

using namespace std;

void createHnodeTree(Hnode * & top, string path, int & index) {
	cout << "index = " << index << endl;
	if (!top) {
		return;
	}
	Hnode * child = new Hnode();
	if (path[index] == 'C') {
		top->letter = path[++index];
		cout << top->letter << endl;
		index++;
		return;
	}
	else if (path[index] == 'L') {
		top->left = new Hnode();
		createHnodeTree(top->left, path, ++index);
		if (path[index] != 'R') {
			cout << "ERROR - unproperly formatted graph" << endl;
			return;
		}
		top->right = new Hnode();
		createHnodeTree(top->right, path, ++index);
		return;
	}
	else {
		cout << "ERROR - unproperly formatted graph" << endl;
		return;
	}
}

void createHnodeTreeTop(Hnode * & top, string path) {
	int index = 0;
	createHnodeTree(top, path, index);
}

string charToBits(char c) {
	int num = int(c);
	string byteString = "";

	for (int i = 1; i <= 128; i = i * 2) {
		if ( num & i) {
			byteString = "1" + byteString;
		}
		else {
			byteString = "0" + byteString;
		}
	}

	return byteString;
}

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
	Hnode * top = new Hnode();
	string bitPath = "";

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
					cout << "ERROR - Graph not properly formatted" << endl;;
					cout<< l<<r<<c;
					return 0;
			}
			treePath += ch;
			if (l == r && c == l+1) {
					doneTreePath = true;
					createHnodeTreeTop(top, treePath);
			}
		}
		// now dealing with bitstring path
		else {
				// bitPath += charToBits(ch);

		}
	}
	cout << charToBits('0') << endl;
	cout << charToBits('\n') << endl;
	cout << charToBits('	') << endl;

	return 0;
}
