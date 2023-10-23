## UID: 123456789
##change from VM
## Pipe Up

One sentence description
The purpose of this lab was to implement my own version of the pipe [|] operator in a shell script.
## Building

Explain briefly how to build your program
To build this program, run 'gcc -o pipe pipe.c'. From there, call './pipe com1 com2 com3... comn', replacing the comx with whatever commands you want to pipe.
## Running

Show an example run of your program, using at least two additional arguments, and what to expect
./pipe ls cat would produce a vertical line of the fils in the given directory, in this case being the files from the original skeleton code, pipe, and the __pycache__ directory.
./pipe ls cat  wc would produce the word count of the relevant files given from ls|cat, or in this case, 6 6 56.

## Cleaning up

Explain briefly how to clean up all binary files
To get rid of the build 'pipe', run 'make clean'. To get rid of the excess __pycache__ directory that occurs after running the python tests, enter the directory, delete the file inside, leave the directory, and delete the directy.
