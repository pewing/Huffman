// Huffman decoder
// Author: Philip Ewing
// Start date: September 21, 2015

#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

using namespace std;

void form_tree(Hnode * & root, string & str) {
	if (!root) {
		if (str[0] == 'O') {
			root = new Hnode();
			root->letter = str[1];
			str = str.substr(2);
		}
		else if (str[0] == 'I') {
			root = new Hnode();
			str = str.substr(1);
			form_tree(root->left, str);
			form_tree(root->right, str);
		}
	}
	
}


int main(int argc, char * argv[]) {
	if (argc != 2 ) {
		cout << "ERROR - Proper syntax:  decoder.exe filename.huf"<<endl;
		return 0;
	}
	string file_name = argv[1];
	int file_name_size = file_name.size();
	if (file_name_size < 5 || file_name.substr(file_name_size-4) != ".huf") {
		cout << "ERROR - Can only decode .huf files" <<endl;
		return 0; 
	}
	
	ifstream readFile(file_name.c_str());
	int char_count = 0;
	readFile >> char_count;
	
	if (!char_count) {
		ofstream writeFile((file_name.substr(file_name_size-4) + ".dehuf").c_str());
		readFile.close(); 
		writeFile.close();
		return 0;
	}
	
	char c;
	while (1) {
		readFile.get(c);
		if (not readFile)
			break;
		cout << c;
	}
	cout << endl;
	Hnode * root = NULL;
	string str = "IIIIO\nO1OsOtIO3IOeO ";
	form_tree(root, str);
	
	return 0;
}
