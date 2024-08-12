#pragma once

#include <string>
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
	string nameOfStudent;
	int totalMarkOfStudent;
	int rankOfStudent;
	TreeNode* left;
	TreeNode* right;
};

class BinaryTreeChart {
	TreeNode* root;
	int size;
	string treename = "";

public:
	BinaryTreeChart(string treename) {
		root = nullptr;
		size = 0;
		this->treename = treename;
	}

	~BinaryTreeChart() {
		cout << "Destroying " << treename << " tree from memory." << endl;
	}

	void insert(string name, int marks, int rank) {
		insert(root, name, marks, rank);
	}

	void inorder() {
		inorder(root);
	}

	void preorder() {
		preorder(root);
	}

	void postorder() {
		postorder(root);
	}

	bool doesNameExist(string name) {
		TreeNode* temp = root;
		while (temp != nullptr) {
			if (name == temp->nameOfStudent) {
				return true;
			}
			//check left subtree, then right subtree
			if (doesNameExist(temp->left, name)) {
				return true;
			}
			else if (doesNameExist(temp->right, name)) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}

	string searchName(string name) {
		TreeNode* temp = root;
		while (temp != nullptr) {
			if (name == temp->nameOfStudent) {
				return "Name: " + temp->nameOfStudent + ", Marks: " + to_string(temp->totalMarkOfStudent) + ", Rank: " + to_string(temp->rankOfStudent);
			}
			// Traverse both left and right subtrees
			if (doesNameExist(temp->left, name)) {
				return searchName(temp->left, name);
			}
			else if (doesNameExist(temp->right, name)) {
				return searchName(temp->right, name);
			}
			else {
				temp = nullptr;
			}
		}
		// Name not found
		return "Name not found";
	}

	//display binary tree in tree format
	void displayInTreeFormat() {
		displayInTreeFormat(root, 0);
	}

private:
	void insert(TreeNode*& node, string name, int marks, int rank) {
		/*
		the nodes will be inserted where the format follows:
		root = node1
		root->left = node2
		root->right = node3
		root->left->left = node4
		root->left->right = node5
		root->right->left = node6
		root->right->right = node7
		...
		*/

		//if root is null, create a new node
		if (node == nullptr) {
			node = new TreeNode;
			node->nameOfStudent = name;
			node->totalMarkOfStudent = marks;
			node->rankOfStudent = rank;
			node->left = nullptr;
			node->right = nullptr;
			size++;
		}
		else {
			//if left is null, insert to left
			if (node->left == nullptr) {
				insert(node->left, name, marks, rank);
			}
			//if right is null, insert to right
			else if (node->right == nullptr) {
				insert(node->right, name, marks, rank);
			}
			//if both left and right are not null, insert to left
			else {
				insert(node->left, name, marks, rank);
			}
		}
	}

	bool doesNameExist(TreeNode* node, string name) {
		if (node == nullptr) {
			return false;
		}
		else if (name == node->nameOfStudent) {
			return true;
		}
		else {
			return doesNameExist(node->left, name) || doesNameExist(node->right, name);
		}
	}

	string searchName(TreeNode* node, string name) {
		if (node == nullptr) {
			return "Name not found";
		}
		else if (name == node->nameOfStudent) {
			return "Name: " + node->nameOfStudent + ", Marks: " + to_string(node->totalMarkOfStudent) + ", Rank: " + to_string(node->rankOfStudent);
		}
		else {
			string result = searchName(node->left, name);
			if (result != "Name not found") {
				return result;
			}
			else {
				return searchName(node->right, name);
			}
		}
	}

	void inorder(TreeNode* node) {
		if (node != nullptr) {
			inorder(node->left);
			cout << node->nameOfStudent << ", marks: " << node->totalMarkOfStudent << ", rank: " << node->rankOfStudent << endl;
			inorder(node->right);
		}
	}

	void preorder(TreeNode* node) {
		if (node != nullptr) {
			cout << node->nameOfStudent << ", marks: " << node->totalMarkOfStudent << ", rank: " << node->rankOfStudent << endl;
			preorder(node->left);
			preorder(node->right);
		}
	}

	void postorder(TreeNode* node) {
		if (node != nullptr) {
			postorder(node->left);
			postorder(node->right);
			cout << node->nameOfStudent << ", marks: " << node->totalMarkOfStudent << ", rank: " << node->rankOfStudent << endl;
		}
	}

	void displayInTreeFormat(TreeNode* node, int space) {
		//just display one by one
		//dont need to space
		if (node == nullptr) {
			return;
		}
		displayInTreeFormat(node->right, space + 10);
		cout << endl;
		for (int i = 10; i < space; i++) {
			cout << " ";
		}
		cout << "name: " << node->nameOfStudent << " (" << node->totalMarkOfStudent << "marks), Rank " << node->rankOfStudent << endl;
		displayInTreeFormat(node->left, space + 10);
	}

};