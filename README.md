# Custom-Linux-Shell-in-C

This project is a basic implementation of a custom shell (like bash) written in C. It mimics the behavior of a Linux command-line interface and supports multiple basic shell features.

-----

## Features:

 -Command execution (e.g, ls, pwd, date, etc.)  
 -Built-in commands: cd, exit, history  
 -Background process execution using &  
 -History tracking of executed commands  
 - Simple command parsing using fork(), execvp() and wait()
 
-----

## File Information

- custom_linux_shell.c – Main source file containing shell logic
- README.md – Project documentation (you’re reading it!)

 -----

 ## How to Compile and Run:
 
Make sure you're on a Linux-based system or using WSL.

bash
gcc custom_linux_shell.c -o myshell
./myshell

## output
![demo_ouput](https://github.com/user-attachments/assets/35b9109c-9a8f-4e6e-9c99-30ad2208056a)



