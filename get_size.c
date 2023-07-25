#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string to print the arguments
 * @i: Index of the current character in the format string
 *
 * Return: Size.
 */
int get_size(const char *format, int *i)
{
int size = 0;

/* Check if the size specifier is specified */
if (format[*i + 1] == 'l') {
size = S_LONG;
} else if (format[*i + 1] == 'h') {
size = S_SHORT;
} else {
return 0;
}

/* Update the index */
*i += 2;

return size;
}
