#include "myshell.h"

char outputfile[MAX_BUFFER]; // file to redirect standard output to

/* Handle Batch mode */
int batch_mode(char * filename)
{
  FILE *in_file  = fopen(filename, "r"); // this is opening the batch file or the standard input file the user passes in

  // test for files not existing. 
  if (in_file == NULL) 
    {
      printf("Error! Could not open file\n");
      exit(-1);
    }

  rewind(in_file); // move to start of file, make sure your reading from start of file
  while( fgets (buf, MAX_BUFFER, in_file)!=NULL )
  {
    buf[strcspn(buf, "\n")] = 0; // remove new line
    buf[strcspn(buf, "\r")] = 0; // remove carrige return
    check(buf); // pass the input from the file back into check function
  }

  exit(0);
}

/* Change Directory */
int my_cd(char **args)
{
  char cwd[1024];

  if (args[1] == NULL)
  {
    getcwd(cwd, sizeof(cwd)); // get and print current working directory
    printf("%s\n", cwd);
  }

  else
  {
    /* error for directory not existing */
    if (chdir(args[1]) != 0)
    {
      printf("This directory does not exist!\n");
    }

    else
    {
      getcwd(cwd, sizeof(cwd));
      setenv("PWD", cwd, 1); // Set PWD environment variable to the current working directory
    }
  }
  return 1;
}

/* Help */
int my_help(char **args)
{
  if(output_file_found == 1) // case for standard output
  {
    /* Concatenate the name of the output file with the command string and then run it using a system call */
    char commandstring[MAX_BUFFER] = "cat readme.md > "; // Dont have to pipe it to more as its being written to a file
    char * returnoutput = strcat(commandstring,outputfile);
    system(returnoutput);
    return 1;
  }
  else
  {
    system("cat readme.md | more"); // Display the contents of the readme file, filtering it to more
    return 1;
  }

  return 1;
}

/* Clear */
int my_clr(char **args)
{
  system("clear");
  return 1; // return
}

/* dir */
int my_dir(char **args)  // Assumption: My understanding is users can pass dir and the folder and nothing else
{
  char buffer[256];
  if(output_file_found == 1) // case for standard output
  {
    /* Concatenate the name of the output file with the command string and then run it using a system call */
    char commandstring[MAX_BUFFER] = "ls -la > ";
    char * returnoutput = strcat(commandstring,outputfile);
    system(returnoutput);
    return 1;
  }
  else
  {
    if (args[1] == NULL)
    {
      system("ls -la"); // if no directory is given, list the contents of the current directory
    }
    else
    {
      /* list the contents of a given directory */
      snprintf(buffer, sizeof(buffer), "ls -la %s", args[1]);
      system(buffer); 
    }
  }
  return 1;
}

/* Environ */
int my_environ(char **args)
{
  if(output_file_found == 1) // case for standard output
  {
    /* Concatenate the name of the output file with the command string and then run it using a system call */
    char commandstring[MAX_BUFFER] = "env > ";
    char * returnoutput = strcat(commandstring,outputfile);
    system(returnoutput);
    return 1;
  }
  else
  {
    system("env"); // get environment variables
    return 1;
  }
  return 1;
}

/* Pause */
int my_pause(char **args)
{
  #define MAX 256
  char buf[MAX];
  fgets(buf, MAX, stdin); // wait for user input
  return 1;
}

/* Echo */
int my_echo(char **args)
{
  if(output_file_found == 1) // case for standard output
  {
    /* Concatenate the name of the output file with the command string and then run it using a system call */
    char commandstring[MAX_BUFFER] = "echo ";
    char * returnoutput1 = strcat(commandstring,args[1]);
    char * returnoutput2 = strcat(returnoutput1," >");
    char * returnoutput3 = strcat(returnoutput2,outputfile);
    system(returnoutput3);
    return 1;
  }
  else
  {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "echo %s", args[1]);
    system(buffer);
    return 1;
  }
  return 1;
}

/* Built in commands supported by this shell that the user can enter */
char *mycommands[] = {
  "cd",
  "help",
  "quit",
  "clr",
  "dir",
  "environ",
  "echo",
  "pause"
};

/* Functions corrosponding to each of the built in commands supported */
int (*commands_functions[]) (char **) = {
  &my_cd,
  &my_help,
  &my_clr,
  &my_dir,
  &my_environ,
  &my_echo,
  &my_pause
};

/* Execute */
int my_execute(char **args)
{
  int mysize = sizeof(mycommands) / sizeof(char *); // Get size of commands to use in for loop

  /* If the user doesnt give a command, do nothing */
  if (args[0] == NULL)
  {
    return 1;
  }

  /* If the user has entered a built in command, call the appropriate function */
  for (int i = 0; i < mysize; i++)
  {
    if (!strcmp(args[0], mycommands[i]))
    {
      return (*commands_functions[i])(args);
    }
  }

  return external_commands(args);
}

/* External commands */
int external_commands(char **args)
{
  pid_t pid; // process id variable of type pid_t
  int return_code; // initialize return code variable
  int count = 0; // initialize count variable

  for(int i = 1;args[i];i++)
  {
    count = count + 1; // create a count of arguments
  }

  /* forking and execing a child process */
  pid = fork();
  if (pid == 0)
  {
    /* Child process */
    if (!strcmp(args[count], "&"))
    {
      args[count] = NULL;
    }
    if (execvp(args[0], args) == -1)
    {
      printf("Error");
    }
    exit(0);
  }
  else if (pid < 0)
  {
    // If creation of child process is unsucessful, e.g. not enough memory
    printf("Error");
  }
  else
  {
    /* Parent Process */
    if (strcmp(args[count],"&"))
    {
      do
      {
        waitpid(pid, &return_code, WUNTRACED);
      } while (!WIFEXITED(return_code) && !WIFSIGNALED(return_code));
    }
  }

  return 1;
}
