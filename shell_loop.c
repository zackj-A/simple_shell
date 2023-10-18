#include "shell.h"

/**
 * hsh - main function of shell loop
 * @info: the parameter
 * @av: the argument vector
 * Return: 0 on success, 1 on error, or error code
 */
void hsh(info_t *info, char **av)
{
	ssize_t f = 0;
	int builtin_ret = 0;

	while (f != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		f = get_input(info);
		if (f != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
}

/**
 * find_builtin - function to find a builtin command
 * @info: the parameter
 * Return: -1 if builtin not found,
 *		0 if builtin executed,
 *		1 if builtin found but not successful,
 *		-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int l, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (l = 0; builtintbl[l].type; l++)
		if (_strcmp(info->argv[0], builtintbl[l].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[l].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - function to find a command in PATH
 * @info: the parameter
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int l, h;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (l = 0, l = 0; info->arg[l]; l++)
		if (!is_delim(info->arg[l], " \t\n"))
			h++;
	if (!h)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - function to fork a an exec thread to run cmd
 * @info: the parameter
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
