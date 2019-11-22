#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct node {
	string letter;
	string code;
	node* left; 
	node* right;
};

class btree {
public: 
	btree();
	void insert(string letter, string code);
	void inorder_print(string letter);

	string search(string code);

private:
	void destroy_tree(node* leaf);
	void insert(string letter, string code, node* leaf, string codePure);
	void inorder_print(node* leaf, string letter);

	string search(string code, node* leaf);

	node* root;
};

btree::btree() {
	root = NULL;
}

void btree::destroy_tree(node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(string letter, string code)
{
	if (root != NULL) {
		insert(letter, code, root, code);
	}
	else {
		root = new node;
		root->letter = letter;
		root->code = code;
		root->left = NULL;
		root->right = NULL;
	}

}

void btree::insert(string letter, string code, node* leaf, string codePure)
{
	if (code[0] == '.') {
		if (leaf->left != NULL) {
			insert(letter, code.substr(1, code.length()) , leaf->left, codePure);
		}
		else {
			leaf->left = new node;
			leaf->left->letter = letter;
			leaf->left->code = codePure;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}
	else  {
		if (leaf->right != NULL) {
			insert(letter, code.substr(1, code.length()), leaf->right, codePure);
		}
		else {
			leaf->right = new node;
			leaf->right->letter = letter;
			leaf->right->code = codePure;
			leaf->right->left = NULL;
			leaf->right->right = NULL;
		}
	}
}

void btree::inorder_print(string letter) {
	inorder_print(root, letter);
}

void btree::inorder_print(node* leaf, string letter) {
	if (leaf != NULL) {
		inorder_print(leaf->left, letter);
		if (leaf->letter == letter) {
			cout << leaf->code << "\n";
		}
		inorder_print(leaf->right, letter);
	}
}

string btree::search(string code, node* leaf) {
	if (leaf != NULL) {
		if (code == "") {
			return leaf->letter;
		}
		if (code[0] == '.') {
			return search(code.substr(1), leaf->left);
		}
		else {
			return search(code.substr(1), leaf->right);
		}
	}
	else {
		return " ";
	}
}

string btree::search(string code) {
	return search(code, root);
}

void decode(btree* tree, string input) {
	string temp = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			cout << tree->search(temp) << " ";
			temp = "";
		}
		else {
			temp += input[i];
		}
		
	}
	cout << tree->search(temp) << " " << endl;

}

void encode(btree* tree, string input) {
	string temp = "";
	for (int i = 0; i < input.length(); i++) {
		temp = input[i];
		tree->inorder_print(temp);
	}
	
}

int main() {

	btree* tree = new btree();
	tree->insert(" ", " ");

	ifstream morse;
	for (int i = 0; i < 4; i++) {
		morse.open("morse.txt");
		while (!morse.eof()) {
			string input = "";
			string letter = "";
			string code = "";
			morse >> input;
			for (int i = 0; i < input.length(); i++) {
				if (input[i] == 46 || input[i] == 95) {
					code += input[i];
				}
				else {
					letter += input[i];
				}
			}
			if (code.length() == i + 1) {
				tree->insert(letter, code);
			}
		}
		morse.close();
	}

	decode(tree, "... ___ ... .");
	encode(tree, "here is where the fun");
}