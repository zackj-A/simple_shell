#include "shell.h"

/**
 *_eputs - To print an input string
 * @str: string to be printed
 * Return: nothing
 */
void _eputs(const char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - function to write the character c to stderr
 * @c: character to be printed
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
void _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
}

/**
 * _putfd - To write the character c to given fd
 * @c: character
 * @fd: The filedescriptor to write
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 *_putsfd - To print an input string
 * @str: string to be printed
 * @fd: the filedescriptor to write
 * Return: the number of chars
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
