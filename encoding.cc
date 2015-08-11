// Huffman Encoding
#include <iostream>
#include <fstream>
#include "tree.h"
using namespace std;

void insert(Node * queue, Hnode * huffnode) {
	if (!queue) {
		queue = new Node(huffnode);
		cout << huffnode->letter << endl;
	}
	else if (huffnode->count <= queue->data->count) {
		queue = new Node(huffnode, queue);
		cout << huffnode->letter << endl;
	}
	else
		insert(queue->next, huffnode);
}

void print_tree(Hnode * root, int indent) {
	if (!root)
		return;
	if (!root->left)  //leaf
		cout << string(indent, ' ') << root->count << root->letter;
	else {
		cout << "[]" << endl;
		print_tree(root->left, indent+1);
		print_tree(root->right, indent+1);
	}
}

int main(int argc, char * argv[]) {
	ifstream readFile;
	readFile.open(argv[1]);
	char output;
	
	int Count[256];
	for (int i=0; i<256; i++)
		Count[i] = 0;

	cout << "test |" << string(7, ' ') <<"|" <<endl;
	
	//int j=0;
	while (!readFile.eof()) {
		readFile.read(&output, 1);
		Count[output]++;
	}
	
	Node * queue = NULL;
	
	for (int i=0; i<256; i++) 
		if (Count[i])
			insert(queue, new Hnode((unsigned char)i, Count[i]));
		
	cout << "1" <<endl;
	// NEED TO CHECK IF ONLY ONE LETTER
	Hnode * old_root = new Hnode();
	cout << "1.5" <<endl;
	if (!queue)
		cout << "huh" <<endl;
	old_root->right = queue->data;
	
	cout << "2" <<endl;
	
	Node * temp = queue;
	queue = queue->next;
	
	cout << "3" <<endl;
	delete temp;
	
	cout << "2" <<endl;
	
	while (queue) {
		Hnode * root = new Hnode();
		Hnode * leaf = queue->data;
		root->left = leaf;
		root->right = old_root;
		Node * temp = queue;
		queue = queue->next;
		delete temp;
		old_root = root;
	}
	
	cout << "test |" << string(7, ' ') <<"|" <<endl;
	
	return 0;
}