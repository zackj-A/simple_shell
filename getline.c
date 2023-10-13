#include "shell.h"

/**
 * input_buf - To buffer chained commands
 * @info: parameter
 * @buf: address 1
 * @len: address 2
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t f = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		f = getline(buf, &len_p, stdin);
#else
		f = _getline(info, buf, &len_p);
#endif
		if (f > 0)
		{
			if ((*buf)[f - 1] == '\n')
			{
				(*buf)[f - 1] = '\0';
				f--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = f;
				info->cmd_buf = buf;
			}
		}
	}
	return (f);
}

/**
 * get_input - function to get a line minus the newline
 * @info: parameter
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t f = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	f = input_buf(info, &buf, &len);
	if (f == -1)
		return (-1);
	if (len)
	{
		y = x;
		p = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (f); /* return length of buffer from _getline() */
}

/**
 * read_buf - function to read a buffer
 * @info: parameter
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t f = 0;

	if (*i)
		return (0);
	f = read(info->readfd, buf, READ_BUF_SIZE);
	if (f >= 0)
		*i = f;
	return (f);
}

/**
 * _getline - To get the next line of input from STDIN
 * @info: parameter
 * @ptr: pointer to buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t h;
	ssize_t f = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len)
		x = len = 0;

	f = read_buf(info, buf, &len);
	if (f == -1 || (f == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	h = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + h : h + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + x, h - x);
	else
		_strncpy(new_p, buf + x, h - x + 1);

	s += h - x;
	x = h;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - To block ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
