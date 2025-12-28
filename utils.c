#include "shell.h"

/**
 * display_prompt - Display shell prompt
 */
void display_prompt(void)
{
    printf("$ ");
    fflush(stdout);
}

/**
 * read_input - Read input from stdin
 * Return: Input string or NULL on EOF
 */
char *read_input(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    
    nread = getline(&line, &bufsize, stdin);
    if (nread == -1)
    {
        free(line);
        return (NULL);
    }
    
    if (nread > 0 && line[nread - 1] == '\n')
        line[nread - 1] = '\0';
    
    return (line);
}

/**
 * free_args - Free arguments array
 * @args: Array to free
 */
void free_args(char **args)
{
    int i;
    
    if (!args)
        return;
    
    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    
    free(args);
}

/**
 * print_error - Print error message in required format
 * @program: Program name
 * @command: Command that failed
 */
void print_error(char *program, char *command)
{
    fprintf(stderr, "%s: 1: %s: not found\n", program, command);
}

/**
 * change_dir - Change directory built-in
 * @args: Arguments
 * Return: 1
 */
int change_dir(char **args)
{
    char *dir = args[1];
    char cwd[PATH_MAX];
    char *home;
    
    if (dir == NULL)
    {
        home = _getenv("HOME");
        if (home)
            dir = home;
        else
            dir = "/";
    }
    
    if (chdir(dir) != 0)
    {
        fprintf(stderr, "cd: can't cd to %s\n", dir);
        return (1);
    }
    
    /* Get and optionally print new directory */
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        /* In simple shell, we don't update PWD env variable */
        return (1);
    }
    
    return (1);
}
