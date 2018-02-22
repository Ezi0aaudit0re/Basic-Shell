/**
 * THis class consists of a bunch of helper functions 
 * @author Aman Nagpal 
 * @version 1.0
 */

#include <iostream>
#include <unistd.h>
#include "helper.h"

using namespace std;



/**
 * THis function prints the array it is given
 * @param arr -> the array to pring 
 * @param len -> The length of the array default of 10
 */
void printArr(string arr[], int len){
    for(int i = 0; i < len; i++){
        if(arr[i].compare("") != 0){
            cout << arr[i] << endl;
        }
    
    }
}


void printArr(char* arr[], int len){
    for(int i = 0; i < len; i++){
        if(arr[i] != NULL){
            cout << arr[i] << endl;
        }
    }
}

/**
 * THis method breaks the string based on the deliminator
 */
vector<string> breakLine(string cmd, char deleminator){
        // vector to store values in 
        vector<string> word;
        // break string to array
        stringstream ss(cmd);

        string str;

        while(ss >> str){
            word.push_back(str);

            if(ss.peek() == deleminator)
                ss.ignore();
        }

        return word;
}

void fillDefaultArr(char* arr[], int len){

    for(int i =0; i < len; i++){
        arr[i] = NULL;
    }



}



