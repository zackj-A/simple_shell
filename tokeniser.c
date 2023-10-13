#include "shell.h"

/**
 * **strtow - To split a string into words
 * @str: string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int l, y, h, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
		if (!is_delim(str[l], d) && (is_delim(str[l + 1], d) || !str[l + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[l], d))
			l++;
		h = 0;
		while (!is_delim(str[l + h], d) && str[l + h])
			h++;
		s[y] = malloc((h + 1) * sizeof(char));
		if (!s[y])
		{
			for (h = 0; h < y; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < h; m++)
			s[y][m] = str[l++];
		s[y][m] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - function to split a string into words
 * @str: string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int h = 0, y = 0, l = 0, m = 0, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
		if ((str[l] != d && str[l + 1] == d) ||
		    (str[l] != d && !str[l + 1]) || str[l + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, y = 0; y < numwords; y++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		l = 0;
		while (str[l + h] != d && str[l + h] && str[l + h] != d)
			l++;
		s[y] = malloc((y + 1) * sizeof(char));
		if (!s[y])
		{
			for (h = 0; h < y; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < h; m++)
			s[y][m] = str[l++];
		s[y][m] = 0;
	}
	s[y] = NULL;
	return (s);
}
