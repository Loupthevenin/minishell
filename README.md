# Minishell

## 🐚 Objective

The goal of this project is to create a basic UNIX shell from scratch. This exercise dives deep into the fundamentals of process management, signal handling, file descriptors, and environment manipulation in C, providing a hands-on experience with many low-level concepts used by actual shells like `bash`.

## 🧠 Skills Involved

- Advanced use of file descriptors and pipes
- Process creation and management (`fork`, `execve`, `wait`)
- Signal handling (`SIGINT`, `SIGQUIT`)
- Parsing and lexical analysis
- Implementing built-in shell commands
- Memory management and clean resource handling
- Modular and norm-compliant C code

## 🚀 Features

### Mandatory

- **Prompt Display**: Shows a prompt waiting for user input.
- **Command Execution**: Executes commands based on `$PATH`, absolute or relative paths.
- **Redirections**: Supports `<`, `>`, `<<`, `>>`.
- **Pipes**: Handles pipelines (`cmd1 | cmd2 | ...`).
- **Quotes**: Supports single (`'`) and double (`"`) quotes.
- **Environment Variables**: Supports `$VAR`, `$?`, etc.
- **Signal Handling**: Correctly manages `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.
- **Builtins Implemented**:
  - `echo [-n]`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **History**: Uses the GNU Readline library for command history and line editing.

## 🛠️ Usage

```bash
# Clone your repo and go to project directory
make            # Compile the shell

./minishell     # Launch the shell

```
