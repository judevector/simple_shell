#include "shell.h"

/**
 **strnCopy - this copies a string in place of another
 *@target: the destination or target of the string to be copied to
 *@src: the source string used in the copy
 *@n: the amount of characters to be copied
 *Return: the concatenated string after the copy
 */
char *strnCopy(char *target, char *src, int n)
{
	int i, j;
	char *s = target;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		target[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			target[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strnConcat - This concatenates the two strings
 *@target: the first string used in the copy
 *@src: the second string used in the copy
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string after running this function
 */
char *strnConcat(char *target, char *src, int n)
{
	int l, m;
	char *s = target;

	l = 0;
	m = 0;
	while (target[l] != '\0')
		l++;
	while (src[m] != '\0' && m < n)
	{
		target[l] = src[m];
		l++;
		m++;
	}
	if (m < n)
		target[l] = '\0';
	return (s);
}

/**
 **findChar - This locates a character in a string
 *@s: the string to be parsed in the command
 *@c: the character to look for in the command
 *Return: (s) a pointer to the memory area s
 */
char *findChar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

