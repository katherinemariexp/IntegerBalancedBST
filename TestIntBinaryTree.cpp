//Binary Search Tree
// Description: Assignment 14 
// Author: Katherine-Marie Gonzales
// COMSC200 - 5001
// May 13, 2019
// Status: Incomplete - balance not implemented, missing functions 

//TestIntBinaryTree.cpp
#include<bits/stdc++.h> 
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "IntBinaryTree.h"
using namespace std;

class Node{
public:
	int data;
	Node *left, *right;
	Node(int data){
		this->data = data;
		left = right = nullptr;
	}
};

class BST {
    Node *root;	
    void display(Node *root);
    void displayPreorder(Node *root);
    void displayPostorder(Node *root);
    bool travInOrder(Node *root, vector<int> &record);
    void printInOrder(const Node *p, string lpad, string rpad) const;
public:
	BST(){ root = nullptr; }
	bool find(int id);
	bool remove(int id);
	Node *getSuccessor(Node* target);
	void insert(int id);
	void display() { display(root); }
	void displayPreorder() {displayPreorder(root);}
	void displayPostorder() {displayPreorder(root);}
	void printInOrder () const { printInOrder(root, " ", " "); }
	bool travInOrder( vector<int> &record ) {
	    travInOrder( root, record );
	}
};

bool BST::find(int id) {
	Node *current = root;
	while(current) {
		if(current->data > id) { current = current->left; }
		else if(current->data < id) { current = current->right; }
		else { return true; }
	}
	return false;
}

bool BST::remove(int id) {
	Node *parent = root;
	Node *current = root;
	bool isLeftChild = false;
	while(current->data!=id) {
		parent = current;
		if(current->data > id) {
			isLeftChild = true;
			current = current->left;
		}
		else {
			isLeftChild = false;
			current = current->right;
		}
		if( !current ) return false; 
	}
	//if i am here that means we have found the node
	//Case 1: if node to be removed has no children
	if(!current->left && !current->right){
		if(current==root) { root = nullptr; }
		if(isLeftChild){ parent->left = nullptr; }
		else { parent->right = nullptr; }
	}
	//Case 2 : if node to be removed has only one child
	else if(current->right==nullptr){
		if(current==root){ root = current->left; }
		else if(isLeftChild) { parent->left = current->left; }
		else{ parent->right = current->left; }
	}
	else if(current->left==nullptr){
		if(current==root){ root = current->right; }
		else if(isLeftChild){ parent->left = current->right; }
		else{ parent->right = current->right; }
	}else {// i.e. if( current->left && current->right){
		//now we are to find the minimum left on the right sub tree
		Node *successor = getSuccessor(current);
		if(current==root){ root = successor; }
		else if(isLeftChild){ parent->left = successor; }
		else{ parent->right = successor; }			
		successor->left = current->left;
	}		
	return true;		
}

Node* BST::getSuccessor(Node* target) {
	Node *successsor = nullptr;
	Node *successsorParent = nullptr;
	Node *current = target->right;
	while(current) {
		successsorParent = successsor;
		successsor = current;
		current = current->left;
	}
	//check if successor has the right child, it cannot have left child for sure
	// if it does have the right child, add it to the left of successorParent.
	if(successsor != target->right) {
		successsorParent->left = successsor->right;
		successsor->right = target->right;
	}
	return successsor;
}

void BST::insert(int id){
	Node *newNode = new Node(id);
	if(!root){ root = newNode; return;}
	Node *current = root;
	Node *parent = nullptr;
	while(true){
		parent = current;
		if(id<current->data){				
			current = current->left;
			if(!current){
				parent->left = newNode;
				return;
			}
		}
		else{
			current = current->right;
			if(!current){
				parent->right = newNode;
				return;
			}
		}
	}
}


void BST::display(Node *root){
 	if(root){
 		display(root->left);
 		cout << " " << root->data;
 		display(root->right);
 	}

 }
 
void BST::displayPreorder(Node *root){
 	if(root){
 		cout << " " << root->data;
 		displayPreorder(root->left);
 		displayPreorder(root->right);
 	}

 }
 
 void BST::displayPostorder(Node *root){
 	if(root){
 		displayPostorder(root->left);
 		displayPostorder(root->right);
 		cout << root->data << endl;
 	}
 }

// the cash-back (call-back) version
//
/*void BST::display(Node *root) {
    vector<int> record;
    travInOrder(record);
    for( auto x:record )
        cout << x << " ";
}*/

bool BST::travInOrder(Node *p, vector<int> &record){
	if (p){
	    if(p->left) travInOrder(p->left, record);
		record.push_back(p->data);
		if(p->right) travInOrder(p->right, record);
	}
	return true;
}


void BST::printInOrder(const Node *p, string lpad, string rpad) const {
    string pad = lpad.substr(0, lpad.size() - 1);
    if (p == nullptr)	return;
    printInOrder(p->right, rpad + "    |", rpad + "     ");
    cout << pad << "+--" << setw(3) << p->data << endl;
    printInOrder(p->left, lpad + "     ", lpad + "    |");
}

void menu()
{
	cout << endl << "--- Integer Binary Search Tree ---" << endl;
    cout << "B - to Batch enter Tree" << endl;
    cout << "b - to balance Tree" << endl;
    cout << "C - to clear Tree" << endl;
    cout << "D - to Display Tree (2D)" << endl;
    cout << "1 - to Pre order Traversal" << endl;
    cout << "2 - to In Order Traversal" << endl;
    cout << "3 - to Post Order Traversal" << endl;
    cout << "m - menu" << endl;
    cout << "Q - to Quit" << endl << endl;
}
	
vector<int> getVals(string s, char delim)
{
    vector<int> v;
    string i;
    stringstream ss(s);
    while(getline(ss,i,delim))
    {
        stringstream c(i);
        int x;
        c >> x;
        v.push_back(x);
    }
    return v;
}



int main() {
	BST *b = new BST;
	vector<int> pattern {46,11,3,22,23,64,62,99,58,60,6,8};//{3,8,1,4,6,2,10,9,20,25,15,16};
	for(auto x:pattern) b->insert(x);
	char command;
	string input;
	
	menu();

	do{
		cout << endl << "Enter a command: ";
		cin >> command;
		
		cout << endl;

		switch (command)
		{
			case 'B': cout << "Enter a list of integers separated by a comma (,): ";
			cin >> input;
			getVals(input, ',');
			cout << endl;
			break;
			case 'b':
			break;
			case 'C': pattern.clear();
			break;
			case 'D': b->printInOrder(); 
			break;
			case '1': b->displayPreorder();
			break;
			case '2': b->display();
			break;
			case '3': b->displayPostorder();
			break;
			case 'm': menu();
			break;
			case 'Q': cout << endl; "Goodbye.";
			break;
			default: cout << "Please enter a valid option." << endl;
			break;
		}
	}
	while (command != 'Q');


}