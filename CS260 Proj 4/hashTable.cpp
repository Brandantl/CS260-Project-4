/* 
 * File:   hashTable.cpp
 * Author: Brandan Tyler Lasley
 * 
 * Created on November 9, 2014, 2:06 AM
 * Revised on November 20, 2014, 7:05 AM
 */
#include "hashTable.hpp"

hashTable::hashTable() {
    stockList = new linkList[CAPACITY];
    size = 0;
}

hashTable::hashTable(const hashTable& obj) {
    size = 0;
    CAPACITY = obj.getCapacity();
    size = obj.size;
    stockList = new linkList[CAPACITY];
    for (int i = 0; i < CAPACITY; i++) {
        stockList[i] = obj.stockList[i];
    }
}

hashTable::~hashTable() {
    if (CAPACITY > 0) {
        delete [] stockList;
    }
    size = 0;
}

int hashTable::count() {
    return this->size;
}

void hashTable::add(vendor * obj) {
    int index = this->sdbm(obj->getProduct());
    stockList[index].insert(obj);
    size++;
}

bool hashTable::remove(char * key) {
    for (int i = 0; i < CAPACITY; i++) {
        if (stockList[i].getLength() > 0 && stockList[i].exists(key)) {
            if (stockList[i].remove(key)) {
                size--;
                return true;
            }
        }
    }
    return false;
}

int hashTable::retrievearrcount(char * key) {
    int count = 0;
    for (int i = 0; i < CAPACITY; i++) {
        count += stockList[i].productExists(key);
    }
    return count;
}

vendor * hashTable::retrievearr(char * key) {
    int count = this->retrievearrcount(key);
    if (count > 0) {
        vendor * arr = new vendor[count];
        int idx2 = 0;

        for (int i = 0; i < CAPACITY; i++) {
            if (stockList[i].getLength() > 0) {
                const vendor * tmp = this->stockList[i].retrievedata();
                int count_tmp = stockList[i].getLength();
                for (int idx = 0; idx < count_tmp; idx++) {
                 
                    if (strcmp(tmp[idx].getProduct(), key) == 0) {
                        arr[idx2] = tmp[idx];
                        idx2++;
                    }
                    
                }
                delete [] tmp;
            }
        }
        return arr;
    }
    return NULL;
}

vendor * hashTable::retrieve(char * key) {
    int index = this->sdbm(key);
    return stockList[index].retrieve(key);
}

void hashTable::display() {
    for (int i = 0; i < CAPACITY; i++) {
        if (stockList[i].getLength() > 0) {
            cout << stockList[i];
        }
    }
}

void hashTable::monitor() {
    cout << "Starting Block Dump:" << endl;
    for (int i = 0; i < CAPACITY; i++) {
        cout << "BLOCK " << i << ": " << stockList[i].getLength() << endl;
    }
}

int hashTable::sdbm(const char * key) const { // Not really sdbm anymore.
    /*unsigned long hash = 0;
    int c;

    while (c = *key++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    hash = hash % CAPACITY;*/
    
    return (key[0] - 65) % CAPACITY; // I don't how any other way to sort a hash table in alphabetical order.
}

int hashTable::getCapacity() const {
    return this->CAPACITY;
}

const hashTable& hashTable::operator=(const hashTable& obj) {
    this->~hashTable();
    CAPACITY = obj.getCapacity();
    stockList = new linkList[CAPACITY];
    for (int i = 0; i < CAPACITY; i++) {
        vendor * tmp = obj.stockList[i].retrievedata();
        for (int idx = 0; idx < obj.getCapacity(); idx++) {
            this->add(&tmp[idx]);
        }
        delete [] tmp;
    }
    return *this;
}

void hashTable::SaveToDisk(char * filename) {
    ofstream launchCodesFile;
    launchCodesFile.open(filename, ios::trunc); // Truncate those codes, do not want spies stealing them.   
    for (int i = 0; i < CAPACITY; i++) {
        if (stockList[i].getLength() > 0) {
            vendor * data = stockList[i].retrievedata();

            for (int idx = 0; idx < stockList[i].getLength(); idx++) {
                if (data[idx].getEvent()) {
                    launchCodesFile << data[idx].getEvent();
                }
                launchCodesFile << ",";
                launchCodesFile << data[idx].getName();
                launchCodesFile << ",";
                launchCodesFile << data[idx].getPhone();
                launchCodesFile << ",";
                launchCodesFile << data[idx].getProduct() << endl;
            }

            delete [] data;
        }
    }
    launchCodesFile.close();
}