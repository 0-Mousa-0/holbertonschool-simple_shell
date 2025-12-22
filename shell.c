#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

char *trim_spaces(char *str)
{
char *end;
while (*str == ' ' || *str == '\t')
str++;
if (*str == 0)
return str;
end = str + strlen(str) - 1;
while (end > str && (*end == ' ' || *end == '\t'))
end--;
*(end + 1) = '\0';
return str;
}

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
pid_t pid;
int status;
char *argv[2];
char *command;
char *first_word;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "#cisfun$ ", 9);

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

first_word = strtok(command, " \t");
if (!first_word)
continue;

pid = fork();
if (pid == -1)
{
perror("fork");
continue;
}

if (pid == 0)
{
argv[0] = first_word;
argv[1] = NULL;
if (execve(argv[0], argv, environ) == -1)
{
fprintf(stderr, "%s: No such file or directory\n", argv[0]);
exit(1);
}
}
else
wait(&status);
}

free(line);
return 0;
}
