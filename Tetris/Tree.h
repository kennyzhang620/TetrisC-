#pragma once
#include <iostream>
#include "PlayerStats.h"
#include <vector>

class Tree
{
private:
	Tree* LEFT = NULL;
	Tree* RIGHT = NULL;

	void _dealloc(Tree* node) {
		if (node == NULL) {
			int j = 0;
		}
		else {
			_dealloc(node->LEFT);
			_dealloc(node->RIGHT);

			//delete node;
			node = NULL;
		}
	}

	void _PrintData(Tree* node) {
		if (node == NULL) {
			std::cout << "End.\n";
			return;
		}
		else {
			std::cout << "Current Node: " << node->data.GetUserNameT() << '\n';
			std::cout << "Traverse Left\n";
			_PrintData(node->LEFT);
			std::cout << "Traverse Right\n";
			_PrintData(node->RIGHT);
		}
	}

	Tree* _appendBinTree(Tree* node, PlayerStats data1) {
		if (node == NULL) {
			node = new Tree(data1);
			return node;
		}
		else if (node->data.GetUserNameT().compare("Username0X5") == 0) {
			node->data = data1;
		}
		else {
			if ((node->data.GetUserNameT().compare(data1.GetUserNameT()) > 0)) {
				//std::cout << "L\n";
				node->LEFT = _appendBinTree(node->LEFT, data1);
			}
			else if (node->data.GetUserNameT().compare(data1.GetUserNameT()) < 0) {
				//std::cout << "R\n";
				node->RIGHT = _appendBinTree(node->RIGHT, data1);
			}
			else {
			}
		}
		return node;
	}
	int subStrExists(string substr1, string substr2) {
		int len = 0;

		if (substr1.length() < substr2.length())
			len = substr1.length();
		else {
			return 1;
		}

		for (int i = 0; i < len; i++) {
			if (substr1[i] != substr2[i])
				return 1;
		}
		
		return 0;
	}
	
	Tree* _searchBinTree(Tree* node, PlayerStats data1, std::vector<PlayerStats>* results) {
		if (node == NULL) {
			return node;
		}
		else if (node->data.GetUserNameT().compare(data1.GetUserNameT()) == 0) {
			return node;
		}
		else {
			if ((node->data.GetUserNameT().compare(data1.GetUserNameT()) > 0)) {
				if (subStrExists(data1.GetUserNameT(), node->data.GetUserNameT()) == 0) {
						std::cout << "||" << node->data.GetUserNameT() << "  |  " << node->data.GetUID() << "  |  " << node->data.GetHighScore() << '\n';
						results->push_back(node->data);
				}
				return _searchBinTree(node->LEFT, data1, results);
			}
			else if (node->data.GetUserNameT().compare(data1.GetUserNameT()) < 0) {
				if (subStrExists(data1.GetUserNameT(), node->data.GetUserNameT()) == 0) {
						std::cout << "||" << node->data.GetUserNameT() << "  |  " << node->data.GetUID() << "  |  " << node->data.GetHighScore() << '\n';
				}
				return _searchBinTree(node->RIGHT, data1, results);
			}
			else {
			}
		}
	}

	void _append(Tree* node, PlayerStats input) {
		node  = _appendBinTree(node, input);
	}

public:
	PlayerStats data;

	Tree() {
		LEFT = NULL;
		RIGHT = NULL;
	}

	Tree(PlayerStats input) {
		LEFT = NULL;
		RIGHT = NULL;
		data = input;
	}

	~Tree() {
		_dealloc(this);
	}
	
	void Init() { // Initalizes the tree for writing to either L or R node
		LEFT = new Tree;
		RIGHT = new Tree;
	}

	void AddData(PlayerStats data1) {
		data = data1;
	}

	bool isNUll() {
		if (this == NULL)
			return true;
		else
			return false;
	}


	void PrintTree() {
		_PrintData(this);
	}
	
	void AppendBinTree(PlayerStats input) {
		_append(this, input);
	}
	
	Tree* SearchBinTree(PlayerStats input, std::vector<PlayerStats>* store) {
		return _searchBinTree(this, input, store);
	}
};

