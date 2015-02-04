/* 
 * File:   hashTable.hpp
 * Author: Brandan Tyler Lasley
 *
 * Created on November 9, 2014, 2:05 AM
 * Revised on November 20, 2014, 7:05 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef HASHTABLE_HPP
#define	HASHTABLE_HPP
#include "vendor.hpp"
#include "linkList.hpp"
#include <iostream>
#include <fstream>
using namespace std;

class hashTable {
public:
    hashTable();
    hashTable(const hashTable& obj);
    virtual ~hashTable();
    void add(vendor * obj);
    bool remove(char * key);
    vendor * retrieve(char * key);
    vendor * retrievearr(char * key);
    int retrievearrcount(char * key);
    void display();
    void monitor();
    int count();
    void SaveToDisk(char * filename);
    int getCapacity() const;

    const hashTable& operator=(const hashTable& obj);
private:
    int CAPACITY = 26;
    int size = 0;
    int top;
    linkList * stockList;
    int sdbm(const char * key) const;
};

#endif	/* HASHTABLE_HPP */