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

- flowchart TD
    A[Start] --> B[Initialize Shell]
    B --> C{Interactive Mode?}
    C -->|Yes| D[Display Prompt]
    C -->|No| E[Wait for Input]
    D --> E
    E --> F[Read Input]
    F --> G{Input Valid?}
    G -->|No| H[Handle Error]
    G -->|Yes| I[Parse Command]
    I --> J{Built-in Command?}
    J -->|Yes| K[Execute Built-in]
    J -->|No| L[Fork Process]
    L --> M{Fork Successful?}
    M -->|No| H
    M -->|Yes| N[Execute Command]
    N --> O{Execution Status}
    O -->|Success| P[Wait for Child]
    O -->|Failure| Q[Handle Error]
    P --> R{Continue?}
    K --> R
    Q --> R
    H --> R
    R -->|Yes| C
    R -->|No| S[Cleanup & Exit]
    S --> T[End]
- `main.c`: The entry point of the shell, handling the command loop and user input
- `main.h`: Header file with function prototypes and global variable declarations
- `splitline.c`: Implements `split_line` to divide user input into an array of arguments
- `AUTHORS`: Lists the contributors to the project
