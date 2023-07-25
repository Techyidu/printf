#include "main.h"


/*
 * print_unsigned() - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_unsigned(va_list types, char *buffer,
int flags, int width, int precision, int size)
{
int index = BUFF_SIZE - 2; /* Index of the last character in the buffer */
unsigned long int num = va_arg(types, unsigned long int);


/* Convert the number to the desired size */
num = convert_size_unsgnd(num, size);


/* If the number is 0, just print a 0 */
if (num == 0) {
buffer[index--] = '0';
}


/* Initialize the buffer with a null terminator */
buffer[BUFF_SIZE - 1] = '\0';


/* Print the number as a decimal number */
while (num > 0) {
buffer[index--] = (num % 10) + '0';
num /= 10;
}


/* Increment the index to the start of the printed number */
index++;


/* Return the number of characters printed */
return write_unsgnd(0, index, buffer, flags, width, precision, size);
}


/*
 * print_octal() - Prints an unsigned number in octal notation
 * @types: List of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char *buffer,
int flags, int width, int precision, int size)
{
int index = BUFF_SIZE - 2; /* Index of the last character in the buffer */
unsigned long int num = va_arg(types, unsigned long int);
unsigned long int init_num = num;


/* Discard the width parameter */
UNUSED(width);


/* Convert the number to the desired size */
num = convert_size_unsgnd(num, size);


/* If the number is 0, just print a 0 */
if (num == 0) {
buffer[index--] = '0';
}


/* Initialize the buffer with a null terminator */
buffer[BUFF_SIZE - 1] = '\0';


/* Print the number as an octal number */
while (num > 0) {
buffer[index--] = (num % 8) + '0';
num /= 8;
}


/* If the number was not 0, print a leading 0 */
if (init_num != 0) {
buffer[index--] = '0';
}


/* Increment the index to the start of the printed number */
index++;


/* Return the number of characters printed */
return write_unsgnd(0, index, buffer, flags, width, precision, size);
}
/*
 * print_hexadecimal() - Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char *buffer,
int flags, int width, int precision, int size)
{
return print_hexa(types, "0123456789abcdef", buffer, flags, 'x', width, precision, size);
}


/*
 * print_hexa_upper() - Prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char *buffer,
int flags, int width, int precision, int size)
{
return print_hexa(types, "0123456789ABCDEF", buffer, flags, 'X', width, precision, size);
}


/*
 * print_hexa() - Prints a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char *map_to, char *buffer,
int flags, char flag_ch, int width, int precision, int size)
{
int index = BUFF_SIZE - 2; /* Index of the last character in the buffer */
unsigned long int num = va_arg(types, unsigned long int);
unsigned long int init_num = num;


/* Discard the width parameter */
UNUSED(width);


/* Convert the number to the desired size */
num = convert_size_unsgnd(num, size);


/* If the number is 0, just print a 0 */
if (num == 0) {
buffer[index--] = '0';
}


/* Initialize the buffer with a null terminator */
buffer[BUFF_SIZE - 1] = '\0';


/* Print the number as a hexadecimal number */
while (num > 0) {
buffer[index--] = map_to[num % 16];
num /= 16;
}


/* If the number was not 0, print a leading 0x */
if (flags & F_HASH && init_num != 0) {
buffer[index--] = flag_ch;
buffer[index--] = '0';
}


/* Increment the index to the start of the printed number */
index++;


/* Return the number of characters printed */
return write_unsgnd(0, index, buffer, flags, width, precision, size);
}
