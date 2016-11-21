#include "FamilyTree.h"

void PrintMembers(const FamilyMember* root, int printLevel = 0, bool isLeft = false, int blankIndex = 0) {
  if (root != NULL) {
  	// print
    if (isLeft) {  // wife
    	if (root->sex == girl && root->right) { printLevel++; }  // printlevel
    	cout << " / ";
    	cout << root->data << endl;
    } else { // child
    	if (printLevel > 0) {
    		for (int i = 0; i < printLevel-1; i++) {
    			if (i < printLevel-1-blankIndex) {
	    			cout << "│  ";
    			} else {
	    			cout << "   ";
	    		}
    		}
	    	if (root->right) {
	    		cout << "├─ ";
	    	} else {
	    		cout << "└─ ";
	    		blankIndex++;  // blankindex
	    	}
    	}
    	cout << root->data;
    	if (root->left == NULL) { cout << endl; }  // whether has a wife
    }
    if (root->left) {
    	if (!(root->sex == girl && root->left->sex == girl)) {  // preWife
    		PrintMembers(root->left, printLevel, true, blankIndex);
    	}
    }
    PrintMembers(root->right, printLevel, false, blankIndex);
  }
}
