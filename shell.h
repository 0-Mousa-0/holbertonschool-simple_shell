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

/* Global environment */
extern char **environ;

/* Function prototypes */

/* Main shell functions */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);

/* Built-in functions */
int handle_builtin(char **args);
int exit_shell(char **args);
int print_env(char **args);
int change_dir(char **args);

/* Path handling functions */
char *find_in_path(char *command);
int check_command_exists(char *command);

/* Utility functions */
void free_args(char **args);
void print_error(char *program, char *command);
int is_builtin(char *command);

/* Custom string functions */
int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

#endif
