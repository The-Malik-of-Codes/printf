#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return handle_write_char(c, buffer, flags, width, precision, size);
}

/************************* PRINT A STRING *************************/

/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char *str = va_arg(types, char *);
	int length = (str == NULL) ? handle_null_string(&str, precision) : handle_valid_string(str, precision);
	return handle_width_padding(str, buffer, flags, width, length, precision);
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(precision);
	UNUSED(size);
	return handle_char('%', buffer, flags, width, 1);
}

/************************* PRINT INT *************************/

/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	long int n = va_arg(types, long int);
	int is_negative = (n < 0) ? 1 : 0;
	unsigned long int num = (is_negative) ? (unsigned long int)(-n) : (unsigned long int)n;

	int length = handle_number_length(num);
	int padded_length = handle_padded_length(width, precision, is_negative, length);

	return handle_width_padding(num, buffer, flags, width, padded_length, precision);
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - Prints an unsigned number in binary
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);
	int length = handle_binary_length(n);
	int padded_length = handle_padded_length(width, precision, 0, length);

	return handle_width_padding(n, buffer, flags, width, padded_length, precision);
}

/* Additional helper functions can be defined below */

