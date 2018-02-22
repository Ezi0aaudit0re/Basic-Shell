/**
 * This project is a very basic shell 
 * It uses fork() to create a child process and exec() to load a program to it 
 * @author Aman Nagpal 
 * @version 1.0 */

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <stdio.h>


// custom header files 
#include "helper.h"


using namespace std;

#define ARR_LENGTH 10


// prototypes of functions 
void addHistory(string[], int, string);
pid_t createProcess(char* args[], bool);
void changeDirectory(char *);
void parseCommand(vector<string>, string );
void pipeValues(char* args[], char* args2[], vector<string>);
void pipeFunctionality(char* args[], vector<string>);





int main(int argc, char* argv[]){


    // check if program ran with argument
    if(argc == 1){

        // create an array to store history
        string history[ARR_LENGTH];
        int counter = 0; // keep track of the counter to store history

        cout << "Welcome to this implementation of bash. Enter 'quit' at any time to exit" << endl;

        // loop to get input again and again
        while(true){
            // Get the currect directory
            char dir[1024];
            getcwd(dir, sizeof(dir));




            // get command from the user
            string cmd;
            cout << "user@CS575 " << dir << ": ";
            getline(cin, cmd);

            // check if the string has ";" to run multiple commands 
            if(cmd.find(";") != string::npos){
                // source - http://www.cplusplus.com/reference/cstring/strtok/
                char* str = (char*)cmd.c_str();
                char* pch;
                pch = strtok(str, ";");
                while(pch != NULL){
                    // add the command to history
                    addHistory(history, counter, pch); 
                    counter++;

                    // get rid of trailign white spaces
                    pch = trim(pch);


                    vector<string> word = breakLine(pch);
                    parseCommand(word, pch);

                    // reset the value
                    pch = strtok(NULL, ";");
                
                
                }
                // skip to the next itteration of the loop 
                // we do this so that we donot go again to parseCommand
                continue;
            
            
            }
            else{
                // only single command
                 
                 // add to the history
                 addHistory(history, counter, cmd);
                 // update the counter 
                 counter++;
            
            
            }


            vector<string> word = breakLine(cmd);

            // quit the program if the user entered quit  
            if(cmd.compare("quit") == 0){
                exit(0);
            }
            
            else if(cmd.find("cd") != string::npos){
                // change the location of the program
                char* loc = (char*)word.at(1).c_str();
                chdir(loc);
            }
            else if(cmd.compare("history") == 0){
                printArr(history, ARR_LENGTH);
            }
            else{
                parseCommand(word, cmd);
            }
            


            



        
        }

    }

}


/**
 * THis method creates a process using fork()
 * Loads a program to it using execvp()
 * @param args -> The arguments for functions execvp
 * @param wait_process -> true if parent process needs to wait else false
 * @return -> The PID of the process created
 */
pid_t createProcess(char* args[], bool wait_process=true){

    pid_t pid;
    
    // create a new process 
    pid = fork();

    pid_t id = getpid();



    if(pid == 0){
        execvp(args[0], args);
        exit(0);
    }
    else if (pid < 0){
        // there was some problem creating the process
        cout << "THere was some problem creating the process" << endl;
    
    }
    else{
        // parent process 
        if(wait_process){
            // the program wants to run in the foregrond
            wait(NULL);
        }
    }


    return id;

}




/**
 * This function adds to the history array 
 * @param history array
 * @param counter -> location to add
 * @param cmd -> The command to add to the array
 * @return counter -> The updated counter
 */

void addHistory(string arr[], int counter, string cmd){
    if(counter < 10){
        arr[counter] = cmd;
    }
    else{
        // if the counter is over 10 
        for (int itter = 0; itter < (ARR_LENGTH - 1); itter++){ 
            // to array length -1 because we only need to go to arr[8]
            // we add to arr[9]
            arr[itter] = arr[itter+1];
        }
        arr[ARR_LENGTH - 1] = cmd;
    }

}

void pipeFunctionality(char* args[], vector<string> word){

        // pipe found
        // break into two parts 
        char* args2[ARR_LENGTH];
        fillDefaultArr(args2, ARR_LENGTH);
        pipeValues(args, args2, word);

        /**
         * We are currently in the main process of the program 
         * We create a child process 
         * In that child process we funrther create a grandchild process 
         * Now we use the grand child process to run the first part of the pipe 
         * We use the child process, which is the parent of the grand parent process 
         *      to run the second part of the pipe command
         * We do this becuase when the child process terminates we donot 
         *      leave the program becuase the child process of the main process has only terminated
         */
        pid_t pid; 
        pid = fork(); // create a child process 
        if(pid <0){
            perror("Problem creating Pid");
            exit(1);
        }
        else if(pid == 0){

            int fd[2];
            pipe(fd);
            pid_t newPid = fork(); // here we create the grand child process
            if(newPid == 0){

                // grand child process
                close(1); // close STDOUT
                dup(fd[1]); // dublicate it to write end of the pi[e

                close(fd[0]); // close the read end
                execvp(args[0], args); // execute the program 
                close(fd[1]); // close the read end of the file
                exit(0);
            
            }
            else if(newPid < 0){
            
                cout << "Error creating the process" << endl;
                exit(1);
            
            }
            else{

                // parent process: child process of the main process
            
                wait(NULL); // wait until child process is completed

                close(0); // close the STDIN file
                dup(fd[0]); // dunlicate to the read side of the pipe 
                close(fd[1]); // close the write side of the pipe
                execvp(args2[0], args2); // execute the program
                close(fd[0]); // close the read end of the file
            
            
            
            }
        
        }
        else{
            // parent process
            wait(NULL);

        }

}


/**
 * This function checks weather cd command or pipe 
 * @param cmd -> The command to parse through
 */
void parseCommand(vector<string> word,  string cmd){

    char* args[(int)word.size()];

    

    if(cmd.find("|") != string::npos){

        pipeFunctionality(args, word);

    }
    else{
        for(int i = 0; i < (int) word.size(); i++){
            args[i] = (char*)word.at(i).c_str();
        }
        args[(int)word.size()] = NULL;
        

        // NOTE - WE donot need to fill the last spot of args with NULL because
        //        fillDefaultArr does that
        if(cmd.find("&") != string::npos){
            // run in the back ground
            createProcess(args, false);
        }
        else{
            // run in the foreground
        
            createProcess(args);
        }

    }
    


}

/**
 * This method breaks the cmd into two parts 
 * @param -> args consists of the first part BEFORE |
 * @param -> args2 contains the second part AFTER |
 */
void pipeValues(char* args[], char* args2[], vector<string> word){


    for(int i = 0; i < (int) word.size(); i++){

        // get all the parameters till pipe
        if(word.at(i).compare("|") == 0){
            fillDefaultArr(args2, ARR_LENGTH);
            
            i++; // we do this to start getting the value after |
            // get the second part of pipe after |
            for(int j = i; j < (int) word.size(); j++){
                args2[j - i] = (char*)word.at(j).c_str();
            }
            break; // break out of the outer loop the one with i
        }
        else{
            // get the forst part of the pipe
            args[i] = (char*)word.at(i).c_str();
        }
    }




}
