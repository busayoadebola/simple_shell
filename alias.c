#include "shell.h"

static Alias aliases[MAX_ALIASES];
static int alias_count;
/**
 * cleanup_aliases - to clean up alias
 */

void cleanup_aliases(void)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		free(aliases[i].name);
		free(aliases[i].value);
	}
}

/**
 * display_aliases - Function to display aliases
 */

void display_aliases(void)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * add_or_modify_alias - Function to add or modify aliases
 * @name: the name of the alias
 * @value: the valoue of the alias
 * Return: void
 */

void add_or_modify_alias(char *name, char *value)
{
	int i, found = 0;

	for (i = 0; i < alias_count; i++)
	{
		if (_strcmp(aliases[i].name, name) == 0)
		{
			found = 1;
			free(aliases[i].value);
			aliases[i].value = _strdup(value);
			break;
		}
	}
	if (!found && alias_count < MAX_ALIASES)
	{
		aliases[alias_count].name = _strdup(name);
		aliases[alias_count].value = _strdup(value);
		alias_count++;
	}
}

/**
 * alias_builtin - the builtin function
 * @line: accepts string
 * @args: the arg vector
 * @cnt: the num of args passed
 * @av: the args passed to program
 * Return: void
 */

void alias_builtin(UNUSED char *line, char **args,
		UNUSED int cnt, UNUSED char **av)
{
	int i;

	if (args[1] == NULL)
	{
		display_aliases();
	}
	else if (args[1] && args[2] == NULL)
	{
		for (i = 0; i < alias_count; i++)
		{
			if (strcmp(aliases[i].name, args[1]) == 0)
			{
				printf("%s='%s'\n", aliases[i].name, aliases[i].value);
				return;
			}
		}
	}
	else if (args[1] && args[2])
	{
		for (i = 1; args[i] != NULL; i++)
		{
			char *name = args[i];
			char *equals_pos = _strchr(name, '=');

			if (equals_pos != NULL)
			{
				char *value;

				*equals_pos = '\0';
				value = equals_pos + 1;
				add_or_modify_alias(name, value);
			}
		}
	}
	else
	{
		printf("I'm here\n");
	}
}
