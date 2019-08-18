Have you ever run shell from within vim with `:shell` command? If you so probably this app has a use for you.

If you run shell from within vim, you can comeback (exit from current shell) to vim with `exit` command. The problem, you might've not run the shell from vim and the exit command closes your terminal emulator, very frustrating!

This little app, tells you if you are running current shell within a vim. So you are confident that running `exit` command will take you back to vim.

## How to use
You just need to run the command like below:

`$ isvim`

if current shell is running through a vim process, it will show you the following command:

`VIM is running (234556)`

the number in braces is process id of the vim which ran the current shell. it also exits with 0 shell status code.

If there is no vim as the parent of current shell, nothing will be printed and shell will have 1 as exit code.

## Install
To install:

```
$ make
$ make install
```
