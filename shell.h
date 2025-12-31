#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

/* Main shell functions */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args, char *prog_name);

/* Built-in functions */
int handle_builtin(char **args);
int exit_shell(char **args);

/* Path handling */
char *find_executable(char *command);

/* Utility functions */
void free_args(char **args);
void print_error(char *program, char *command);
int is_builtin(char *command);

/* String functions */
int _strlen(const char *s);
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);

#endif
