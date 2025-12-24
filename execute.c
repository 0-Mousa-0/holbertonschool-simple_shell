#include "shell.h"

/**
 * execute_command - Executes a command with arguments
 * @args: Array of arguments (args[0] is the command)
 *
 * Description: Finds the command in PATH, checks if it exists,
 * and only then forks to execute it.
 */
void execute_command(char **args)
{
    char *command_path;
    pid_t pid;
    int status;
    
    if (args == NULL || args[0] == NULL)
        return;
    
    /* Check if command exists before forking */
    command_path = find_in_path(args[0]);
    if (command_path == NULL)
    {
        write(STDERR_FILENO, args[0], _strlen(args[0]));
        write(STDERR_FILENO, ": command not found\n", 20);
        return;
    }
    
    /* Fork and execute */
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(command_path);
        return;
    }
    else if (pid == 0) /* Child process */
    {
        if (execve(command_path, args, environ) == -1)
        {
            perror(args[0]);
            free(command_path);
            exit(EXIT_FAILURE);
        }
    }
    else /* Parent process */
    {
        waitpid(pid, &status, 0);
        free(command_path);
    }
}
