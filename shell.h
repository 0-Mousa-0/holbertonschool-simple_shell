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

void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args, char *prog_name);
void free_args(char **args);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int has_slash(char *command);
char *find_in_path(char *command);

#endif
