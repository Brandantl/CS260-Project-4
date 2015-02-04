/* 
 * File:   LinkList.hpp
 * Author: Brandan Tyler Lasley
 *
 * Created on November 9, 2014, 3:05 AM
 * Revised on November 20, 2014, 7:05 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef LINKLIST_HPP
#define	LINKLIST_HPP
#include "vendor.hpp"
#include <assert.h>
#include <iostream>
#include <iomanip>
using namespace std;

class linkList {
public:
    linkList(void);
    linkList(const linkList &obj);
    ~linkList();

    bool insert(vendor * obj);
    bool remove(char * key);
    bool exists(char * key);
    int productExists(char * key);
    int getLength(void) const;
    vendor* retrieve(char * const key);
    vendor* retrievedata();

    const linkList& operator=(const linkList& obj);
    friend ostream& operator<<(ostream&, const linkList&);
private:

    struct node {
        vendor * item;
        node * nextByProduct;
    };

    node * headByProduct;
    int size;
};
#endif	/* LINKLIST_HPP */