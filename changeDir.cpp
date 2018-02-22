#include <iostream>
#include <unistd.h>
#include "changeDir.h"
#include "helper.h"

using namespace std;

// prototypes 
void changeDirectory(char*);



int main(int argc, char* argv[]){
    // this func runs when this file is called 
    if(argc > 1){
        changeDirectory(argv[1]);
    }
    else{
        char default_dir[] = "/";
        changeDirectory(default_dir);
    }
}

/**
 * This function is a way of implementing cd command using chdir() sys call
 * @param path to where to go
 */
void changeDirectory(char* path){
    int ret;
    ret = chdir(path);
    if(ret == -1){
        cout << "An error occured changing the dir" << endl;
    }
   char buff[1024];
   getcwd(buff, sizeof(buff));
   cout << "Files in the changed directory: " << buff << " are:-" << endl;
   string ls = "ls";
   string flag = "-a";
   char* args[3];
   args[0] = (char*)ls.c_str();
   args[1] = (char*)flag.c_str();
   args[2] = NULL;
   execvp(args[0], args);
}
