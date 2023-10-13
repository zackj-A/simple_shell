#include "shell.h"

/**
 * _myhistory - function to display the history list
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function to set alias to string
 * @info: parameter
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *q, w;
	int ret;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	w = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = w;
	return (ret);
}

/**
 * set_alias - function to set alias to string
 * @info: struct
 * @str: string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function to print an alias string
 * @node: alias node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *q = NULL, *a = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (a = node->str; a <= q; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - to mimic the alias builtin
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int l = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (l = 1; info->argv[l]; l++)
	{
		q = _strchr(info->argv[l], '=');
		if (q)
			set_alias(info, info->argv[l]);
		else
			print_alias(node_starts_with(info->alias, info->argv[l], '='));
	}

	return (0);
}
