# Simple Shell

## Description
The **Simple Shell** project is a basic implementation of a Unix shell written in C. The goal is to understand the internal mechanisms of a command interpreter, including process management, input/output handling, and environment management.

## Features
- Displays a prompt and waits for a command from the user
- Executes entered commands with their arguments
- Handles errors (e.g., command not found, permissions issues)
- Supports absolute and relative paths
- Reads commands from a file
- Handles built-in commands such as `exit`

- ## Flowchart
- ![Flowchart](https://raw.githubusercontent.com/stan-holberton/holbertonschool-simple_shell/7caa66304a071441ba6c3a0d1479dab15db8a6cd/e3a08b68-f5b2-4005-a5fe-4fad4a1634f9.svg)

## Requirements
- **Operating System**: Linux
- **Compiler**: GCC, compatible with the flags `-Wall`, `-Werror`, `-Wextra`, `-pedantic`

## Compilation
To compile the project, use the following command:
- **gcc -Wall -Werror -Wextra -pedantic *.c -o hsh**

## Usage
Run the shell using: `./hsh`

### Modes

#### Interactive Mode
Example:
- $ ./hsh
- $ ls -l
- $ pwd
- $ exit

#### Non-Interactive Mode
Example:
- echo "ls -l" | ./hsh


## Included Files

### Files and Descriptions
- `execute.c`: Contains the `execute` function, which runs commands in a child process
- `main.c`: The entry point of the shell, handling the command loop and user input
- `main.h`: Header file with function prototypes and global variable declarations
- `splitline.c`: Implements `split_line` to divide user input into an array of arguments
- `AUTHORS`: Lists the contributors to the project

