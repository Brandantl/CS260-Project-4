/* 
 * File:   collection.hpp
 * Author: Brandan Tyler Lasley
 *
 * Created on November 15, 2014, 10:50 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef tree_HPP
#define	tree_HPP
#include "hashTable.hpp"
#include <iostream>
#include <sstream> 
#include <stdlib.h> 
#include <string.h>
#include <fstream>

using namespace std;

class collection {
public:
    collection();
    collection(const collection& obj);
    virtual ~collection();
    void add(const vendor &obj);
    bool remove(char * vendorName);
    const vendor * retrieveByName(char * vendorName);
    const vendor * retrieveByProduct(char * vendorProduct);
    int getArrCount(char * key);
    void displayByName();
    void displayByProduct();
    int count();
    void SaveToDisk(char * filename);
    void ReadFromDisk(char * filename);
    const collection& operator=(const collection& obj);
private:

    struct TreeNode {
        vendor * item;
        TreeNode * left = NULL;
        TreeNode * right = NULL;

        TreeNode(vendor * obj) {
            item = obj;
            left = right = NULL;
        }
    };
    TreeNode * root;
    int size;

    hashTable hashTbl;

    // Tree Stuff.. Gross!
    void addToTree(TreeNode *&root, vendor * obj);
    bool removeFromTree(TreeNode *&root, char * name);
    void displayTree(TreeNode *node);
    void deleteNode(TreeNode *& target);
    void destroyTree(TreeNode *&root);
    bool exists(char * key);
    vendor * getItem(TreeNode *root, char * name);
};

#endif	/* tree_HPP */