#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

void printArr(string[], int=10);
void printArr(char* arr[], int);
void fillDefaultArr(char* arr[], int); // fill the array provided with default values
vector<string> breakLine(string cmd, char deliminator = ' ');
char* trim(char*); // remove the trailing white space from a string



#endif // HEADER_H
