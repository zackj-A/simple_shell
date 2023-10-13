#include "shell.h"

/**
 * interactive -function to returns true if shell is interactive
 * @info: struct address
 *
 * Return: 1 if interactive, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - function to check if character is a delimeter
 * @b: the char
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 *_isalpha - function to check for alphabetic character
 *@b: The character
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - function to convert a string to an integer
 *@x: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *x)
{
	int l, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (l = 0;  x[l] != '\0' && flag != 2; l++)
	{
		if (x[l] == '-')
			sign *= -1;

		if (x[l] >= '0' && x[l] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (x[l] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
