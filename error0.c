#include "shell.h"

/**
 * _eputs - To print an input string
 * @str: string to be printed
 * Return: nothing
 */
void _eputs(const char *str);

/**
 * _eputchar - function to write the character c to stderr
 * @c: character to be printed
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c);

/**
 * _putfd - To write the character c to a given file descriptor
 * @c: character
 * @fd: The file descriptor to write
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd);

/**
 * _putsfd - To print an input string to a given file descriptor
 * @str: string to be printed
 * @fd: the file descriptor to write
 * Return: the number of characters written
 */
int _putsfd(char *str, int fd);

