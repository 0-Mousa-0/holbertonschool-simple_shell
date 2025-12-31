#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args, char *prog_name);
void free_args(char **args);
int is_builtin(char *command);
int _strcmp(char *s1, char *s2);

#endif
