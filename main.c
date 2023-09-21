#include "shell.h"

/**
 * main - a shell replica
 * @ac: number of args passed
 * @av: the args passed
 * Return: 0.
 */

int main(int ac, char **av)
{
	int cmd_cnt = 0;
	char *line = NULL;
	size_t n = 0;
	ssize_t glread = 0;
	char *command;

	if (ac == 2)
	{
		FILE *file = fopen(av[1], "r");
		if (file == NULL)
		{
			dprintf(STDERR_FILENO,
					"%s: %d: Can't open %s\n",
					av[0], cmd_cnt, av[1]);
			exit(127);
		}

		while ((getline(&line, &n, file)) != -1)
		{
			command = _strtok(line, "#");
			get_keywords(av, &cmd_cnt, command);
		}
		fclose(file);
	}
	else if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			write(STDOUT_FILENO, "($) ", sizeof("($) "));
			glread = _getline(&line, &n, STDIN_FILENO);
			if (glread == -1)
				return (-1);

			command = _strtok(line, "#");
			get_keywords(av, &cmd_cnt, command);
		}
	}
	else
	{
		while (_getline(&line, &n, STDIN_FILENO) != -1)
		{
			command = _strtok(line, "#");
			get_keywords(av, &cmd_cnt, command);
		}
	}
	free(line);
	cleanup_aliases();
	return (0);
}

/**
 * get_keywords - gets the keywords from terminal using getline
 * @av: the args passed in CLI
 * @cnt: number of cmd typed
 * @line: the command passed through getline
 *
 * Return: void
 */

void get_keywords(char **av, int *cnt, char *line)
{
	char **argv = NULL;
	int argc = 0;


	/* tokenize the keywords */
	argv = tokenize_keywords(line, &argc);
	*cnt += 1;
	if (argv == NULL)
		return;
	/* builtin */
	if (builtin_cmd(argv[0], line, argv, *cnt, av) == 1)
	{
		free_ptr_db(argv);
		return;
	}
	/* call the function for child process */
	child_process_execute(av, cnt, argv);
	free_ptr_db(argv);
}

/**
 * child_process_execute - to call a child process
 * @av: arguments passed
 * @cnt: no of commands typed
 * @argv: array of argumnt
 * Return: void
 */

void child_process_execute(char **av, int *cnt, char **argv)
{
	char *exec_path = NULL;
	pid_t child_process = 0;
	struct stat statbuf;

	if (!argv[0])
		return;
	exec_path = find_path(argv[0]);
	if (exec_path != NULL && access(exec_path, X_OK) == 0 &&
			stat(exec_path, &statbuf) == 0)
	{
		child_process = fork();
		if (child_process == -1)
		{
			perror("fork:");
			return;
		}
		if (child_process == 0)
		{
			execve(exec_path, argv, NULL);
			print_exec_err(av, *cnt, argv[0]);
			exit(98);
		}
		else
			wait(NULL);
	}
	else
	{
		print_exec_err(av, *cnt, argv[0]);
		return;
	}
	free_ptr(exec_path);
}

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
	token = strtok(line_cpy, delim);
	if (token == NULL)
		return (NULL);
	while (token)
	{
		*argc += 1;
		token = strtok(NULL, delim);
	}
	free_ptr(line_cpy);

	argv = malloc(sizeof(char *) * (*argc + 1));
	if (argv == NULL)
		return (NULL);
	i = 0;
	token = strtok(line, delim);
	while (token)
	{
		argv[i++] = _strdup(token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * find_path - takes command name as argument & search for full path
 * @command: the command name opassed as an arguement
 *
 * Return: full path if found, otherwise return NULL
 */

char *find_path(char *command)
{
	char *path_env = NULL, *path = NULL, *full_path = NULL;
	size_t full_path_len = 0;
	bool path_type = false;

	if (command[0] == '.')
	{
		if (access(command, X_OK) == 0)
		{
			full_path = _strdup(command);
			return (full_path);
		}
	}
	path_type = (command[0] == '/');
	if (path_type && access(command, X_OK) == 0)
	{
		return (_strdup(command)); /* Return an absolute path */
	}
	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path = strtok(path_env, ":");
	while (path != NULL)
	{
		full_path_len = _strlen(path) + _strlen(command) + 2;
		full_path = malloc(sizeof(char) * full_path_len);
		if (full_path == NULL)
		{
			free_ptr(path_env);
			return (NULL); /*Memory allocation error*/
		}
		_strcpy(full_path, path);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		else
		{
			path = strtok(NULL, ":");
			free_ptr(full_path);
		}
	}
	free_ptr(path_env);
	return (NULL); /* Command not found*/
}

