#include "shell.h"

/**
 * *_strcat - to concatenate two strings
 * @dest: where to concatenate to
 * @src: where to concatenate from
 *
 * Return: dest the concatenated value
 */

char *_strcat(char *dest, char *src)
{
	int len = 0;
	int j = 0;

	while (dest[len] != '\0')
	{
		len++;
	}
	while (src[j] != '\0')
	{
		dest[len] = src[j];
		j++;
		len++;
	}
	dest[len] = '\0';
	return (dest);
}

/**
 * env_comp - compares the environment key
 * @k1: key 1
 * @k2: key 2
 * @byte: the bytes to check
 *
 * Return: bool true if equal
 */

bool env_comp(char *k1, char *k2, int byte)
{
	int i;

	for (i = 0; i < byte; i++)
	{
		if (k1[i] != k2[i])
			return (false);
	}
	return (true);
}


/**
 * builtin_cmd - check and execute builtin cmds
 * @str: the command to search for
 * @line: stored token
 * @argv: db ptr
 * @cnt: number of args passed so far
 * @av: args passed to main
 *
 * Return: int
 */

int builtin_cmd(char *str, char *line, char **argv, int cnt, char **av)
{
	int i;
	built_in cmd_check[] = {
		{"exit", builtin_exit}, /* void (*f)(void) */
		{"env", builtin_env},
		{"cd", cd_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{"alias", alias_builtin},
		{NULL, NULL}
	};

	i = 0;
	while (cmd_check[i].s)
	{
		if (!_strcmp(cmd_check[i].s, str))
		{
			cmd_check[i].f(line, argv, cnt, av);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * _atoi - converts a string num to int
 * @s: the string containing num
 *
 * Return: int
 */

int _atoi(char *s)
{
	int i, value = 0;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (2);
		value = (value * 10) + (s[i] - '0');
		i++;
	}
	if (s[0] == '-')
		value = (value * -1);
	return (value);
}

