#include "shell.h"

/**
 * tokenize_keywords - tokenize the keywords passed into the tty
 * @line: the text/keys to togcc -Wall -Werror -Wextra
 * -pedantic -std=gnu89 *.c -o hshkenize
 * @argc: number of tokens
 * Return: arrays of pointers to tokens
 */

char **tokenize_keywords(char *line, int *argc)
{
	char **argv = NULL, *token = NULL, *delim = " \n", *line_cpy = NULL;
	int i = 0;

	/* duplicate string and increment argc for memalloc */
	line_cpy = _strdup(line);
	token = _strtok(line_cpy, delim);
	if (token == NULL)
		return (NULL);
	while (token)
	{
		*argc += 1;
		token = _strtok(NULL, delim);
	}
	free_ptr(line_cpy);

	argv = malloc(sizeof(char *) * (*argc + 1));
	if (argv == NULL)
		return (NULL);
	i = 0;
	token = _strtok(line, delim);
	while (token)
	{
		argv[i++] = _strdup(token);
		token = _strtok(NULL, delim);
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * *check_absolute_path - to check if the path
 * is absolute
 * @command: the command to check
 * Return: NULL
 */

char *check_absolute_path(char *command)
{
	if (access(command, X_OK) == 0)
	{
		return (_strdup(command));
	}
	return (NULL);
}

/**
 * search_path - too search for the command path
 * @command: the command to search for
 * Return: the file opath
 */

char *search_path(char *command)
{
	char *path_env = NULL, *path = NULL, *full_path = NULL;
	size_t full_path_len = 0;

	bool path_type = (command[0] == '/');

	if (path_type)
		return (check_absolute_path(command));
	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path = _strtok(path_env, ":");
	while (path != NULL)
	{
		full_path_len = _strlen(path) + _strlen(command) + 2;
		full_path = malloc(sizeof(char) * full_path_len);
		if (full_path == NULL)
		{
			free(path_env);
			return (NULL);
		}
		_strcpy(full_path, path);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_env);
			return (full_path);
		}
		else
		{
			path = _strtok(NULL, ":");
			free(full_path);
		}
	}
	free(path_env);
	return (NULL);
}

/**
 * find_path - to find the fie path
 * @command: the command path to find
 * Return: path
 */

char *find_path(char *command)
{
	char *path = NULL;

	path = check_absolute_path(command);
	if (path != NULL)
	{
		return (path);
	}
	return (search_path(command));
}

