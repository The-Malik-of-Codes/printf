#include "main.h"

int _printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    int printed_chars = 0;
    va_list args;
    char buffer[BUFF_SIZE];
    int buff_ind = 0;

    va_start(args, format);

    for (int i = 0; format[i]; ++i)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind, &printed_chars);
        }
        else
        {
            print_buffer(buffer, &buff_ind, &printed_chars);
            i += handle_format(&format[i + 1], args, buffer, &printed_chars);
        }
    }

    print_buffer(buffer, &buff_ind, &printed_chars);
    va_end(args);

    return printed_chars;
}

void print_buffer(char buffer[], int *buff_ind, int *printed_chars)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *printed_chars += *buff_ind;
        *buff_ind = 0;
    }
}

int handle_format(const char *format, va_list args, char buffer[], int *printed_chars)
{
    int flags, width, precision, size;
    int printed = 0;

    flags = get_flags(format, &format);
    width = get_width(format, &format, args);
    precision = get_precision(format, &format, args);
    size = get_size(format, &format);

    printed = handle_print(format, args, buffer, flags, width, precision, size);
    if (printed == -1)
        return 0;

    *printed_chars += printed;
    return format - 1;
}

