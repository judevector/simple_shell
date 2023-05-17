#include "shell.h"

/**
 * errorPrintString - This prints an error to the string
 * @str: the string to be printed
 *
 * Return: Nothing done
 */
void errorPrintString(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        printErrorChar(str[i]);
        i++;
    }
}

/**
 * printErrorChar - This writes the character zy in an error`
 * @cha: The character to print and worked with
 *
 * Return: On success and 1 if error
 */
int printErrorChar(char cha)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (cha == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (cha != BUF_FLUSH)
        buf[i++] = cha;
    return (1);
}

/**
 * fdPrint - writes the character c to given fd
 * @c: The character to print to the output
 * @fd: The file descriptor to write to (default)
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fdPrint(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * fdPuts - This prints the input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to (default)
 *
 * Return: the number of chars put
 */
int fdPuts(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += fdPrint(*str++, fd);
    }
    return (i);
}

