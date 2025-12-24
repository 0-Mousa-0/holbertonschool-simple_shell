#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Environment variable functions */
extern char **environ;
char *_getenv(const char *name);

/* String utility functions */
int _strlen(const char *s);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Path handling functions (path.c) */
char *find_in_path(char *command);
char *build_full_path(char *dir, char *command);
int file_exists(char *path);

/* Parser functions (parser.c) */
char **tokenize_input(char *input);
void cleanup_args(char **args);

/* Execution functions (execute.c) */
void execute_command(char **args);

/* Shell main functions */
void print_prompt(void);
void handle_eof(char *input);

#endif /* SHELL_H */
