#include "shell.h"

/**
 * isInteractiveMode - this returns true when shell is in interactive mode
 * @shellInfo: struct address or shell information
 *
 * Return: 0 when shell is not interactive, otherwise 1
 */
int isInteractiveMode(info_t *shellInfo)
{
	return (isatty(STDIN_FILENO) && shellInfo->readfd <= 2);
}

/**
 * isDelimiter - checks if character is a delimeter
 * @c: the character to check
 * @delimiterString: the delimeter string
 * Return: 1 if true, 0 if otherwise
 */
int isDelimiter(char c, char *delimiterString)
{
	while (*delimiterString)
		if (*delimiterString++ == c)
			return (1);
	return (0);
}

/**
 * isAlphabetic - checks for alphabetic character in string
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 if otherwise
 */

int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertToInt - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int convertToInt(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
