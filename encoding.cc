// Huffman Encoding
#include <iostream>
#include <fstream>
#include "tree.h"
using namespace std;

void insert(Node * & queue, Hnode * huffnode) {
	if (!queue) {
		queue = new Node(huffnode);
		//cout << queue->data->letter << endl;
	}
	else if (huffnode->count <= queue->data->count) {
		queue = new Node(huffnode, queue);
		//cout << queue->data->letter << endl;
	}
	else
		insert(queue->next, huffnode);
}

void print_tree(Hnode * root, int indent) {
	if (!root)
		return;
	if (!root->left)  //leaf
		cout << string(indent-4, ' ') << root->count << root->letter;
	else {
		cout << string(3, ' ') << "[]" << endl;
		cout << string(indent, ' ') << "/";
		cout << "  \\" << endl;
		print_tree(root->left, indent+3);
		print_tree(root->right, indent+3);
	}
}

int main(int argc, char * argv[]) {
	ifstream readFile;
	readFile.open(argv[1]);
	char output;
	
	int Count[256];
	for (int i=0; i<256; i++)
		Count[i] = 0;

	//cout << "test |" << string(7, ' ') <<"|" <<endl;
	
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
	Hnode * old_root = new Hnode();
	old_root->right = queue->data;
		
	Node * temp = queue;
	queue = queue->next;

	delete temp;
		
	Hnode * root = NULL;
		
	while (queue) {
		root = new Hnode();
		Hnode * leaf = queue->data;
		root->left = leaf;
		root->right = old_root;
		Node * temp = queue;
		queue = queue->next;
		delete temp;
		old_root = root;
	}
	
	print_tree(root, 2);
	
	
	return 0;
}