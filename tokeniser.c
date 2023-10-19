#include "shell.h"

/**
 * **strtow - To splits a string into words. Repeat delimiters are ignored
 * @str: input string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int l, h, k, m, numwords = 0;
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
	for (l = 0, h = 0; h < numwords; h++)
	{
		while (is_delim(str[l], d))
			l++;
		k = 0;
		while (!is_delim(str[l + k], d) && str[l + k])
			k++;
		s[h] = malloc((k + 1) * sizeof(char));
		if (!s[h])
		{
			for (k = 0; k < h; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[h][m] = str[l++];
		s[h][m] = 0;
	}
	s[h] = NULL;
	return (s);
}

/**
 * **strtow2 - Function to split a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int l, h, k, m, numwords = 0;
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
	for (l = 0, h = 0; h < numwords; h++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		k = 0;
		while (str[l + k] != d && str[l + k] && str[l + k] != d)
			k++;
		s[h] = malloc((k + 1) * sizeof(char));
		if (!s[h])
		{
			for (k = 0; k < h; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[h][m] = str[l++];
		s[h][m] = 0;
	}
	s[h] = NULL;
	return (s);
}
