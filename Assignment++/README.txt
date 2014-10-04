Sample Output

#1

armaan-shell running user:bindra$ ls
armaan-shell++	       armaan-shell++.o
armaan-shell++.c  makefile
armaan-shell running user:bindra$ pwd
/home/users/bindra/OS/project1/Assignment++
armaan-shell running user:bindra$ cd ..
armaan-shell running user:bindra$ pwd
/home/users/bindra/OS/project1
armaan-shell running user:bindra$ ls
Assignment++  BasicAssignment
armaan-shell running user:bindra$ cd ..
armaan-shell running user:bindra$ pwd
/home/users/bindra/OS
armaan-shell running user:bindra$ ls
hw2  hw3  hw4  lab1  lab2  my-shell-history.txt  project1
#2

armaan-shell running user:bindra$ ls
hw2  hw3  hw4  lab1  lab2  my-shell-history.txt  project1
armaan-shell running user:bindra$ emacs
armaan-shell running user:bindra$ /bin/emacs
armaan-shell running user:bindra$ ls
hw2  hw4   lab2				 newTestFile.txt
hw3  lab1  my-shell-history.txt  project1
armaan-shell running user:bindra$ rm newTestFile.txt
armaan-shell running user:bindra$ ls
hw2  hw3  hw4  lab1  lab2  my-shell-history.txt  project1
armaan-shell running user:bindra$ cd project1
armaan-shell running user:bindra$ ls
Assignment++  BasicAssignment
armaan-shell running user:bindra$ mkdir testProj
armaan-shell running user:bindra$ ls
Assignment++  BasicAssignment  testProj
armaan-shell running user:bindra$ rm -r testProj 
armaan-shell running user:bindra$ ls
Assignment++  BasicAssignment
armaan-shell running user:bindra$ 



#3

armaan-shell running user:bindra$ ls
Assignment++  BasicAssignment
armaan-shell running user:bindra$ history
wipe
ls
pwd
cd ..
pwd
ls
cd ..
pwd
ls
wipe
ls
emacs
/bin/emacs
ls
rm newTestFile.txt
ls
cd project1
ls
mkdir testProj
ls
rm -r testProj
ls
history
armaan-shell running user:bindra$

Documentation on Extra Features

1.	      The getenv() system call is used to get username from the environment and that's used in the shell prompt line. For example if I run the program then the shell prompt line would be :
armaan-shell running user:bindra$
	     Where the shell is called armaan-shell and my username is bindra.

2.	     The chdir() system call was implemented to work just like the normal one by using cd to move between directories as can be seen in sample output #1 above

3.	     Just to make it less tiresome and the shell more user friendly I automatically concatenate /bin/ for some common commands listed here
•	     ls
•	     mkdir
•	     rm
•	     pwd
•	     cat
•	     make
•	     mv
•	     cp
Which means to use these commands it is not necessary to write out /bin/ls, instead ls performs the same function.
4.    I added a new command called wipe, that is not case sensitive, thus can even be written as WiPE/wIpe/wipe/WIpe etc. , that clears the screen of the terminal.
5.    Similarly there is another case insensitive command called quit to exit my shell at anytime during the execution of the program
6.    I also implemented a history command that somewhat similar to the terminal history command prints out of list of recently used commands, it can be used by simply typing the shell command:  history
7.    As an added fun feature to personalize it, if you type in armaan as a command, the shell will print out a by line
