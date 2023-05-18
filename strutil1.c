#include "shell.h"

/**
 * str_copy - This copies a string in the command
 * @dest: the destination for the string
 * @src: the source for the string
 *
 * Return: pointer to destination
 */
char *str_copy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

/**
 * strdupl - This duplicates a string in the destination
 * @str: the string to duplicate in the program
 *
 * Return: pointer to the duplicated string
 */
char *strdupl(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**
 * printString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printString(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        writeChar(str[i]);
        i++;
    }
}

/**
 * writeChar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeChar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

