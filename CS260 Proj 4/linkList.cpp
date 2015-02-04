/* 
 * File:   LinkList.cpp
 * Author: Brandan Tyler Lasley
 * 
 * Created on November 9, 2014, 3:05 AM
 * Revised on November 20, 2014, 7:05 AM
 */

#include "linkList.hpp"

linkList::linkList() {
    size = 0;
    headByProduct = NULL;
}

linkList::linkList(const linkList &obj) {
    headByProduct = NULL;
    this->size = 0;
    node * curr = headByProduct;
    while (headByProduct) {
        curr = headByProduct->nextByProduct;
        delete headByProduct;
        headByProduct = curr;
    }
    if (!obj.headByProduct)
        headByProduct = NULL;
    else {
        headByProduct = new node;
        assert(headByProduct != NULL);
        headByProduct->item = obj.headByProduct->item;
        node * destNode = headByProduct;
        node * srcNode = obj.headByProduct->nextByProduct;
        while (srcNode) {
            destNode->nextByProduct = new node;
            assert(destNode->nextByProduct);
            destNode = destNode->nextByProduct;
            destNode->item = srcNode->item;
            srcNode = srcNode->nextByProduct;
            this->size++;
        }
        destNode->nextByProduct = NULL;
    }
}

linkList::~linkList() {
    if (size != 0) {
        node * curr = headByProduct;
        while (headByProduct) {
            curr = headByProduct->nextByProduct;
            delete headByProduct;
            headByProduct = curr;
            size--;
        }
    }
}

bool linkList::insert(vendor * obj) {
    node * prev = NULL;
    node * curr = headByProduct;

    while (curr != NULL && curr->item < obj) {
        prev = curr;
        curr = curr->nextByProduct;
    }

    if (curr && curr->item == obj) {
        return false;
    } else {
        // Create a new node
        node * newNode = new node;
        newNode->item = obj;
        newNode->nextByProduct = curr;
        if (prev == NULL) {
            headByProduct = newNode;
        } else {
            prev->nextByProduct = newNode;
        }
        size++;
        return true;
    }
    return false;
}

bool linkList::remove(char * key) {
    if (size > 0) {
        node * prev = NULL;
        node * curr;
        bool found = false;

        if (size == 0) {
            return false;
        } else {
            for (curr = headByProduct; curr; curr = curr->nextByProduct) {
                if (strcmp(curr->item->getName(), key) == 0) {
                    found = true;
                    if (!prev) {
                        headByProduct = NULL;
                    } else {
                        prev->nextByProduct = curr->nextByProduct;
                    }
                    break;
                }
                prev = curr;
            }

            if (found) {
                delete curr;
                size--;
                return true;
            }
        }
    }
    return false;
}

bool linkList::exists(char * key) {
    if (size > 0) {
        node * curr;
        for (curr = headByProduct; curr; curr = curr->nextByProduct) {
            if (strcmp(curr->item->getName(), key) == 0) {
                return true;
            }
        }
    }
    return false;
}

int linkList::productExists(char * key) {
    int count = 0;
 
    if (size > 0) {
        node * curr;
        for (curr = headByProduct; curr; curr = curr->nextByProduct) {
            if (strcmp(curr->item->getProduct(), key) == 0) {
                count++;
            }
        }
    }
    
    return count;
}

int linkList::getLength(void) const {
    return this->size;
}

vendor* linkList::retrieve(char * const key) {
    if (size > 0) {
        node * curr;
        for (curr = headByProduct; curr; curr = curr->nextByProduct) {
            if (strcmp(curr->item->getProduct(), key) == 0) {
                return curr->item;
            }
        }
    }
    return NULL;
}

vendor* linkList::retrievedata() {
    if (this->size > 0) {
        vendor * tmp = new vendor[this->getLength() + 1];
        node * curr;
        int i = 0;
        for (curr = headByProduct; curr; curr = curr->nextByProduct) {
            tmp[i] = *curr->item;
            i++;
        }
        return tmp;
    }
    return NULL;
}

const linkList& linkList::operator=(const linkList& obj) {
    if (this == &obj)
        return *this;
    else {
        this->size = 0;
        node * curr = headByProduct;
        while (headByProduct) {
            curr = headByProduct->nextByProduct;
            delete headByProduct;
            headByProduct = curr;
        }
        if (!obj.headByProduct)
            headByProduct = NULL;
        else {
            headByProduct = new node;
            assert(headByProduct != NULL);
            headByProduct->item = obj.headByProduct->item;
            node * destNode = headByProduct;
            node * srcNode = obj.headByProduct->nextByProduct;
            while (srcNode) {
                destNode->nextByProduct = new node;
                assert(destNode->nextByProduct);
                destNode = destNode->nextByProduct;
                destNode->item = srcNode->item;
                srcNode = srcNode->nextByProduct;
                this->size++;
            }
            destNode->nextByProduct = NULL;
        }
        return *this;
    }
}

ostream& operator<<(ostream& out, const linkList& obj) {
    if (obj.size > 0) {

        linkList::node * curr;

        for (curr = obj.headByProduct; curr; curr = curr->nextByProduct) {
            out << left << setw(7) << curr->item->getName();
            if (curr->item->getEvent()) {
                out << left << setw(25) << curr->item->getEvent();
            }
            out << left << setw(6) << curr->item->getProduct();
            if (curr->item->getPhone()) {
                out << left << setw(5) << curr->item->getPhone();
            }
            out << endl;
        }
    }
    return out;
}