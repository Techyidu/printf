#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: Index of the current character in the format string
 * @list: List of arguments
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
int precision;

/* Check if the precision is specified */
if (format[*i + 1] != '.') {
return -1;
}

/* Initialize the precision */
precision = 0;

/* Iterate over the characters after the '.' */
for (*i += 2; format[*i] != '\0'; *i++) {
/* Check if the character is a digit */
if (is_digit(format[*i])) {
/* Multiply the precision by 10 and add the digit */
precision *= 10;
precision += format[*i] - '0';
}
/* Check if the character is a '*' */
else if (format[*i] == '*') {
/* Get the precision from the list of arguments */
precision = va_arg(list, int);
break;
}
/* Otherwise, the precision is invalid */
else {
break;
}
}

return precision;
}
