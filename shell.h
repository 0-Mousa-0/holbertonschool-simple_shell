#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/* parser */
char **parse_line(char *line);
int is_empty_line(char *line);

/* path */
char *resolve_command(char *cmd);

/* execute */
void execute_command(char **argv);

#endif
