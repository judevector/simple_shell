#include "shell.h"

/**
 * resetMatrix - This fills the memory with a constant byte in the given matrix
 * @s: the pointer to the memory area inn the program
 * @b: the byte to fill *s with in the program
 * @n: This is the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s else return null
 */
char *resetMatrix(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * dispose - This frees or dispose a string of strings
 * @pp: The string of strings used in the program
 */
void dispose(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * reallocate - reallocates a block of memory in the program
 * @ptr: This pointer to previous mallocated block
 * @prev_size: byte size of previous block
 * @modified_size: The byte size of new block
 * Return: pointer to the old block
 */
void *reallocate(void *ptr, unsigned int prev_size, unsigned int modified_size)
{
	char *p;

	if (!ptr)
		return (malloc(modified_size));
	if (!modified_size)
		return (free(ptr), NULL);
	if (modified_size == prev_size)
		return (ptr);

	p = malloc(modified_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < modified_size ? prev_size : modified_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}

