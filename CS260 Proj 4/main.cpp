/* 
 * File:   main.cpp
 * Author: Brandan Tyler Lasley
 *
 * Created on November 15, 2014, 10:42 AM
 */

#include "main.hpp"

int main() {
    t.ReadFromDisk("launch-codes");

    char command = 'a';
    displayMenu();
    command = getCommand();
    while (command != 'q') {
        executeCmd(command);
        displayMenu();
        command = getCommand();
    }

    t.SaveToDisk("launch-codes");
    return 0;
}

void displayMenu() {
    cout << "\nImplemented by: Brandan Lasley" << endl;
    cout << "\nWelcome to CS Vendor Management System! " << endl;
    cout << "\ta> add a vendor" << endl
            << "\tr> remove a vendor" << endl
            << "\td> Test Routine" << endl
            << "\tl> Display By Name" << endl
            << "\tk> Display By Product" << endl
            << "\ts> Search By Name" << endl
            << "\tw> Search By Product" << endl
            << "\tq> quit the application" << endl << endl;
}

char getCommand() {
    char cmd;
    cout << "Please enter your choice (a, r, d, l, k, s, w or q):";
    cin >> cmd;
    cin.ignore(100, '\n');
    return tolower(cmd);
}

void executeCmd(char command) {
    char tmp1[MAX_LEN];
    const vendor * tmp2;
    int count;
    vendor ven;
    switch (command) {
        case 'a':
            char name[MAX_LEN];
            char event[MAX_LEN];
            char phone[MAX_LEN];
            char product[MAX_LEN];
            getString("Enter Name: ", name);
            getString("Enter Event: ", event);
            getString("Enter Phone: ", phone);
            getString("Enter Product: ", product);
            ven.setEvent(event);
            ven.setName(name);
            ven.setPhone(phone);
            ven.setProduct(product);
            t.add(ven);
            break;
        case 'r':
            getString("Enter Name: ", tmp1);
            t.remove(tmp1);
            break;
        case 'd':
            testRoutine();
            break;
        case 'l':
            t.displayByName();
            break;
        case 'k':
            t.displayByProduct();
            break;
        case 's':
            getString("Enter Name: ", tmp1);
            tmp2 = t.retrieveByName(tmp1);
            if (tmp2) {
            cout << tmp2->getName();
            cout << " ";
            cout << tmp2->getEvent();
            cout << " ";
            cout << tmp2->getProduct();
            cout << " ";
            cout << tmp2->getPhone();
            cout << endl;
            } else {
                cout << "Not Found :( " << endl;
            }
            break;
        case 'w':
            getString("Enter Product: ", tmp1);
            tmp2 = t.retrieveByProduct(tmp1);
            count = t.getArrCount(tmp1);
            if (tmp2) {
            for (int i = 0; i < count; i++) {
                cout << tmp2[i].getName();
                cout << " ";
                cout << tmp2[i].getEvent();
                cout << " ";
                cout << tmp2[i].getProduct();
                cout << " ";
                cout << tmp2[i].getPhone();
                cout << endl;
            }
            delete [] tmp2;
            } else {
                cout << "No Results :( " << endl;
            }
            break;
        default: cout << "illegal command!" << endl;
            break;
    }
}

void getString(char * prompt, char * input) {
    cout << prompt;
    cin.get(input, MAX_LEN, '\n');
    cin.ignore(100, '\n');
}

void testRoutine(void) {
    collection h;
    vendor a;
    a.setName("A");
    a.setProduct("B");
    vendor b;
    b.setName("B");
    b.setProduct("C");
    vendor c;
    c.setName("C");
    c.setProduct("A");

    cout << "========== TEST ROUTINE! ==========" << endl << endl;


    cout << "========== BST TEST/FUNCTIONS ==========" << endl;
    cout << "Adding A" << endl;
    h.add(a);
    cout << "Adding B" << endl;
    h.add(b);
    cout << "Adding C" << endl;
    h.add(c);


    cout << "========== LIST IN ORDER (By Name) ==========" << endl;
    h.displayByName();

    cout << "========== DELETE A (root) ==========" << endl;
    h.remove("A");
    h.displayByName();

    cout << "========== RETRIEVE (B) ==========" << endl;
    if (h.retrieveByName("B")) {
        cout << h.retrieveByName("B")->getName() << endl;
    }

    cout << "========== REMOVE (C) ==========" << endl;

    h.remove("C");
    h.displayByName();

    cout << "========== REMOVE (B (ROOT) ) ==========" << endl;

    h.remove("B");
    h.displayByName();
    cout << endl;
    cout << "If no items appear above, then all items were removed successfully!" << endl;

    cout << "========== HASH TABLE ==========" << endl << endl;

    cout << "Adding [product] C" << endl;
    h.add(b);
    cout << "Adding [product] B" << endl;
    h.add(a);
    cout << "Adding [product] A" << endl;
    h.add(c);

    cout << "========== LIST IN ORDER (By Product) ==========" << endl;
    h.displayByProduct();

    cout << "========== RETRIEVE (B) ==========" << endl;

    const vendor * tmp = h.retrieveByProduct("B");

    for (int i = 0; i < h.getArrCount("B"); i++) {
        cout << tmp[i].getProduct() << endl;
    }

    delete [] tmp;

    cout << "---------- NOTE: Items removed by name! ----------" << endl;

    cout << "========== REMOVE (A) ==========" << endl;
    h.remove("A");
    h.displayByProduct();

    cout << "========== REMOVE (C) ==========" << endl;
    h.remove("C");
    h.displayByProduct();

    cout << "========== REMOVE (B) ==========" << endl << endl;
    h.remove("B");
    h.displayByProduct();
    cout << "If no items appear above, then all items were removed successfully!" << endl << endl;

    cout << "========== TEST ROUTINE HAS BEEN COMPLETED! ==========" << endl << endl;
}