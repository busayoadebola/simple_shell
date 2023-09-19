#include "shell.h"

/**
 * _strcmp- to compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 correct
 */

int _strcmp(char *s1, char *s2)
{
	int a = 0;

	while (s1[a] != '\0' && s2[a] != '\0')
	{
		if (s1[a] != s2[a])
		{
			return (s1[a] - s2[a]);
		}
		a++;
	}
	if (s1[a] == '\0' && s2[a] == '\0')
		return (0);
	return (s1[a] - s2[a]);
}

/**
 * _strdup - to make an array with a copy of a string
 * @str: the string to be copied
 *
 * Return: copy
 */

char *_strdup(char *str)
{
	char *copy = NULL;
	int c = 0;
	int r = 0;

	if (str == NULL)
		return (NULL);

	while (str[c] != '\0')
		c++;

	copy = malloc(sizeof(char) * (c + 1));
	if (copy == NULL)
		return (NULL);
	for (r = 0; str[r]; r++)
		copy[r] = str[r];
	copy[r] = '\0';
	return (copy);
}


/**
 * _getenv - gets the enviroment value
 * @str: the key to send its value
 *
 * Return: a string to the value of a key
 */

char *_getenv(char *str)
{
	int i, pos, len;

	i = pos = len = 0;
	len = _strlen(str);

	while (environ[i])
	{
		while (env_comp(environ[i], str, len) != true && environ[i])
		{
			i++;
		}
		if (environ[i] == NULL)
			return (NULL);
		pos = len + 2;
		return (_strdup(environ[i] + pos));
	}
	return (NULL);
}

/**
 * _strlen - finds the len of a string
 * @s: the string
 *
 * Return: length of a string
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

/**
 * *_strcpy - to copy a string in a dest to another
 * @dest: the destination to copy to
 * @src: the place to copy from
 *
 * Return: dest the pointer
 */

char *_strcpy(char *dest, char *src)
{
	int str_len = 0;
	int copy = 0;

	while (*(src + str_len) != '\0')
	{
		str_len++;
	}
	while (copy < str_len)
	{
		dest[copy] = src[copy];
		copy++;
	}
	dest[str_len] = '\0';
	return (dest);
}

