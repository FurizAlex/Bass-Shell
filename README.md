# <img src='bassShellIcon.png' width=48> Our Minature Shell Project

<img width="1920" height="200" alt="bassHeader" src="https://github.com/user-attachments/assets/c2ae96b2-5212-4ba7-baef-b7142b35ed7c" />

> A Miniture shell project where you create a fairly simple Unix Shell. This shell has parsing for commands, execution, piping, redirection to name a few. The goal for this project is to essentially understand how shells works. It's an introduction to systems programming & CLI

<img width="2000" height="500" alt="bassShellHeader" src="https://github.com/user-attachments/assets/bfe940c5-e5ca-4bbd-97f1-9a918726dbab" />

## INSTRUCTIONS FOR COMPILATION:
```
make
make re - Remake Compilation
make clean - Clean up object files
make fclean - Clean up object files & program
run ./minishell
```

## Available Options
The shell runs executables from an absolute, relative or environment path. `[/bin/ls]` or `[ls]`. You can also run commands with `''` or `""` which works the same like it does in Bash.

You can also separate commands with `;`, As well as redirection support with `<` `>` `|` `>>`

Environment Variables are handled such as `$HOME`, `$?` is supported as well. You can also access environment variables with `env` & add `export` to add an environment variable.

`CTRL + C` `CTRL + D` `CTRL + \` are supported as well, making interrupting, quitting and throwing an EOF respectively.

A fair few `"built-in"` functions have also been implemented, specifically `echo` `pwd` `cd` `env` `export` `unset` & `exit`

<img width="1920" height="200" alt="bassHeader" src="https://github.com/user-attachments/assets/c2ae96b2-5212-4ba7-baef-b7142b35ed7c" />

![BassShellHeader](https://github.com/user-attachments/assets/40eee59d-8865-4ef2-98fb-9013d6f2a8b3)
