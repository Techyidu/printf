#include "main.h"


/*PRINT POINTER **/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
int printing_flags, int width, int precision, int size)
{
char padding_character;
int index = BUFF_SIZE - 2, length = 2; /* length=2, for '0x' */
unsigned long num_addrs;
char map_to[] = "0123456789abcdef";
void *addrs = va_arg(types, void *);


/* Unused parameter */
UNUSED(size);


/* Check if the pointer is null */
if (addrs == NULL) {
return write(1, "(nil)", 5);
}


/* Initialize the buffer with a null terminator */
buffer[BUFF_SIZE - 1] = '\0';


/* Convert the pointer to a hexadecimal number */
num_addrs = (unsigned long)addrs;


while (num_addrs > 0) {
buffer[index--] = map_to[num_addrs % 16];
num_addrs /= 16;
length++;
}


/* Determine the padding character */
padding_character = (printing_flags & F_ZERO) && !(printing_flags &
F_MINUS) ? '0' : ' ';


/* Write the pointer to the buffer */
index++;
return write_pointer(buffer, index, length,
width, printing_flags, padding_character, 0, 1);
}


/*For Print non-printable */
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
int printing_flags, int width, int precision, int size)
{
int i = 0, offset = 0;
char *str = va_arg(types, char *);


/* Unused parameters */
UNUSED(printing_flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);


/* Check if the string is null */
if (str == NULL) {
return write(1, "(null)", 6);
}


/* Print the non-printable characters in hexadecimal */
while (str[i] != '\0') {
if (is_printable(str[i])) {
buffer[i + offset] = str[i];
} else {
offset += append_hexa_code(str[i], buffer, i + offset);
}


i++;
}


/* Write the buffer to the standard output */
buffer[i + offset] = '\0';
return write(1, buffer, i + offset);
}


/*Print The Reverse*/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */


int print_reverse(va_list types, char buffer[],
int printing_flags, int width, int precision, int size)
{
char *str;
int i, count = 0;


/* Unused parameters */
UNUSED(buffer);
UNUSED(printing_flags);
UNUSED(width);
UNUSED(size);




int print_reverse(va_list types, char buffer[],
int printing_flags, int width, int precision, int size)
{
char *str;
int i, count = 0;


/* Unused parameters */
UNUSED(buffer);
UNUSED(printing_flags);
UNUSED(width);
UNUSED(size);


/* Check if the string is null */
if (str == NULL) {
return write(1, "(null)", 6);
}


/* Print the string in reverse order */
for (i = strlen(str) - 1; i >= 0; i--) {
count += write(1, &str[i], 1);
}


return count;
}


/****************** UTILITY FUNCTIONS *************************/
/**
 * _putchar - writes a character to stdout
 * @c: The character to write
 *
 * Return: On success 1.
 * On error, -1 is returned and errno is set appropriately.
 */
int _putchar(char c)
{
return write(1, &c, 1);
}


/**
 * is_printable - checks if a character is printable
 * @c: The character to check
 *
 * Return: 1 if the character is printable, 0 otherwise.
 */
int is_printable(char c)
{
return (c >= 32 && c <= 126);
}


/**
 * append_hexa_code - appends the hexadecimal code of a character to a buffer
 * @c: The character to get the hexadecimal code of
 * @buffer: The buffer to append the code to
 * @index: The index in the buffer to append the code to
 *
 * Return: The number of characters appended to the buffer.
 */
int append_hexa_code(char c, char buffer[], int index)
{
char hex_byte1, hex_byte2;


hex_byte1 = c >> 4;
hex_byte2 = c % 16;


buffer[index] = "0123456789abcdef"[hex_byte1];
buffer[index - 1] = "0123456789abcdef"[hex_byte2];


return 2;
}


/**
 * write_pointer - writes a pointer in hexadecimal format to a buffer
 * @buffer: The buffer to write the pointer to
 * @index: The index in the buffer to start writing the pointer
 * @length: The length of the pointer in hexadecimal
 * @width: The width of the pointer
 * @flags: The flags for the pointer
 * @padding_character: The padding character
 * @pad_start: Whether to pad the start of the pointer
 *
 * Return: The number of characters written to the buffer.
 */
int write_pointer(char buffer[], int index, int length, int width, int flags,
char padding_character, int pad_start, int zero_padding)
{
int count = 0;


/* Check if we need to pad the start */
if (pad_start) {
while (width > length) {
buffer[index++] = padding_character;
width--;
count++;
}
}


/* Write the pointer in hexadecimal format */
while (length > 0) {
buffer[index++] = buffer[index - length];
length--;
count++;
}


/* Check if we need to pad the end */
if (zero_padding && width > count) {
while (width > count) {
buffer[index++] = '0';
width--;
count++;
}
}


return count;
}
