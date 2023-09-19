#include "shell.h"

/**
 * _unsetenv - unsets an env
 * @name: the key to unset
 *
 * Return: int
 */


int _unsetenv(char* name)
{
	size_t env_count;
	char **environ_ptr = environ;
	char **new_environ;
	int new_idx = 0;

	if (name == NULL || strchr(name, '=') != NULL)
	{
		return -1;
	}

	while (*environ_ptr != NULL)
	{
		env_count++;
		environ_ptr++;
	}
	
	new_environ = malloc(sizeof(char*) * (env_count + 1));
	if (new_environ == NULL)
	{
		return (-1);
	}

	environ_ptr = environ;
	while (*environ_ptr != NULL)
	{
		char* entry_name = *environ_ptr;
		char* equals_pos = strchr(entry_name, '=');
		
		if (equals_pos != NULL)
		{
			size_t entry_len = equals_pos - entry_name;
			
			if (strncmp(entry_name, name, entry_len) != 0)
			{
				new_environ[new_idx] = *environ_ptr;
				new_idx++;
			}
		}
		environ_ptr++;
	}
	new_environ[new_idx] = NULL;
	environ = new_environ;
	free_ptr_db(new_environ);
	return (0);
}

/**
 * unsetenv_builtin - unsets an env
 * @line: accepts string
 * @argv: the arg vector
 * @cnt: the num of args passed
 * @av: the args passed to program
 *
 *
 * Return: void
 */

void unsetenv_builtin(UNUSED char *line, char **args,
		int cnt, char **av)
{
	char c = cnt + '0';

	if (args[1])
	{
		if (_unsetenv(args[1]) == -1)
		{
			char error_msg[] = "unsetenv: Failed to unset ";

			write(STDERR_FILENO, error_msg,
					strlen(error_msg));
			write(STDERR_FILENO, args[1], strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
		}
	}
	else
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": ", _strlen(": "));
		write(STDERR_FILENO, &c, 1);
		write(STDERR_FILENO, ": ", _strlen(": "));
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, ": not found\n ", 12);
	}
}
