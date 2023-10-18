#include "shell.h"

// Function prototypes
void _eputs(const char *str);
void _eputchar(char c);
void populate_env_list(info_t *info);
void read_history(info_t *info);
void hsh(info_t *info, char **av);

int main(int ac, char **av) {
    info_t info[] = { INFO_INIT };
    int fd = 2;

    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    if (ac == 2) {
        fd = open(av[1], O_RDONLY);
        if (fd == -1) {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT) {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }
    
    populate_env_list(info);
    read_history(info);
    hsh(info, av);
    
    return EXIT_SUCCESS;
}

void _eputs(const char *str) {
    // Implement _eputs function logic here
}

void _eputchar(char c) {
    // Implement _eputchar function logic here
}

void populate_env_list(info_t *info) {
    // Implement populate_env_list function logic here
}

void read_history(info_t *info) {
    // Implement read_history function logic here
}

void hsh(info_t *info, char **av) {
    // Implement hsh function logic here
}

