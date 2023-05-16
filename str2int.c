#include "shell.h"

/**
 * isInteractive - returns true if shell is interactive mode
 * @commandInfo: address of the struct
 *
 * Return: 1 if the mode is interactive, 0 otherwise
 */
int isInteractive(info_t *commandInfo)
{
    return (isatty(STDIN_FILENO) && commandInfo->readfd <= 2);
}

/**
 * isDelimiter - determines whether a character is a delimeter
 * @c: The check char
 * @delimiter: the string for the delimeter
 * Return: if true, 1; if false, 0
 */
int isDelimiter(char c, char *delimiter)
{
    while (*delimiter)
        if (*delimiter++ == c)
        return (1);
    return (0);
}

/**
 * isAlphabetic - verifies the presence of alphabetic characters
 * @c: The input character
 * Return: 1 if character c is alphabetic and 0 otherwise.
 */

int isAlphabetic(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * convertToInt - ransforms a string to an integer
 * @s: the string to be converted
 * Return: 0 if there are no numbers in the string, converted number else
 */

int convertToInt(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int intResult = 0;

    	for (i = 0; s[i] != '\0' && flag != 2; i++)
    	{
        	if (s[i] == '-')
           	sign *= -1;

        		if (s[i] >= '0' && s[i] <= '9')
        		{
            		flag = 1;
            		intResult *= 10;
            		intResult += (s[i] - '0');
        		}
        	else if (flag == 1)
            	flag = 2;
    	}

    if (sign == -1)
        output = -intResult;
    else
        output = intResult;

    return (output);
}

