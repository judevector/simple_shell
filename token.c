#include "shell.h"

/**
 * **word_split - This splits a string into words in the program
 * @str: the input string used in the program
 * @d: the delimeter string used in the program
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **word_split(char *str, char *d)
{
	int i, j, k, m, wordTotal = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isDelimiter(str[i], d) && (isDelimiter(str[i + 1], d) || !str[i + 1]))
			wordTotal++;
	if (wordTotal == 0)
		return (NULL);
	s = malloc((1 + wordTotal) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wordTotal; j++)
	{
		while (isDelimiter(str[i], d))
			i++;
		k = 0;
		while (!isDelimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **extract_words - This extracts or splits a string into words
 * @str: the input string used in the program
 * @d: the delimeter used in the program
 * Return: a pointer to an array of strings, else NULL on failure
 */
char **extract_words(char *str, char d)
{
	int i, j, k, m, wordTotal = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			wordTotal++;
	if (wordTotal == 0)
		return (NULL);
			s = malloc((1 + wordTotal) * sizeof(char *));
			if (!s)
				return (NULL);
			for (i = 0, j = 0; j < wordTotal; j++)
			{
				while (str[i] == d && str[i] != d)
					i++;
				k = 0;
				while (str[i + k] != d && str[i + k] && str[i + k] != d)
					k++;
				s[j] = malloc((k + 1) * sizeof(char));
				if (!s[j])
				{
					for (k = 0; k < j; k++)
						free(s[k]);
					free(s);
					return (NULL);
				}
				for (m = 0; m < k; m++)
					s[j][m] = str[i++];
				s[j][m] = 0;
			}
			s[j] = NULL;
			return (s);
}
