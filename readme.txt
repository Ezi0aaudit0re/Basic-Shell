This is the implementation of Project 1 for CS575 

The program is written in C++


We use g++ as a compiler

Follow the following steps - 

g++ project.cpp helper.cpp


We run the program using ./a.out 

Implementation of chdir():

We change the current working directory of bash

We execute the chdir command using -> cd /

The program links to commands in refrence to root 
Therefore a command such as ~/Desktop would give an error 
A command such as -> cd /Users/<user> would work 


We can execute pipe commands also 

Commands tested - 
ls | wc -c
ls | head-3

NOTE -> WE achine piping through a function since this function is called through the main process we need to create a child process and in that process create a grand child process. Since parent and children share pipe file the first part of the pipe is executed by the grandchild process and the second part of the pipe is executed by child process(grandchild's parent)


We can execute multiple commands using the format <command1>; <command2>
