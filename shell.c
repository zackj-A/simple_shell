#include "shell.h"
#include <stdio.h>
/**
 * _eputs - main function
 * @str: string
 */
void _eputs(const char *str)
{
	fprintf(stderr, "%s", str);
}
/**
 * _eputchar - main function
 * @c: character
 * Return: o
 */
int _eputchar(char c)
{
	fputc(c, stderr);
	return (0);
}

/**
 * _putsfd - To print an input string to a given file descriptor
 * @str: String to be printed
 * @fd: The file descriptor to write
 * Return: The number of characters written, or -1 on error
 */

int _putsfd(char *str, int fd)
{
	int num_written = 0;

	if (!str || fd < 0)
	{
		return (-1);
	}

	while (*str)
	{
		if (write(fd, str, 1) < 0)
		{
			return (-1);
		}
		num_written++;
		str++;
	}
	return (num_written);
}

/**
 * _putfd - To write the character c to a given file descriptor
 * @c: Character to be written
 * @fd: The file descriptor to write
 * Return: 1 on success, -1 on error
 */
int _putfd(char c, int fd)
{
	if (fd < 0)
	{
		return (-1);
	}

	if (write(fd, &c, 1) == 1)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
