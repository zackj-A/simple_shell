#include "shell.h"
#include <stdio.h>

void _eputs(const char *str) 
{
    fprintf(stderr, "%s", str);
}

int _eputchar(char c) 
{
    fputc(c, stderr);
    return (0);
}
