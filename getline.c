#include "shell.h"

/**
 * read_into_buffer - Function to read data into a buffer
 * @buffer: storage of read line
 * @buffer_size: the number of chars read
 * @fd: the descriptor
 *
 * Return: ssize_t
 */
ssize_t read_into_buffer(char **buffer, size_t *buffer_size, int fd)
{
	ssize_t bytes_read;

	if (buffer == NULL || buffer_size == NULL)
	{
		return (-1);
	}
	if (*buffer == NULL || *buffer_size == 0)
	{
		*buffer_size = INITIAL_BUFFER_SIZE;
		*buffer = (char *)malloc(sizeof(char) * *buffer_size);
		if (*buffer == NULL)
		{
			return (-1);
		}
	}
	bytes_read = read(fd, *buffer, *buffer_size);

	if (bytes_read < 0)
	{
		return (-1);
	}
	return (bytes_read);
}

/**
 * extract_line - Function to extract lines from the buffer
 * @lineptr: storage of read line
 * @n: the number of chars read
 * @buffer: the descriptor
 * @buffer_position: the position
 * @bytes_in_buffer: the buffer bytes
 *
 * Return: ssize_t
 */
ssize_t extract_line(char **lineptr, size_t *n, char *buffer,
		size_t *buffer_position, size_t bytes_in_buffer)
{
	ssize_t chars_read = 0;
	size_t line_length = 0;
	int found_newline = 0;

	while (*buffer_position < bytes_in_buffer)
	{
		if (buffer[*buffer_position] == '\n')
		{
			found_newline = 1;
			break;
		}
		(*lineptr)[line_length++] = buffer[(*buffer_position)++];
	}
	if (found_newline)
	{
		(*lineptr)[line_length] = '\0';
		(*buffer_position)++;
		chars_read = line_length + 1;
	}
	if ((size_t)chars_read > *n)
	{
		*n = chars_read;
		*lineptr = (char *)realloc(*lineptr, *n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}
	return (chars_read);
}

/**
 * _getline - reads a line of text
 * @lineptr: storage of read line
 * @n: the number of chars read
 * @fd: the descriptor
 *
 * Return: ssize_t
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[INITIAL_BUFFER_SIZE];
	static size_t buffer_position, bytes_in_buffer;
	ssize_t chars_read = 0;
	size_t line_length = 0;

	if (lineptr == NULL || n == NULL)
	{
		return (-1);
	}
	if (*lineptr == NULL || *n == 0)
	{
		*n = INITIAL_BUFFER_SIZE;
		*lineptr = (char *)malloc(sizeof(char) * *n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buffer_position >= bytes_in_buffer)
		{
			bytes_in_buffer = read(fd, buffer, INITIAL_BUFFER_SIZE);
			buffer_position = 0;
			if (bytes_in_buffer == 0)
			{
				if (line_length > 0)
				{
					free(*lineptr);
					(*lineptr)[line_length] = '\0';
					return (chars_read);
				}
				return (-1);
			}
		}
		chars_read = extract_line(lineptr, n,
				buffer, &buffer_position, bytes_in_buffer);
		if (chars_read > 0)
			break;
	}
	return (chars_read);
}
