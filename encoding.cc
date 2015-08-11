// Huffman Encoding
#include <iostream>
#include <fstream>
#include "tree.h"
using namespace std;

void insert(Node * queue, Hnode * huffnode) {
	if (!queue)
		queue = new Node(huffnode);
	
	else if (huffnode->count <= queue->data->count)
		queue = new Node(huffnode, queue);
	else
		insert(queue->next, huffnode);
}

void print_tree(Hnode * root, int indent) {
	if (!root)
		return;
	cout << root << 
}


int main(int argc, char * argv[]) {
	ifstream readFile;
	readFile.open(argv[1]);
	char output;
	
	int Count[256];
	for (int i=0; i<256; i++)
		Count[i] = 0;
	
	//int j=0;
	while (!readFile.eof()) {
		readFile.read(&output, 1);
		Count[output]++;
	}
	
	Node * queue = NULL;
	
	for (int i=0; i<256; i++) 
		if (Count[i])
			insert(queue, new Hnode((unsigned char)i, Count[i]));

		
	// NEED TO CHECK IF ONLY ONE LETTER
	Hnode * root = new Hnode();
	root->right = queue->data;
	Node * temp = queue;
	queue = queue->next;
	delete temp;
	
	while (queue) {
		
	}
	return 0;
}