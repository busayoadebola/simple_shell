#include "shell.h"

Alias aliases[MAX_ALIASES];
int alias_count = 0;

typedef void (*AliasFunction)(char **);

/**
 * cleanup_aliases - cleanup
 *
 */

void cleanup_aliases()
{
	int i;
	for (i = 0; i < alias_count; i++)
	{
		free(aliases[i].name);
		free(aliases[i].value);
	}
}

/**
 * list_aliases - to list the alias
 * @args: argument passed
 *
 */
void list_aliases(UNUSED char **args)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * update_alias - to update the list of alias
 * @args: the argument passed
 *
 */

void update_alias(char **args)
{
	int i, found = 0;
	char *name = args[1];
	char *value = args[2];

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			free(aliases[i].value);
			aliases[i].value = strdup(value);
			found = 1;
			break;
		}
	}
	if (!found)
	{
		if (alias_count < MAX_ALIASES)
		{
			aliases[alias_count].name = strdup(name);
			aliases[alias_count].value = strdup(value);
			alias_count++;
		}
		else
		{
			printf("Alias limit reached. Cannot add more aliases.\n");
		}
	}
}

/**
 * alias_builtin - the main function
 * @args: argument passed
 *
 * Return: void
 */
void alias_builtin(UNUSED char *line, char **args,
		UNUSED int cnt, UNUSED char **av)
{
	if (args[1] == NULL)
	{
		list_aliases(args);
	}
	else if (args[2] == NULL)
	{
		int i;

		for (i = 0; i < alias_count; i++)
		{
			if (strcmp(aliases[i].name, args[1]) == 0)
			{
				printf("%s='%s'\n", aliases[i].name, aliases[i].value);
				return;
			}
		}
	}
	else
	{
		update_alias(args);
	}
}

