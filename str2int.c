#include "shell.h"

/**
 * isInteractive - This returns true if shell is in interactive mode
 * @commandInfo: address of the struct used in the program
 *
 * Return: 1 if the mode is in interactive, 0 otherwise
 */
int isInteractive(info_t *commandInfo)
{
	return (isatty(STDIN_FILENO) && commandInfo->readfd <= 2);
}

/**
 * isDelimiter - This determines whether a character is a delimeter
 * @zyk: The check the char used
 * @delimiter: the string for the delimeter
 * Return: if true, 1; if false, 0
 */
int isDelimiter(char zyk, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == zyk)
			return (1);
	return (0);
}

/**
 * isAlphabetic - verifies the presence of alphabetic characters
 * @cha: The input character
 * Return: 1 if character c is alphabetic and 0 otherwise.
 */

int isAlphabetic(int cha)
{
	if ((cha >= 'a' && cha <= 'z') || (cha >= 'A' && cha <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertToInt - This converts a string to an integer
 * @str: the string to be converted in the program
 * Return: 0 if there are no numbers in the string, else return 1
 */

int convertToInt(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int intResult = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			intResult *= 10;
			intResult += (str[i] - '0');
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
