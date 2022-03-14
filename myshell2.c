#include "commands.c"
#include "myshell2.h"

int input_file_found = 0;

int main(int argc, char ** argv)
{
    // getcwd(cwd, sizeof(cwd));
    setenv("shell", argv[0], 1);

    /* Batch Mode */
    if(argc==2)
    {
        batch_mode(argv[1]);
    }

    /* keep reading input until "quit" command or eof of redirected input */
    while (!feof(stdin))
    { 
        /* Gets working directory and concatenates it with the divider to make the shell prompt */
        getcwd(cwd, sizeof(cwd));
        char divider[] = "==> ";
        char * prompt = strcat(cwd,divider);

        /* get command line from input */
        fputs (prompt, stdout); // write prompt

            if (fgets (buf, MAX_BUFFER, stdin ))
            {  // read a line

                check(buf);
            }
    }

    return 0;

}


int check(char mystr[MAX_BUFFER])
{
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args

    char newstr[MAX_BUFFER];
    strcpy(newstr, mystr);

    /* tokenize the input into args array */
    arg = args;
    *arg++ = strtok(newstr,SEPARATORS);   // tokenise input

    while ((*arg++ = strtok(NULL,SEPARATORS)));
    if (input_file_found == 0)
    {
        char inputfile[MAX_BUFFER];
        for(int i = 0;args[i];i++)
        {
            if (!strcmp(args[i],"<"))
            {
                input_file_found = 1;
                strcpy(inputfile, args[i + 1]);
                batch_mode(inputfile);
            }
        }
    }

    if (args[0])
    { // if there's anything there
        /* check for internal/external command */
        if (!strcmp(args[0],"cd")) { // "cd" command
            my_cd(args);
            return 1;
        }

        if (!strcmp(args[0],"clr")) {
            my_clr(args);
            return 1;
        }

        if (!strcmp(args[0],"help")) {
            my_help(args);
            return 1;
        }

        if (!strcmp(args[0],"dir")) {
            my_dir(args);
            return 1;
        }

        if (!strcmp(args[0],"environ")) {
            my_environ(args);
            return 1;
        }

        if (!strcmp(args[0],"pause")) {
            my_pause(args);
            return 1;
        }

        if (!strcmp(args[0],"echo")) {
            my_echo(args);
            return 1;
        }

        if (!strcmp(args[0],"quit")) {  // "quit" command
            exit(0);
        }                    // exit programme

        else
        {
            my_execute(args);
            return 1;
        }
    }

    return 0; 
}
