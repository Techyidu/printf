#include "main.h"

/**
 * get_width - This Calculates the width for printing..
 * @format: Formatted string in which to print the arguments
 * @i: Index of the current character in the format string
 * @list: Argument List 
 *
 * Return: Width.
 */
int get_width(const char *format, int *i, va_list list)
{
int width = 0;

/* Iterate over the characters after the '%' */
for (*i += 1; format[*i] != '\0'; *i++) {
/* Check if the character is a digit */
if (is_digit(format[*i])) {
/* Multiply the width by 10 and add the digit */
width *= 10;
width += format[*i] - '0';
}
/* Check if the character is a '*' */
else if (format[*i] == '*') {
/* Get the width from the list of arguments */
width = va_arg(list, int);
break;
}
/* Otherwise, the width is invalid */
else {
break;
}
}

return width;
}
