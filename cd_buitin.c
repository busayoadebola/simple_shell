#include "shell.h"

void cd_builtin(UNUSED char *line, char **args,
	       UNUSED int cnt, UNUSED char **av)
{
    char new_dir[MAX_DIR_LEN];
    char *home_dir = _getenv("HOME");
    char *old_dir = _getenv("PWD");

    if (!args[1] || _strcmp(args[1], "~") == 0 ||
		    _strcmp(args[1], "$HOME") == 0)
    {
	    if (home_dir)
	    {
		    _strcpy(new_dir, "/");
		    _strcat(new_dir, home_dir);
	    }
	    else
	    {
		    write(STDERR_FILENO, "cd: HOME environment variable not set\n", 37);
		    return;
	    }
    }
    else if (_strcmp(args[1], "-") == 0)
    {
	    if (old_dir)
	    {
		    _strcpy(new_dir, "/");
		    _strcat(new_dir, old_dir);
	    }
	    else
	    {
		    write(STDERR_FILENO, "cd: PWD environment variable not set\n", 36);
		    return;
	    }
    }
    else
    {
	    _strcpy(new_dir, args[1]);
    }
    
    if (chdir(new_dir) == 0)
    {
	    char cwd[MAX_DIR_LEN];
	    
	    if (getcwd(cwd, sizeof(cwd)) != NULL)
	    {
		    _setenv("PWD", cwd, 1);
	    }
	    else
	    {
		    write(STDERR_FILENO, "cd: Unable to update PWD environment variable\n", 46);
	    }
    }
    else
    {
	    perror("cd");
    }
    free_ptr(old_dir);
    free_ptr(home_dir);
}
