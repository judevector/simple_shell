#include "shell.h"

/**
 * str_length - This returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string else negative
 */
int str_length(char *s)
{
int i = 0;

if (!s)
return (0);

while (*s++)
i++;
return (i);
}

/**
 * compareStrings - This performs comparison of two strings in the program
 * @s1: the first string in the program
 * @s2: the second string in the program
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compareStrings(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
 * str_concat - This concatenates the two strings
 * @destination: This is the destination buffer in the program
 * @src: the source buffer in the program
 * Return: pointer to destination buffer
 */
char *str_concat(char *destination, char *src)
{
char *ret = destination;
while (*destination)
destination++;
while (*src)
*destination++ = *src++;
*destination = *src;
return (ret);
}

