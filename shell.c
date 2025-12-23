#include "shell.h"

/* Remove leading and trailing spaces/tabs */
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

/* Fork and execute a command */
void execute_command(char **argv)
{
    pid_t pid;
    int status;

    char *full_path = get_full_path(argv[0]);
    if (!full_path)
    {
        fprintf(stderr, "%s: command not found\n", argv[0]);
        return; /* skip fork */
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(full_path);
        return;
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
