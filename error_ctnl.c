#include "shell.h"

/**
 * print_error - detects and prints type of error
 * @error: Error
 *
 * Return: void.
 */

void print_error(int error)
{
	switch (error)
	{
		case EINVAL:
			write(STDERR_FILENO,
					"Bad arguments\n", 14);
			break;
		case ENOMEM:
			write(STDERR_FILENO,
					"Memory Issue\n", 13);
			break;
		case EAGAIN:
			write(STDERR_FILENO,
					"System imposed limit on number of threads\n", 42);
			break;
		default:
			write(STDERR_FILENO,
					"Error encountered\n", 18);
			break;
	}
}

/**
 * print_function_error - function had a problem
 *
 * Return: void
 */

void print_function_error(void)
{
	write(STDERR_FILENO,
			"Couldn't parse the required datatype\n", 37);
}

/**
 * print_exec_err - prints when execve encounters error
 * @av: shell interpreter
 * @cnt: num of cmd so far
 * @s: command not found
 *
 * Return: void
 */

void print_exec_err(char **av, int cnt, char *s)
{
	int i, j;

	i = j = 0;
	if (!s)
		return;
	for (i = 0; av[0][i]; i++)
		_putchar(av[0][i]);
	_putchar(':');
	_putchar(' ');
	dprintf(STDERR_FILENO, "%d", cnt);
	_putchar(':');
	_putchar(' ');
	for (j = 0; s[j]; j++)
		_putchar(s[j]);
	write(STDOUT_FILENO, ": not found\n", 12);
}

/**
 * print_int - prints an integer
 * @n: the int value
 *
 * Return: void
 */
int print_int(int n)
{
	if (n < 0)
	{
		_putchar('-');
		n = (n * -1);
	}

	while (n / 10)
	{
		print_int(n / 10);
	}
	return (1 + _putchar((n % 10) + '0'));
	
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
