#include "shell.h"

/**
 * _strchr - checks for the pos of occur of char
 * @str: the str
 * @ch: the char to check for
 *
 * Return: char *
 */

char *_strchr(char* str, int ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return ((char*)str);
		}
		str++;
	}
	if (ch == '\0')
	{
		return ((char*)str);
	}
	return (NULL);
}

/**
 * _putenv - stores an env
 * @str: the value
 *
 * Return: int
 */

int _putenv(char* str)
{
	char *name, *existing;

	if (str == NULL || _strchr(str, '=') == NULL)
	{
		return -1;
	}
	
	name = str;
	while (*name != '=' && *name != '\0')
	{
		name++;
	}
	if (*name == '=')
	{
		*name = '\0';
		name++;
		existing = _getenv(str);
		if (existing != NULL)
		{
			_strcpy(existing, name);
			return (0);
		}
	}
    return (-1);
}

