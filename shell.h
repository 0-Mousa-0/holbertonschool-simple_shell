#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);
char *find_command(char *command);
void free_args(char **args);
int is_builtin(char *command);
int handle_builtin(char **args);
void print_error(char *command);

/* Built-in commands */
int shell_exit(char **args);
int shell_env(char **args);

/* Environment */
extern char **environ;

#endif
