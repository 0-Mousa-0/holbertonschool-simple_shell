#include "shell.h"

/**
 * handle_command_error - Handles command not found errors
 * @command: Command that wasn't found
 */
static void handle_command_error(char *command)
{
    struct stat st;
    
    if (is_absolute_path(command))
    {
        if (stat(command, &st) == -1)
        {
            write(STDERR_FILENO, command, _strlen(command));
            write(STDERR_FILENO, ": No such file or directory\n", 28);
        }
        else if (access(command, X_OK) == -1)
        {
            write(STDERR_FILENO, command, _strlen(command));
            write(STDERR_FILENO, ": Permission denied\n", 20);
        }
    }
    else
    {
        write(STDERR_FILENO, command, _strlen(command));
        write(STDERR_FILENO, ": command not found\n", 20);
    }
}

/**
 * execute_command - Executes a command with arguments
 * @args: Array of arguments (args[0] is the command)
 */
void execute_command(char **args)
{
    char *command_path;
    pid_t pid;
    int status;
    
    if (args == NULL || args[0] == NULL)
        return;
    
    command_path = find_in_path(args[0]);
    if (command_path == NULL)
    {
        handle_command_error(args[0]);
        return;
    }
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(command_path);
        return;
    }
    
    if (pid == 0)
    {
        execve(command_path, args, environ);
        perror(args[0]);
        free(command_path);
        exit(EXIT_FAILURE);
    }
    
    waitpid(pid, &status, 0);
    free(command_path);
}
