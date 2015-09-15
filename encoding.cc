// Huffman Encoding
#include <iostream>
#include <fstream>
#include "tree.h"
using namespace std;

void build_path(string & path, char c, Hnode * root) {
	if (!root->left)
		return;
	else if (root->left->letter == c) {
		path += '1';
	}
	else {
		path += '0';
		build_path(path, c, root->right);
	}
}

void insert(Node * & queue, Hnode * huffnode) {
	if (!queue) {
		queue = new Node(huffnode);
	}
	else if (huffnode->count <= queue->data->count) {
		queue = new Node(huffnode, queue);
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

char byte_to_char(string str) {
	/*if (str.size() != 8)
		return '';*/
	int temp = 0;
	for (int i=0; i<8; i++) {
		temp = temp << 1;
		if (str[i] == '1')
			temp++;
	}
	return temp;
}

int main(int argc, char * argv[]) { 
	ifstream file(argv[1]);
	char c;
	
	int Count[256];
	string Path[256];
	for (int i=0; i<256; i++) {
		Count[i] = 0;
		Path[i] = "";
	}
	while (1) {
		file.get(c);
		if (not file)
			break;
		Count[(unsigned char) c]++;
	}
	file.close();
	
	Node * queue = NULL;
	string allChars = "";
	for (int i=0; i<256; i++) 
		if (Count[i]) {
			allChars += (unsigned char) i;
			insert(queue, new Hnode((unsigned char)i, Count[i]));
		}
	
/* 	Node * temporary = queue;
	while (temporary) {
		cout << temporary->data->letter;
		temporary = temporary->next;
	} */
		
	// STILL NEED TO CHECK IF ONLY ONE LETTER
		
	Hnode * old_root = queue->data;
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
	
	for (int i=0; i < allChars.size(); i++) 
		build_path(Path[(unsigned char) allChars[i]], allChars[i], root);
	
	ifstream file2(argv[1]);
	int byte_count = 0;
	string bit_string = "";
	string char_string = "";
	
	
	while (1) {
		file2.get(c);
		if (!file2) {
			if (bit_string != "") {
				bit_string += string(8-bit_string.size(), '0'); // turn into last char
				char_string += byte_to_char(bit_string);
				byte_count++;
				}
			break;
		}
		bit_string += Path[(unsigned char) c];
		while (bit_string.size() >= 8) {
			char_string += byte_to_char(bit_string.substr(0,8));
			bit_string = bit_string.substr(8);
			byte_count++;
		}
	} 
	
	
	
	string output_file_name = argv[1];
	ofstream output_file((output_file_name+".huf").c_str());
	
	//cout << byte_to_char("00111111")<< endl;
	
	//print_tree(root, 2);	
	
	return 0;
}