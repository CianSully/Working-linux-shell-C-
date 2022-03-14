#include <stdlib.h>
#include <stdio.h> // Used for basic input/output stream
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h> // Used for handling Qdirectory files
#include <errno.h>  // For error codes and handling

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators
#define my_RL_BUFSIZE 1024
#define my_TOK_BUFSIZE 64
#define my_TOK_DELIM " \t\r\n\a"

char cwd[1024];
char buf[MAX_BUFFER];                      // line buffer
int token_count;


/* Function Declarations for builtin shell commands: */
int check(char str[MAX_BUFFER]);
int batch_mode(char * filename);
int my_cd(char **args);
int my_help(char **args);
int my_quit(char **args);
int my_clr(char **args);
int my_dir(char **args);
int my_environ(char **args);
int my_echo(char **args);
int my_pause(char **args);
int my_execute(char ** args);
int external_commands(char ** args);