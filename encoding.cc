#include <iostream>
#include <fstream>
#include "tree.h"

using namespace std;

Node * sortCharNodes(Node * nodeList, Node * newNode) {
	return nodeList;
}

Node * createAndSortCharNodes(int charCount[]) {
	Node * nodeList;
	for (int i = 0; i < 256; i++) {
		if (charCount[i]) {
			Hnode * h = new Hnode(char('i'), charCount[i]);
			Node * n = new Node(h);
			nodeList = sortCharNodes(nodeList, n);
		}
	}
	return nodeList;
}

int main() {
	int charCount[256];
	char c;
	fstream fin("test.txt", fstream::in);

	cout << "o" << endl;
	while (fin >> noskipws >> c) {
		cout << c;
		charCount[c]++;
	}
	fin.close();


}
