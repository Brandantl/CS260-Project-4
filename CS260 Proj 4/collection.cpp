/* 
 * File:   collection.cpp
 * Author: Brandan Tyler Lasley
 * 
 * Created on November 15, 2014, 10:50 AM
 */

#include "collection.hpp"

// ================ CONSTRUCTOR / SELF DESTRUCTOR =================

collection::collection() {
    root = NULL;
}

collection::collection(const collection& obj) {

}

collection::~collection() {
    // Destroy Tree!!!
    if (root) {
        destroyTree(this->root);
    }

}

// ================= CLASS INTERFACE ============================

void collection::add(const vendor & obj) {
    if (!this->exists(obj.getName())) {
        vendor data;
        data = obj;
        vendor * ptrItem = new vendor;
        *ptrItem = data;
        hashTbl.add(ptrItem);
        addToTree(this->root, ptrItem);
    }
}

bool collection::remove(char * vendorName) {
    if (!hashTbl.remove(vendorName)) {
        return false;
    }
    return removeFromTree(this->root, vendorName);
}

const vendor * collection::retrieveByName(char * vendorName) {
    return this->getItem(this->root, vendorName);
} // Tree Stuff

int collection::count() {
    return hashTbl.count();
}

const vendor * collection::retrieveByProduct(char * vendorProduct) {
    return this->hashTbl.retrievearr(vendorProduct);
}

int collection::getArrCount(char * key) {
    return hashTbl.retrievearrcount(key);
}

void collection::displayByName() {
    displayTree(this->root);
} // Tree Stuff

void collection::displayByProduct() {
    hashTbl.display();
}
// ====================== Private Tree Stuff =======================

void collection::addToTree(TreeNode *&root, vendor * obj) {
    if (root == NULL) {
        root = new TreeNode(obj);
        size++;
        return;
    } else if (*obj < *root->item) { // Not having those *'s was the most time consuming and brain hurting thing ever.
        addToTree(root->left, obj);
    } else {
        addToTree(root->right, obj);
    }
}

bool collection::removeFromTree(TreeNode *&root, char * name) {
    if (!root) {
        return false;
    }
    int result = strcmp(root->item->getName(), name);
    if (result == 0) {
        deleteNode(root);
        return true;
    } else if (result < 0) {
        return removeFromTree(root->left, name);
    } else {
        return removeFromTree(root->right, name);
    }
    return false;
}

void collection::deleteNode(TreeNode *& target) {
    TreeNode * tmp;
    if (!target->left && !target->right) { // LEAF
        delete target->item;
        delete target;
        target = NULL;
    } else if (!target->left) { // NO LEFT
        tmp = target;
        target = target->right;
        tmp->right = NULL;
        delete tmp->item;
        delete tmp;
    } else if (!target->right) { // NO RIGHT
        tmp = target;
        target = target->left;
        tmp->left = NULL;
        delete tmp->item;
        delete tmp;
    } else { // BOTH CHILDREN PRESENT
        TreeNode * prev = NULL;
        TreeNode * curr = target->right;
        while (curr->left) {
            prev = curr;
            curr = curr->left;
        }
        delete target->item;
        target->item = curr->item;
        if (!prev) {
            target->right = curr->right;
        } else {
            prev->left = curr->left;
        }
        curr->right = NULL;
        delete curr;
    }
    size--;
}

void collection::destroyTree(TreeNode *&root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root->item;
        delete root;
        root = NULL;
    }
}

void collection::displayTree(TreeNode *node) {
    if (node != NULL) {
        displayTree(node->left);
        cout << left << setw(7) << node->item->getName();
        cout << left << setw(25);
        if (node->item->getEvent()) {
            cout << node->item->getEvent();
        } else {
            cout << "";
        }
        cout << left << setw(6) << node->item->getProduct();
        cout << left << setw(5);
        if (node->item->getPhone()) {
            cout << node->item->getPhone();
        } else {
            cout << "";
        }
        cout << endl;
        displayTree(node->right);
    }
}

vendor * collection::getItem(TreeNode *root, char * name) {
    if (!root) {
        return NULL;
    }
    int result = strcmp(root->item->getName(), name);
    if (result == 0) {
        return root->item;
    } else if (result < 0) {
        return getItem(root->left, name);
    } else {
        return getItem(root->right, name);
    }
    return NULL;
}

// ======================== MISC STUFF ============================

void collection::SaveToDisk(char * filename) {
    hashTbl.SaveToDisk(filename); // I don't know how to get data efficiently with BST
}

void collection::ReadFromDisk(char * filename) {
    ifstream codes(filename);
    while (codes) {
        string s;
        if (!getline(codes, s)) break;
        istringstream ss(s);
        while (ss) {
            vendor obj;
            string s;
            if (!getline(ss, s, ',')) break;
            obj.setEvent(s.c_str());
            if (!getline(ss, s, ',')) break;
            obj.setName(s.c_str());
            if (!getline(ss, s, ',')) break;
            obj.setPhone(s.c_str());
            if (!getline(ss, s, ',')) break;
            obj.setProduct(s.c_str());
            this->add(obj);
        }
    }
}

const collection& collection::operator=(const collection& obj) {
    this->root = obj.root;
    this->hashTbl = obj.hashTbl;
    this->size = obj.size;
    return * this;
}

bool collection::exists(char * key) {
    if (this->getItem(this->root, key)) {
        return true;
    }
    return false;

}