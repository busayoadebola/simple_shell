#include "shell.h"


Alias aliases[MAX_ALIASES];
int alias_count = 0;

void cleanup_aliases()
{
	int i;
	int alias_count = 0;

	for (i = 0; i < alias_count; i++)
	{
		free(aliases[i].name);
		free(aliases[i].value);
	}
}

void alias_builtin(UNUSED char *line, char **args,
		UNUSED int cnt, UNUSED char **av)
{
	int i, found, j;
	char *name, *equals_pos, *value;

	if (args[1] == NULL)
	{
		for (i = 0; i < alias_count; i++)
		{
			printf("%s='%s'\n", aliases[i].name, aliases[i].value);
		}
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
			name = args[i];
			equals_pos = strchr(name, '=');
			if (equals_pos != NULL)
			{
				equals_pos = '\0';
				value = equals_pos + 1;
				found = 0;
				for (j = 0; j < alias_count; j++)
				{
					if (strcmp(aliases[j].name, name) == 0)
					{
						found = 1;
						free(aliases[j].value);
						aliases[j].value = strdup(value);
						return;
					}
				}
				if (!found && alias_count < MAX_ALIASES)
				{
					aliases[alias_count].name = strdup(name);
					aliases[alias_count].value = strdup(value);
					alias_count++;
				}
			}
		}
	}
	else
	{
		printf("I'm here\n");
	}
}

