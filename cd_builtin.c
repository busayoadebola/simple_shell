#include "shell.h"

/**
 * change_directory - Function to change the
 * current working directory
 * @new_dir: the new directory
 * Return: the result
 */

int change_directory(char *new_dir)
{
	if (chdir(new_dir) == 0)
	{
		char cwd[MAX_DIR_LEN];

		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			_setenv("PWD", cwd, 1);
			return (0); /* Success */
		}
		else
		{
			fprintf(stderr, "cd: Unable to update PWD environment variable\n");
			return (1); /* Error updating PWD */
		}
	}
	else
	{
		perror("cd");
		return (2); /* Error changing directory */
	}
}

/**
 * cd_builtin - Function to handle the cd_builtin logic
 * setenv_builtin - sets an env
 * @line: accepts string
 * @args: arg vecto
 * @cnt: num of args passed
 * @av: args passed to program
 * Return: void
 */

void cd_builtin(UNUSED char *line, char **args,
		UNUSED int cnt, UNUSED char **av)
{
	char new_dir[MAX_DIR_LEN], *home_dir = getenv("HOME");
	char *old_dir = getenv("PWD");
	int result;

	if (!args[1] || strcmp(args[1], "~") == 0 ||
			strcmp(args[1], "$HOME") == 0)
	{
		if (home_dir)
		{
			_strcpy(new_dir, "/");
			_strcat(new_dir, home_dir);
		}
		else
		{
			fprintf(stderr, "cd: HOME environment variable not set\n");
			return;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (old_dir)
		{
			_strcpy(new_dir, "/");
			_strcat(new_dir, old_dir);
		}
		else
		{
			fprintf(stderr, "cd: PWD environment variable not set\n");
			return;
		}
	}
	else
	{
		_strcpy(new_dir, args[1]);
	}
	result = change_directory(new_dir);
	free(home_dir);
	free(old_dir);
	if (result == 0)
		printf("Changed directory to %s\n", new_dir);
}

/**
 * _putchar - prints a char
 * @c: the char
 *
 * Return: values printed
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}


/**
 * _perror - prints to stderr
 * @c: the char
 *
 * Return: values printed
 */

int _perror(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * print_interr - prints an integer
 * @n: the int value
 *
 * Return: void
 */
int print_interr(int n)
{
	if (n < 0)
	{
		_perror('-');
		n = (n * -1);
	}

	while (n / 10)
	{
		print_interr(n / 10);
	}
	return (1 + _perror((n % 10) + '0'));
}
