# Minishell

Minishell is a simple command-line shell interpreter implemented in C as part of a School 42 team project. The shell is designed to handle various commands, implement builtins, and support redirections, pipes, and environment variables.
## Usage
```sh
git clone https://github.com/misteriaud/42_minishell.git
cd 42_minishell
make
./minishell
```
## Features

Minishell provides the following features:

- Displaying a prompt when waiting for a new command.
- Working history.
- Searching and launching the right executables.
- Handling quotes and special characters.
- Implementing redirections (`<`, `>`, `<<`, `>>`).
- Implementing pipes (`|`).
- Handling environment variables.
- Handling `$?` to expand to the exit status of the most recently executed foreground pipeline.
- Handling signals (`ctrl-C`, `ctrl-D`, `ctrl-\`).
- Implementing builtins (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).

## Builtins

Minishell supports the following builtins:

- `echo` with option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options
