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


/* struct Tree {
	
	int size;
	Hnode * head;
	void insert_char(char c, int count);
	
	Tree() {
		size = 0;
		head = new Hnode();
	}
};

void Tree:: insert_char(char c, int count) {
	if (size==0) {
		head->left = new Hnode(c, count);
		size++;
		return;
	}
	else if (size==1) {
		if (head->left.count < count) {
			head->right = head->left;
			head->left = new Hnode(c, count);
		}
		else 
			head->right = new Hnode(c, count);
		size++;
	}
	
	else {
		Hnode * temp = head;
		while (temp->right && temp->left.count > count) {
			
		}
	

	}
} */







