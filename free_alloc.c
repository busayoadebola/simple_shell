#include "shell.h"

/**
 * free_ptr - frees a single pointer
 * @ptr: ptr to free
 *
 * Return: void
 */

void free_ptr(char *ptr)
{
	free(ptr);
}

/**
 * free_ptr_db - freeing a double pointer
 * @ptr: ptr to free
 * @pos: where to free from
 *
 * Return: void.
 */

void free_ptr_db(char **ptr)
{
	int i;

	for (i = 0; ptr[i]; i++)
		free(ptr[i]);
	free(ptr);
}
