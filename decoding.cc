// Huffman decoder
// Author: Philip Ewing


#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

using namespace std;

void createHnodeTree(Hnode * & top, string path, int & index) {
	if (!top) {
		return;
	}
	Hnode * child = new Hnode();
	if (path[index] == 'C') {
		top->letter = path[++index];
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


bool findLetter(Hnode * currentNode, string & bitPath, unsigned char & letter) {
	if (!currentNode) {
		return false;
	}
	else if (!currentNode->left) {
		letter = (unsigned char)currentNode->letter;
		return true;
	}
	else if (bitPath == "") {
		return false;
	}
	string newBitPath = bitPath.substr(1);
	if (bitPath[0] == '0') {
		if (findLetter(currentNode->left, newBitPath, letter)) {
			bitPath = newBitPath;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (findLetter(currentNode->right, newBitPath, letter)) {
			bitPath = newBitPath;
			return true;
		}
		else {
			return false;
		}
	}
}


void traversePathAndPrintToFile(ifstream & iFile, Hnode * top, ofstream & oFile) {
	Hnode * currentNode = top;
	char ch;
	unsigned char letter;
	string bitPath = "";

	while (iFile.get(ch)) {
		bitPath += charToBits(ch);

		while (findLetter(currentNode, bitPath, letter)) {
			oFile << letter;
			currentNode = top;
		}
	}
	iFile.close();
	oFile.close();
}


Hnode * readAndMakeBinaryTree(ifstream & iFile) {
	string treePath = "";
	char ch;
	int l = 0;
	int r = 0;
	int c = 0;
	bool doneTreePath = false;
	Hnode * top = new Hnode();

	while (!doneTreePath) {
		iFile.get(ch);
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
				if (l == r && c == l+1) {
					doneTreePath = true;
				}
				break;
			default:
				cout << "ERROR - Graph not properly formatted" << endl;;
				return NULL;
		}
		treePath += ch;
	}

	createHnodeTreeTop(top, treePath);
	return top;
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

	ifstream iFile(filename, ios::in | ios::binary);
	ofstream oFile(filename.substr(0, filenameSize - 4) + ".txt");

	if (!iFile.is_open()) {
		cout << "ERROR - Unable to open file" << endl;
		return 0;
	}

	Hnode * top = readAndMakeBinaryTree(iFile);

	traversePathAndPrintToFile(iFile, top, oFile);

	return 0;
}
