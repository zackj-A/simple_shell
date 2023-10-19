#include "shell.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point to the function
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info = INFO_INIT;

    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (info.readfd)
        : "r" (info.readfd)
    );

    if (ac == 2)
    {
        info.readfd = open(av[1], O_RDONLY);
        if (info.readfd == -1)
        {
            if (errno == EACCES)
            {
                exit(126);
            }
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
