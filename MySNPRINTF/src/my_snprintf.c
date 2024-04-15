#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "my_snprintf.h"


int count_digits(unsigned num, size_t base)
{
    int count = 0;
    do
    {
        count++;
        num /= base;
    }
    while (num != 0);
    return count;
}

int unsigned_to_hex(int *num_digits, unsigned num, char *hex_buffer, size_t buffer_size)
{
    *num_digits = count_digits(num, HEX_BASE);
    if (hex_buffer == NULL || (*num_digits) >= buffer_size)
        return OK;

    for (int i = (*num_digits) - 1; i >= 0; i--)
    {
        int digit = num % 16;
        // Проверка, что текущий индекс не превышает размер буфера
        if (i < buffer_size)
            hex_buffer[i] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        else
            return ERR_TOO_SMALL_BUFF;
        num /= 16;
    }
    hex_buffer[*num_digits] = '\0';
    return OK;
}


int handle_string_specifier(char **buf_ptr, size_t *size, size_t *cnt, bool *flag_record, const char *str)
{
    while (*str)
    {
        if (*flag_record)
            *(*buf_ptr)++ = *str++;
        else
            str++;
        (*cnt)++;
        if (*flag_record && *cnt == *size - 1)
        {
            *(*buf_ptr)++ = '\0';
            *size = 0;
            *flag_record = false;
        }
    }
    return 0;
}

int my_snprintf(char *buffer, size_t size, const char *format, ...)
{
    bool flag_record = true;
    if (format == NULL)
        return -1;
    if (size == 0)
        flag_record = false;
    if (size == 1)
    {
        *buffer = '\0';
        size = 0;
        flag_record = false;
    }
    if (buffer == NULL)
        flag_record = false;
    char *buf_ptr = buffer;
    int chars_written, rc = OK;
    size_t cnt = 0;
    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (*format == '%' && *(format + 1) == 's')
        {
            format += 2;
            const char *str = va_arg(args, const char *);
            rc = handle_string_specifier(&buf_ptr, &size, &cnt, &flag_record, str);
            if (rc)
                flag_record = false;
        }
        else if (*format == '%' && *(format + 1) == 'x')
        {
            format += 2;
            unsigned int num = va_arg(args, unsigned int);
            if (flag_record)
                rc = unsigned_to_hex(&chars_written, num, buf_ptr, size);
            else
                rc = unsigned_to_hex(&chars_written, num, NULL, size);
            if (rc)
                flag_record = false;
            if (flag_record)
                buf_ptr += chars_written;
            cnt += chars_written;
        }
        else if (*format == '%')
        {
            va_end(args);
            *buffer = '\0';
            return -1;
        }
        else
        {
            if (flag_record)
                *buf_ptr++ = *format++;
            else
                format++;
            cnt++;
            if (flag_record && cnt == size - 1)
            {
                *buf_ptr++ = '\0';
                flag_record = false;
            }
        }
    }
    if (flag_record)
        *buf_ptr = '\0';

    va_end(args);
    return cnt;
}
