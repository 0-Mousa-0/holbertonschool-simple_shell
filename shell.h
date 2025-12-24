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

extern char **environ;

/* String utilities */
int _strlen(const char *s);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Shell utilities */
void print_prompt(void);
void handle_eof(char *input);
void remove_comments(char *input);
void strip_leading_trailing_spaces(char *str);
int is_whitespace(char c);

/* Environment */
char *_getenv(const char *name);

/* Path handling */
char *find_in_path(char *command);
int file_exists(char *path);
int is_absolute_path(char *command);

/* Parsing */
char **tokenize_input(char *input);
void cleanup_args(char **args);

/* Execution */
void execute_command(char **args);

#endif /* SHELL_H */
