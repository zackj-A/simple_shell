#include "shell.h"

/**
 * _myenv - function to print the current environment
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - to get the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: env var
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - To initialize or modify a new environment variable
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -To remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int l;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (l = 1; l <= info->argc; l++)
		_unsetenv(info, info->argv[l]);

	return (0);
}

/**
 * populate_env_list - To populate env linked list
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
void populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t l;

	for (l = 0; environ[l]; l++)
		add_node_end(&node, environ[l], 0);
	info->env = node;
}
