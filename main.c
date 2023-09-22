#include "shell.h"


/**
 * processFromFile - Function to process input from a file
 * @filename: the file name
 * @av: the argument therein
 * Return: void
 */

void processFromFile(char *filename, char **av)
{
	int cmd_cnt = 0;
	char *line = NULL;
	size_t n = 0;
	char *command;

	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: Can't open %s\n", av[0], cmd_cnt, filename);
		exit(127);
	}
	while ((getline(&line, &n, file)) != -1)
	{
		command = _strtok(line, "#");
		get_keywords(av, &cmd_cnt, command);
	}
	fclose(file);
	free(line);
}


/**
 * processInput - Function to process input from
 * the command line or standard input
 * @av: the arguments
 * Return: void
 */

void processInput(char **av)
{
	int cmd_cnt = 0;
	char *line = NULL;
	size_t n = 0;
	ssize_t glread = 0;
	char *command;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "($) ", sizeof("($) "));
		}
		glread = getline(&line, &n, stdin);
		if (glread == -1)
		{
			break;
		}
		command = _strtok(line, "#");
		get_keywords(av, &cmd_cnt, command);
	}
	free(line);
}

/**
 * main - the main function
 * @ac: the argument count
 * @av: the array of arguments
 * Return: 0
 */

int main(int ac, char **av)
{
	if (ac == 2)
	{
		processFromFile(av[1], av);
	}
	else
	{
		processInput(av);
	}
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
