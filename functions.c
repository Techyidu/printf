#include "main.h"

/* Prints a char */
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
/* Gets the char from the va_list */
char c = va_arg(types, int);

/* Writes the char to the buffer and returns the number of chars written */
return (handle_write_char(c, buffer, flags, width, precision, size));
}

/* Prints a string */
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
/* UNUSED parameters */
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

/* Gets the string from the va_list */
char *str = va_arg(types, char *);

/* If the string is NULL, prints "(null)" */
if (str == NULL) {
str = "(null)";
if (precision >= 6) {
str = "      ";
}
}

/* Calculates the length of the string */
int length = 0;
while (str[length] != '\0') {
length++;
}

/* If the precision is specified and is less than the length of the string,
* sets the length to the precision */
if (precision >= 0 && precision < length) {
length = precision;
}

/* If the width is greater than the length of the string, pads the string
* with spaces to the left or right, depending on the flag F_MINUS */
if (width > length) {
if (flags & F_MINUS) {
/* Prints the string to the buffer */
write(1, str, length);

/* Pads the remaining width with spaces */
for (int i = width - length; i > 0; i--) {
write(1, " ", 1);
}

return (width);
} else {
/* Pads the remaining width with spaces */
for (int i = width - length; i > 0; i--) {
write(1, " ", 1);
}

/* Prints the string to the buffer */
write(1, str, length);

return (width);
}
}

/* Prints the string to the buffer */
return (write(1, str, length));
}

/* Prints a percent sign */
int print_percent(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
/* UNUSED parameters */
UNUSED(types);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

/* Prints a percent sign to the buffer */
return (write(1, "%%", 1));
}

/* Prints an int */
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
/* Gets the int from the va_list */
long int n = va_arg(types, long int);

/* Converts the int to an unsigned long int */
unsigned long int num = (unsigned long int)n;

/* If the int is 0, prints a 0 to the buffer */
if (n == 0) {
buffer[BUFF_SIZE - 2] = '0';
}

/* Writes a null terminator to the buffer */
buffer[BUFF_SIZE - 1] = '\0';

/* Loops through the number, converting each digit to a char and writing
* it to the buffer */
int i = BUFF_SIZE - 2;
while (num > 0) {
buffer[i--] = (num % 10) + '0';
num /= 10;
}


i++;


return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
/*Prints a Binary */
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned int n, m, i, sum;
unsigned int a[32];
int count;


UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);


n = va_arg(types, unsigned int);
m = 2147483648; /* (2 ^ 31) */
a[0] = n / m;
for (i = 1; i < 32; i++)
{
m /= 2;
a[i] = (n / m) % 2;
}
for (i = 0, sum = 0, count = 0; i < 32; i++)
{
sum += a[i];
if (sum || i == 31)
{
char z = '0' + a[i];


write(1, &z, 1);
count++;
}
}
return (count);
}
