#include "shell.h"

/**
 * safeStringToInt - This converts a string to an integer safely
 * @s: the string to be converted to an integer
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int safeStringToInt(char *s)
{
    int i = 0;
    unsigned long int intResult = 0;

    if (*s == '+')
        s++; /* TODO: why does this make main return 255? */
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            intResult *= 10;
            intResult += (s[i] - '0');
            if (intResult > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (intResult);
}

/**
 * printErr - This prints an error message to the screen
 * @commandInfo: the parameter & return info struct in the command
 * @err_string: This is the string containing specified error type
 * Return: 0 if no numbers in string, else converted number otherwise
 *        -1 on error
 */
void printErr(info_t *commandInfo, char *err_string)
{
    errorPrintString(commandInfo->fileName);
    errorPrintString(": ");
    display_d(commandInfo->line_count, STDERR_FILENO);
    errorPrintString(": ");
    errorPrintString(commandInfo->argv[0]);
    errorPrintString(": ");
    errorPrintString(err_string);
}

/**
 * display_d - This function displays a decimal (integer) number (base 10)
 * @input: the input used to generate the decimal
 * @fd: the file descriptor used to write to the output
 *
 * Return: number of characters printed
 */
int display_d(int input, int fd)
{
    int (*_writeChar)(char) = _writeChar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        _writeChar = printErrorChar;
    if (input < 0)
    {
        _abs_ = -input;
        _writeChar('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            _writeChar('0' + current / i);
            count++;
        }
        current %= i;
    }
    _writeChar('0' + current);
    count++;

    return (count);
}

/**
 * convertNum - This is the converter function, a clone of itoa
 * @number: number used to convert
 * @base: base used to convert
 * @flags: argument flags used in the conversion
 *
 * Return: it returns string
 */
char *convertNum(long int number, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char flag = 0;
    char *ptr;
    unsigned long n = number;

    if (!(flags & CONVERT_UNSIGNED) && number < 0)
    {
        n = -number;
        flag = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (flag)
        *--ptr = flag;
    return (ptr);
}

/**
 * strip_comments - this function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void strip_comments(char *buf)
{
    int in;

    for (in = 0; buf[in] != '\0'; in++)
        if (buf[in] == '#' && (!in || buf[in - 1] == ' '))
        {
            buf[in] = '\0';
            break;
        }
}

