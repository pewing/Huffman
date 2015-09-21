// Huffman Encoding
#include <iostream>
#include <fstream>
#include "tree.h"
using namespace std;

void build_path(string * path, Hnode * root, string bits) {
	if (!root->left) {// reached a char
		path[(unsigned char)root->letter] = bits;
		return;
	}
	build_path(path, root->right, bits+"1");
	build_path(path, root->left, bits+"0");
}

void tree_to_string(Hnode * root, string & tree_string) {
	if (!root->left) 
		tree_string = tree_string + "O" + root->letter;
	else {
		tree_string = tree_string + "I";
		tree_to_string(root->left, tree_string);
		tree_to_string(root->right, tree_string);
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
	string file_name = argv[1];	
	ifstream file(file_name.c_str());
	int char_count = 0;
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
		char_count++;
		Count[(unsigned char) c]++;
	}
	file.close();
	
	if (!char_count) {
		ofstream output_file((file_name+".huf").c_str());
		return 0;
	}
	
	
	Node * queue = NULL;
	string allChars = "";
	for (int i=0; i<256; i++) 
		if (Count[i]) {
			allChars += (unsigned char) i;
			insert(queue, new Hnode((unsigned char)i, Count[i]));
		}
		
	while (queue->next) { // Combine two nodes, insert them back into queue until queue->next = NULL
		Hnode * parent = new Hnode();
		parent->count = queue->data->count + queue->next->data->count;
		parent->left = queue->data;
		parent->right = queue->next->data;
		Node * to_del = queue;
		queue = queue->next;
		delete to_del;
		to_del = queue;
		queue = queue->next;
		delete to_del;
		insert(queue, parent);
	}
	
	
	Hnode * root = queue->data;
	delete queue;
	
	build_path(Path, root, "");
	
	
	ifstream file2(file_name.c_str());
	//int byte_count = 0;
	
	string bit_string = "";
	string char_string = ""; // Full string of char that describes path; Have to keep in variable since we're putting it in our encoded file last
	
	
	while (1) {
		file2.get(c);
		if (!file2) {
			if (bit_string != "") {
				bit_string += string(8-bit_string.size(), '0'); // turn into last char
				char_string += byte_to_char(bit_string);
				//byte_count++;
				}
			break;
		}
		bit_string += Path[(unsigned char) c];
		while (bit_string.size() >= 8) {
			char_string += byte_to_char(bit_string.substr(0,8));
			bit_string = bit_string.substr(8);
			//byte_count++;
		}
	} 
	file2.close();
	
	string tree_string = "";
	tree_to_string(root, tree_string);
	//cout << tree_string << endl;
	
	string output_file_name = argv[1];
	ofstream output_file((file_name+".huf").c_str());
	
	output_file << char_count << tree_string << char_string;

	output_file.close();
	
	// Next thing to do: don't keep char_string in a var. Store in a file, then open that and concat into final file
	
	return 0;
}