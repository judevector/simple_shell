#include "shell.h"

/**
 * main - This is the entry point to the program
 * @ac: This is the arg count
 * @av: This is the arg vector
 *
 * Return: 0 on success, else 1 on error
 */
int main(int ac, char **av)
{
    info_t info[] = {INFO_INIT};
    int fileD = 2;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fileD)
        : "r"(fileD));

    if (ac == 2)
    {
        fileD = open(av[1], O_RDONLY);
        if (fileD == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                errorPrintString(av[0]);
                errorPrintString(": 0: Can't open ");
                errorPrintString(av[1]);
                printErrorChar('\n');
                printErrorChar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = fileD;
    }
    fillEnv(info);
    get_hist(info);
    hsh(info, av);
    return (EXIT_SUCCESS);
}

