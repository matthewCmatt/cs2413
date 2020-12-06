//HW 5
#include <iostream>

class node {
public:
	int key;
	node *left_child = nullptr;
	node *right_child = nullptr;

	node *next = nullptr;			//used in stack implementation
	bool visited = false;

	node(int key) {
		this->key = key;
	}
};

class node_stack {
public:
	bool pop() {
		if (head != nullptr) {
			std::cout << head->key << ' ';
			head->visited = true;
			head = head->next;
			return true;
		}
		return false;
	}

	void push(node* node) {
		node->next = head;
		head = node;
	}

	bool isEmpty() {
		if (head == nullptr) return true;
		else return false;
	}

	node* getTop() {
		return head;
	}

private:
	node* head = nullptr;
};


class BST {
public:
	bool insert_key(int key) {
		node **search_result = Search(key);
		if (*search_result == nullptr) {
			node *a = new node(key);
			*search_result = a;
			return true;
		}
		else {
			return false;
		}
	}

	bool delete_key(int key) {
		node **search_result = Search(key);
		if (*search_result == nullptr) {
			return false;
		}
		else {
			if ((*search_result)->left_child == nullptr) {
				if ((*search_result)->right_child == nullptr) {	//has no children
					*search_result = nullptr;
				}
				else {											//has right child
					*search_result = (*search_result)->right_child;
				}
			}
			else if ((*search_result)->right_child == nullptr) {		//has left child
				*search_result = (*search_result)->left_child;
			}
			else {												//has two children

				//Find smallest of the right subtree, to replace with the deleted key.
				node* parent_of_smallest_right = *search_result;
				while (parent_of_smallest_right->left_child != nullptr) {
					while (parent_of_smallest_right->left_child->left_child != nullptr) {	//Assures that smallest_right has a grand child, to keep track of the parent of smallest child.
						parent_of_smallest_right = parent_of_smallest_right->left_child;
					}
				}

				delete_key(parent_of_smallest_right->left_child->key);

				*search_result = parent_of_smallest_right->left_child; 
			}
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

	void enumerate() {

		node_stack stack;

		stack.push(root);

		while (!stack.isEmpty()) {
			node *temp = stack.getTop();

			bool right_valid = false;
			bool left_valid = false;

			if (temp->right_child != nullptr) {
				if (temp->right_child->visited == false) right_valid = true;
			}
			if (temp->left_child != nullptr) {
				if (temp->left_child->visited == false) left_valid = true;
			}

			if (right_valid) stack.push(temp->right_child);
			if (left_valid) stack.push(temp->left_child);
			if (!right_valid && !left_valid) stack.pop();
		}
	}

private:
	node* root = nullptr;
};

int main() {
	BST tree;		//Binary Search Tree object
	int key;		//Temporary input key
	int operation;	//Key defining which operation we will carry out on the tree
	int operand;	//Key associated with the operator

	//Input keys and build tree
	while (std::cin >> key) {
		tree.insert_key(key);
	}

	std::cin.clear();
	std::cin.ignore(2, '\n');

	//Input operation and operand
	std::cin >> operation;
	std::cin >> operand;

	//Complete operation
	switch (operation) {
		case 1: {
			node** search_ptr_ptr = tree.Search(operand);
			if (*search_ptr_ptr == nullptr) {
				std::cout << -1;
			}
			else {
				tree.enumerate();
			}
			break;
		}
		case 2: {
			bool result = tree.insert_key(operand);
			if (result) {
				tree.enumerate();
			}
			else {
				std::cout << -1;
			}
			break;
		}	
		case 3: {
			bool result = tree.delete_key(operand);
			if (result) {
				tree.enumerate();
			}
			else {
				std::cout << -1;
			}
			break;
		}
	}
}