/* 
 * File:   main.hpp
 * Author: brandan
 *
 * Created on November 15, 2014, 10:48 AM
 */

#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef MAIN_HPP
#define	MAIN_HPP

#include "collection.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void testRoutine(void);
void displayMenu();
char getCommand();
void executeCmd(char command);
void getString(char * prompt, char * input);
int const MAX_LEN = 100;
collection t;


#endif	/* MAIN_HPP */