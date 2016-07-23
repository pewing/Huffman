#include <iostream>
#include <fstream>
#include "tree.h"
#include <typeinfo>

using namespace std;

// Sort Hnodes from lowest to highest count
void sortCharNodes(Hnode * h, Node * & nodeList) {
	if (!nodeList) {
		nodeList = new Node(h);
	}
	else if (nodeList->data->count >= h->count) {
		nodeList = new Node(h, nodeList);
	}
	else {
		sortCharNodes(h, nodeList->next);
	}
}

Node * createAndSortCharNodes(int * charCount, string & charTracker) {
	Node * nodeList = NULL;

	for (int i = 0; i < 256; i++) {
		if (charCount[i] != 0) {
			charTracker += (char)i;
			sortCharNodes(new Hnode((char)i, charCount[i]), nodeList);
		}
	}

	return nodeList;
}

void printNodeList(Node * n) {
	if (!n) {
		return;
	}
	printNodeList(n->next);
}

Hnode * createHnodeTree(Hnode * top, Node * list) {
	Node * toDelete = NULL;
	while (list->next) {
		Hnode * parent = new Hnode();
		parent->left = list->data;
		parent->right = list->next->data;
		parent->count = list->data->count + list->next->data->count;

		toDelete = list;
		list = list->next;
		delete toDelete;
		toDelete = list;
		list = list->next;
		delete toDelete;

		sortCharNodes(parent, list);
	}

	printNodeList(list);

	return list->data;
}

// Left-right traversal to get byte path of all chars
void traverseTreeForBytePath(Hnode * top, string * byteIndex, string bitPath) {
	if (!top->left) {
		byteIndex[(int)top->letter] = bitPath;
		return;
	}
	traverseTreeForBytePath(top->left, byteIndex, bitPath + "0");
	traverseTreeForBytePath(top->right, byteIndex, bitPath + "1");
}


void traverseTreeForGraph(Hnode * top, string & graph) {
	if (!top) {
		return;
	}
	if (top->left) {
		graph += "L";
		traverseTreeForGraph(top->left, graph);
		graph += "R";
		traverseTreeForGraph(top->right, graph);
		return;
	}
	// Otherwise reached a char
	graph += "C";
	graph += top->letter;
}


void callTraverseTreeForGraphAndPrint(Hnode * top, ofstream & oFile) {
	string fullTree = "";
	traverseTreeForGraph(top, fullTree);
	oFile.write(fullTree.c_str(), fullTree.size());
}


string byteToChar(string str) {
	if (str.size() != 8) {
		cout << "Problem with size";
		return "0";
	}

	unsigned char num = 0;
	for (int i = 0; i < 8; i++) {
		num *= 2;
		if (str[i] == '1') {
			num += 1;
		}
	}
	return string(reinterpret_cast<const char *>(num));
}


int main(int argc, char * argv[]) {
	string filename;
	if (argc == 1) {
		cout << "Enter file to be read: ";
		cin >> filename;
	}
	else if (argc == 2) {
		filename = argv[1];
	}
	else {
		cout << "ERROR - Wrong number of arguments. " << endl;
		return 0;
	}

	int charCount[256] = {0};
	char c;
	int byteCount = 0;
	ifstream iFile(filename);

	if (!iFile.is_open()) {
		cout << "ERROR - Unable to open file" << endl;
		return 0;
	}

	while (iFile.get(c)) {
		charCount[(unsigned char)c]++;
		byteCount++;
	}

	iFile.clear();

	string charTracker = ""; //Every different char in file
	Node * nodeList = createAndSortCharNodes(charCount, charTracker);

	Hnode * top = createHnodeTree(top, nodeList);

	string bytePath[256];

	traverseTreeForBytePath(top, bytePath, "");

	iFile.seekg(0, iFile.beg);
	ofstream oFile;
	oFile.open("output_" + filename + ".huf", ios::out | ios::binary);

	callTraverseTreeForGraphAndPrint(top, oFile);

	string currentByte = "";
	while (iFile.get(c)) {
		cout << "c = " << (int)c <<endl;
		currentByte += bytePath[(int)c];
		cout << "path = " << bytePath[(int)c] << endl;
		cout << "byte = " << currentByte << endl<<endl;
		while (currentByte.size() >= 8) {
			// oFile << "hi";
			cout << "1" << endl;
			// const char * byte = byteToChar(currentByte.substr(0,8));
			cout << "2" << endl;
			// Writing one bytw at a time is inefficient. Needs work
			// oFile.write(byteToChar(currentByte.substr(0,8)), 1);
			cout << "3" << endl;
			// cout << "----" <<byteToChar(curresntByte.substr(0,8))<<"-----"<<endl;
			// cout << "----" <<(int)byteToChar(currentByte.substr(0,8))<<"-----"<<endl;
			currentByte = currentByte.substr(8);
		}
	}
	if (currentByte.size() != 0) {
		currentByte += string(8 - currentByte.size(), '0');
		// oFile.write((const char *)byteToChar(currentByte.substr(0,8)), 1);
	}

	iFile.close();
	oFile.close();
}
