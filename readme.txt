This is the implementation of Project 1 for CS575 

The program is written in C++


We use g++ as a compiler

Follow the following steps - 

1.) g++ -o changeDir changeDir.cpp
2.) g++ project.cpp helper.cpp


We run the program using ./a.out 

Implementation of chdir():

We execute the chdir command using -> cd /

The program links to commands in refrence to root 
Therefore a command such as ~/Desktop would give an error 
A command such as -> cd /Users/<user> would work 

NOTE = Because chdir only changes the directory of the current process i print out the ls of the changed directory of that particular process 


I implemented the cd functionality in the child process the working directory of the child process if i implement it in the parent process the process finishes once the execvp has been implemented
