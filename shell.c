#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Trim spaces at start and end */
char *trim_spaces(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == '\0')
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Check if file exists and is executable */
int is_executable(char *path)
{
    struct stat st;
    return (stat(path, &st) == 0 && (st.st_mode & S_IXUSR));
}

/* Search command in PATH */
char *get_full_path(char *cmd)
{
    char *path_env = getenv("PATH");
    char *path_dup, *dir;
    char *full_path = malloc(1024);
    if (!path_env || !full_path)
        return NULL;

    if (strchr(cmd, '/')) /* Already a path */
    {
        if (is_executable(cmd))
            return strdup(cmd);
        free(full_path);
        return NULL;
    }

    path_dup = strdup(path_env);
    dir = strtok(path_dup, ":");
    while (dir)
    {
        snprintf(full_path, 1024, "%s/%s", dir, cmd);
        if (is_executable(full_path))
        {
            free(path_dup);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(path_dup);
    free(full_path);
    return NULL;
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[64];
    char *command;
    int i;
    pid_t pid;
    int status;
    char *full_path;
    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        command = trim_spaces(line);
        if (*command == '\0')
            continue;

        /* Split command into argv */
        i = 0;
        argv[i] = strtok(command, " \t");
        while (argv[i] && i < 63)
        {
            i++;
            argv[i] = strtok(NULL, " \t");
        }
        argv[i] = NULL;

        /* Get full path from PATH */
        full_path = get_full_path(argv[0]);
        if (!full_path)
        {
            fprintf(stderr, "%s: command not found\n", argv[0]);
            continue; /* skip fork */
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(full_path);
            continue;
        }

        if (pid == 0)
        {
            if (execve(full_path, argv, environ) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }

        free(full_path);
    }

    free(line);
    return 0;
}
