myshell()                                                    General Commands Manual                                                    myshell()

NAME
       myshell - Cian Sullivan SHell

SYNOPSIS
       myshell [options] [command_string | file]

COPYRIGHT
       myshell is Copyright (C) by Cian Sullivan

DESCRIPTION
       myshell is experimental shell which supports input from the command line and input from a file. You can pass in custom commands - 

SHELL BUILTIN COMMANDS
       cd  - change the current default directory  . If the  argument is not present, report the current directory. If the directory does not exist an appropriate error is reported. This command changes the PWD environment variable.

       clr - clears the screen.

       dir  - list the contents of directory e.g. ls -al <directory>

       environ - list all the environment strings

       echo  - echo  on the display followed by a new line.

       help - display the user manual using the more filter.

       pause - pause operation of the shell until 'Enter' is pressed

       quit - quit the shell

       Other input commands are interpreted as program invocations. [3]

INVOCATION
       The shell is capable of taking its input from the command line. Enter any commands you would like e.g. "echo hello".

       The shell is capable of taking its command line input from a file. i.e. if the shell is invoked with a command line argument: ./myshell batchfile then batchfile is assumed to contain a set of command lines for the shell to process. When the end-of -file is reached, the shell exits. If the shell is invoked without a command  line argument it solicits input from the user via a prompt on the display.

RESERVED WORDS
       None

COMMENTS
       Comments are not supported.

I/O REDIRECTION
       The shell supports i/o-redirection for both stdin and stdou i.e. the command line:
       programname arg1 arg2 < inputfile > outputfile
       will execute the program programname with arguments arg1 and arg2, the stdin FILE stream r-
       eplaced by inputfile and the stdout FILE stream replaced by outputfile. Stdout redirection 
       is also be possible for the internal commands: dir, environ, echo, and help. [4]

       With output redirection, if the redirection character is > then the outputfile is created 
       if it does not exist and truncated if it does. If the redirection token is >> then output-
       file is created if it does not exist and appended to if it does.

ENVIRONMENT CONCEPTS
       You can pass in the "environ" command to the shell. This will list all the environment
       variables. It is the equivalent of typing "env" in a bash SHell. In other words it will
       display the names and values of each variable currently set. For example PATH=/usr/local
       /sbin:/. In this case when you enter a command to run, the folder "/usr/local/sbin" will 
       be searched for that command. [2]

       When you use the "cd" command to change directory, it will also change the PWD environment variable. It will get the current working directory and show this in the environ section as "PWD=<workingdirectory>".

       This shell also creates a new environment variable for you called shell=</myshell>. The value of this environment variable will be the full path for the shell executable. 

       All other command line input is interpreted as program invocation which should be done by the shell forking and execing the programs as its own child processes. The programs should be executed with an environment that contains the entry: parent= /myshell where /myshell is as described in the last bullet point above.

       Programms which are executed by myshell have an environemnet variable called parent=<myshell>.

PROCESS CONCEPTS
       By default this shell runs in the foreground. The shell will not return to the command line prompt until the commands have finished executing.

       The shell also supports background execution of programs. This is not implemented for internal built in commands, but is for external commands. An ampersand , or & character, at the end of the command line instructs the shell to return to the command line prompt immediately after launching that program whilst it continues to run in the background [1].

AUTHORS
       Cian Sullivan Dublin City University
       cian.sullivan100@gmail.com

BUG REPORTS
       Comments and bug reports concerning this manual page should be directed to cian.sullivan100@gmail.com

BUGS
       If the redirection token is >> then outputfile is created if it does not exist and appended to if it does - Not implemented.

REFERENCES
       [1] Daniel Plerre Bovet, Marco Cesati, Understanding the Linux Kernel: From I/O Ports to Process Management, Massachusetts: O'Reilly , 1 Nov. 2005

       [2] Christopher Negus, Linux Bible, New Jersey: Wiley, 8 Jun. 2020

       [3]  Ellen Siever, Stephen Figgins, Robert Love, Arnold Robbins (Author)Linux in a Nutshell: A Desktop Quick Reference, Massachusetts: O'Reilly , 1 Nov. 2005

       [4] Brian Ward, How Linux Works: What Every Superuser Should Know, San Francisco: No Starch Press, 21 Nov. 2014

