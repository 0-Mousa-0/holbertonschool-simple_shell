#include "shell.h"

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;
    char *full_path;
    
    if (args[0] == NULL)
        return (1);
    
    /* Handle built-in commands */
    if (is_builtin(args[0]))
        return (handle_builtin(args));
    
    /* Find command in PATH before forking */
    full_path = find_in_path(args[0]);
    if (full_path == NULL)
    {
        print_error("hsh", args[0]);
        return (1);
    }
    
    /* Command exists, now fork */
    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(full_path, args, environ) == -1)
        {
            perror("hsh");
            free(full_path);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("hsh");
        free(full_path);
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
        free(full_path);
    }
    
    return (1);
}

/**
 * handle_builtin - Handle built-in commands
 * @args: Array of arguments
 * Return: 1 to continue, 0 to exit
 */
int handle_builtin(char **args)
{
    if (_strcmp(args[0], "exit") == 0)
        return (exit_shell(args));
    else if (_strcmp(args[0], "env") == 0)
        return (print_env(args));
    else if (_strcmp(args[0], "cd") == 0)
        return (change_dir(args));
    
    return (1);
}

/**
 * exit_shell - Exit the shell
 * @args: Arguments
 * Return: 0 to exit
 */
int exit_shell(char **args)
{
    (void)args;
    return (0);
}

/**
 * print_env - Print environment variables
 * @args: Arguments
 * Return: 1
 */
int print_env(char **args)
{
    char **env = environ;
    
    (void)args;
    
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
    
    return (1);
}
