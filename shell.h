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

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);

/* Built-in functions */
int handle_builtin(char **args);
int exit_shell(char **args);
int print_env(char **args);
int change_dir(char **args);
int print_help(char **args);

/* Path handling */
char *find_executable(char *command);
char *find_in_path(char *command);

/* Utility functions */
void free_args(char **args);
void print_error(char *program, char *command);
int is_builtin(char *command);

/* String functions */
int _strlen(const char *s);
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(const char *name);

/* Helper functions */
int is_path_command(const char *command);
char *build_full_path(const char *dir, const char *command);

#endif
