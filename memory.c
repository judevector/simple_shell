#include "shell.h"

/**
 * bufferFree - This frees a pointer and NULLs the address
 * @data: This is the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bufferFree(void **data)
{
    if (data && *data)
    {
        free(*data);
        *data = NULL;
        return (1);
    }
    return (0);
}

