//HW 5
#include <iostream>

class node {
public:
	int key;
	node *left_child = nullptr;
	node *right_child = nullptr;

	node(int key) {
		this->key = key;
	}
};

class BST {
public:
	bool insert_key(int key) {
		node **location = Search(key);
		if (*location == nullptr) {
			node *a = new node(key);
			*location = a;		//the correct location is returned by search()
			return true;
		}
		else {
			return false;
		}
	}

	bool delete_key(int key) {
		node** location = Search(key);
		if (*location == nullptr) {
			return false;
		}
		else {
			//must ROTATE
			delete location;
			location = nullptr;
			return true;
		}
	}

	node** Search(int search_key) {	//Returns a double-pointer to where the key is/should be located.
		node **place = &root;
		while ((*place != nullptr) && ((*place)->key != search_key)) {
			if ((*place)->key < search_key) {
				place = &(*place)->right_child;
			}
			else {
				place = &(*place)->left_child;
			}
		}
		return place;
	}

	void enumerate() {	//Print each element in the tree in post-order
		//TODO TODO TODO TODO TODO TODO TODO TODO
	}

private:
	node* root = nullptr;
};

int main() {
	BST tree;
	int key;
	int operation;	//Key defining which operation we will carry out on the tree
	int operand;	//Key associated with the operator

	//Input keys and build tree
	while (std::cin >> key) {
		tree.insert_key(key);
	}

	//Input operation and operand
	std::cin >> operation;
	std::cin >> operand;

	//Complete operation
	switch (operation) {
		case 1: {
			node** search_dptr = tree.Search(operand);
		}
		case 2: {
			bool result = tree.insert_key(operand);
		}	
		case 3: {
			bool result = tree.delete_key(operand);
			if (result) {

			}
			else {
				std::cout << -1;
			}
		}
	}

	std::cout << "Paused";
}