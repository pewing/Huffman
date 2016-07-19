// tree.h

struct Hnode {
	Hnode* left;
	Hnode* right;
	char letter;
	int count;

	Hnode(char c, int cnt) {
		letter = c;
		count = cnt;
		left = NULL;
		right = NULL;
	}
	Hnode(){
		left = NULL;
		right = NULL;
	}
};

struct Node {
	Hnode * data;
	Node * next;
	Node(Hnode * d, Node * n = NULL) {
		data = d;
		next = n;
	}
};
