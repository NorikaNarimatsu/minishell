# Minishell

## Overview
Minishell is a custom shell that replicates some of the features of Bash. This project introduces fundamental concepts of shell functionality, including command execution, piping, redirections, and environment variable management. It aims to provide a deeper understanding of process control, file descriptors, and command parsing.

## Objectives
1. Develop a shell that executes commands from the system PATH and supports built-in commands.
2. Implement piping, redirections, and environment variable expansion.
3. Handle signals for `ctrl-C`, `ctrl-D`, and `ctrl-\`, creating a user-friendly command-line interface.

## Features

- **Command Execution**: Executes commands found in the system PATH or as built-in commands.
- **Piping**: Supports pipes (`|`) to connect commands in sequence.
- **Redirections**: Handles input (`<`), output (`>`), and append (`>>`) redirections.
- **Environment Variables**: Expands environment variables using `$`.
- **Built-in Commands**:
  - `echo` (with `-n` option)
  - `cd` (change directory)
  - `pwd` (print working directory)
  - `export` (set environment variables)
  - `unset` (remove environment variables)
  - `env` (display environment variables)
  - `exit` (terminate shell)


## Usage
  - git clone <[repository-url](https://github.com/NorikaNarimatsu/minishell>
  - cd minishell
  - make
  - ./minishell
   

## Makefile Commands
- make: Compiles the minishell executable.
- make clean: Removes object files.
- make fclean: Removes object files and the minishell executable.
- make re: Recompiles the shell from scratch.
