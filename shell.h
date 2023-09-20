#ifndef SHELL_H
#define SHELL_H

/* Feature Test Macro Requirement for glibc getline() */
#define _GNU_SOURCE
#define UNUSED __attribute__((unused))

#define INITIAL_BUFFER_SIZE 420
#define MAX_DIR_LEN 1024
#define MAX_ALIASES 100

/* Necessary header file */
#include <stdio.h> /* i/o functionality */
#include <errno.h> /* error type-check */
#include <unistd.h> /* unix standard */
#include <string.h> /* string manipulation header file */
#include <sys/types.h> /* definition of integer constants */
#include <sys/wait.h> /* to implement the wait() */
#include <stdlib.h> /* stadard library */
#include <stdbool.h> /* to use for boolean datatypes */
#include <sys/stat.h> /* get file status */

extern char **environ;
/* DATA STRUCT */

/* builtins */

/**
 * struct builtin - stores builtins
 * @s: the command
 * @f: function pointer to builtin exec
 *
 * Description: builtin commands
 */

typedef struct builtin
{
	char *s;
	void (*f)(char *, char **, int, char **);
} built_in;


/**
 * struct alias - structure to hold an alias
 * @name: the name of alias
 * @value: the value of alias
 *
 * Description: structure holds alias
 */

typedef struct alias
{
	char *name;
	char *value;
} Alias;


/* FUNCTION PROTOTYPES  */

/* keyword functions */
void get_keywords(char **, int *, char *);
void child_process_execute(char **, int *, char **);
char **tokenize_keywords(char *, int *);
char *find_path(char *command);


/* error functions */
void print_error(int);
void print_function_error(void);
void print_exec_err(char **, int, char *);
int _perror(char);
int print_interr(int);
int print_int(int);


/* Freeing functions */
void free_ptr(char *);
void free_ptr_db(char **);
void cleanup_aliases(void);

/* utility functions */
int _strcmp(char *, char *);
char *_strdup(char *);
int _strlen(char *);
char *_getenv(char *);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
int _putchar(char c);
bool env_comp(char *, char *, int);
int _putenv(char *);
char *_strchr(char *, int);
/* char *run_pwd(char *); */

/* builtins */
int builtin_cmd(char *, char *, char **, int, char **);
void builtin_exit(char *, char **, int, char **);
void builtin_env(char *, char **, int, char **);
void cd_builtin(char *, char **, int, char **);
int _setenv(char *, char *, int);
void setenv_builtin(char *, char **, int, char **);
int _unsetenv(char *);
void unsetenv_builtin(char *, char **, int, char **);
void alias_builtin(char *, char **, int, char **);



int _atoi(char *);
/* char *_strtok(char *, char *); */
ssize_t _getline(char **, size_t *, int);


#endif /* SHELL Header File */

