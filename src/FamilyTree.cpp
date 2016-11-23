#include "FamilyTree.hpp"
#include <queue>
using std::queue;

int FamilyTree::FamilyMember::current_id = 0;

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

bool FamilyTree::deleteMember(function<bool(const FamilyMember *person)> filter) {
    int flag = 0;
    if (root != nullptr) {
        queue<FamilyMember*> q;
        q.push(root);
        while(!q.empty()) {
            FamilyMember* temp = q.front();
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
            if (filter(temp)) {
                flag = 1;
                int id = temp->id;
                if (temp->left != nullptr) {
                    queue<FamilyMember*> q1;
                    q1.push(temp->left);
                    while(!q1.empty()) {
                        FamilyMember* temp = q1.front();
                        if (temp->left != nullptr) q1.push(temp->left);
                        if (temp->right != nullptr) q1.push(temp->right);
                        delete temp;
                        q1.pop();
                    }
                }
                if (temp->sex == boy) {
                    if (temp == root) {
                        root = temp->right;
                    } else {
                        queue<FamilyMember*> q2;
                        q2.push(root);
                        while(!q2.empty()) {
                            FamilyMember* temp = q2.front();
                            if (temp->left != nullptr) q2.push(temp->left);
                            if (temp->right != nullptr) q2.push(temp->right);
                            if (temp->right && temp->right->id == id) {
                                temp->right = temp->right->right;
                                break;
                            }
                        }
                    }
                    delete temp;
                } else {
                    temp->id = -1;   // make a flag but don't delete
                }
            }
        }
    }
    if (flag == 0) {
        return false;
    } else {
        return true;
    }
}

vector<FamilyTree::FamilyMember*> FamilyTree::queryMember(function<bool(const FamilyMember *person)> filter) {
    vector<FamilyMember*> vec;
    if (root != nullptr) {
        queue<FamilyMember*> q;
        q.push(root);
        while(!q.empty()) {
            FamilyMember* temp = q.front();
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
            if (filter(temp)) {
                vec.push_back(temp);
            }
            q.pop();
        }
    }
    return vec;
}

bool FamilyTree::updateMember(function<bool(const FamilyMember *person)> filter, function<void(FamilyMember *person)> switcher) {
    vector<FamilyMember*> vec = queryMember(filter);
    int count = 0; // count the number of update object
    for(int i = 0; i < vec.size(); i++) {
        switcher(vec[i]);
        count++;
    }
    if (count != vec.size()) { // Judge whether it updates all the objects in vector
        return false;
    } else {
        return true;
    }
}

size_t FamilyTree::countMembers(function<bool(const FamilyMember *person)> filter) {
    return queryMember(filter).size();
}
