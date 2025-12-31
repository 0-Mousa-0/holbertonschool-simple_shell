# Simple Shell Project (Holberton School-SAU 1025)

## Overview
This project is a simplified custom implementation of a UNIX command-line interpreter (shell). It demonstrates the core functionality of a shell, including command execution, process management using system calls, and environment handling.

## Features
The `simple_shell` implementation covers the following milestones:
- **0.1**: Basic command execution (full paths only) and EOF (Ctrl+D) handling.
- **0.2**: Support for command-line arguments.
- **0.3**: Implementation of the `PATH` variable to find executables.
- **0.4**: Implementation of the `exit` built-in command.
- **1.0**: Implementation of the `env` built-in command to print current environment variables.

## How it Works
The shell operates in a loop performing the following steps:
1. **Prompt**: Displays a prompt (e.g., `:) `) and waits for user input.
2. **Parser**: Reads the input line using `getline` and splits it into tokens (command and arguments) based on spaces.
3. **Search**: If the command is not a full path, the shell searches through directories listed in the `PATH` environment variable.
4. **Execution**: 
   - If the command is a built-in (like `exit` or `env`), it is handled internally.
   - Otherwise, the shell checks if the file exists. If so, it `fork`s a new process and uses `execve` to run the command.
5. **Wait**: The parent process waits for the child to complete before displaying the prompt again.

## Requirements and Permitted Functions
- **Betty Style**: All code complies with Betty linter standards.
- **System Calls used**: `execve`, `fork`, `wait`, `write`, `stat`, `open`, `close`, `getline`.
- **Memory Management**: All allocated memory is properly freed to avoid leaks.

## Usage
To compile the shell:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
To run the shell:
```bash
./hsh
```
Example interaction:
```bash
:) /bin/ls
file1 file2 hsh
:) ls -l
total 12
-rw-r--r-- 1 user group 100 Jan 1 12:00 main.c
:) env
USER=mousa
PATH=/usr/bin:/bin
:) exit
```
---
## Authors
Mousa Abdullah Alrizqi / Nizar Maharrak SAU 1025 members.
