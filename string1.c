#include "shell.h"

/**
 * _strcpy - function to copy a string
 * @dest: destination
 * @src: source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[l])
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = 0;
	return (dest);
}

/**
 * _strdup - function to duplicate a string
 * @str: string to be duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int i = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	for (i++; i--;)
		ret[i] = *--str;
	return (ret);
}

/**
 *_puts - function to print an input string
 *@str: string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_putchar(str[l]);
		l++;
	}
}

/**
 * _putchar -function to  write the character c to stdout
 * @c: The character
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(1, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}
