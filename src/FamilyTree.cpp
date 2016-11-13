#include "FamilyTree.hpp"
#include <queue>
using std::queue;
FamilyTree::FamilyTree() {
    root = NULL;
}

FamilyTree::~FamilyTree() {
    queue<FamilyMember*>q;
    if (root)
        q.push(root);
    while (!q.empty()) {
        FamilyMember* temp = q.front();

        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);

        q.pop();

        delete temp;
    }
}

void FamilyTree::insertChild(FamilyMember *person, FamilyMember *mother) {
    FamilyMember* p = mother;
    while (p->right) p = p->right;
    p->right = person;
}


// when husband == null, insert ancestor
void FamilyTree::insertWife(FamilyMember *person, FamilyMember *husband) {
    if (husband) {
        FamilyMember* p = husband;
        while (p->left) p = p->left;
        p->left = person;
    } else {
        root = person;
    }
}
