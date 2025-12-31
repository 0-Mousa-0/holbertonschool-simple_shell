#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Main functions */
void shell_loop(void);
char **tokenize(char *line);
int execute(char **args, char *path);
char *find_path(char *command);

/* Utility functions */
char *_getenv(const char *name);
int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

#endif
