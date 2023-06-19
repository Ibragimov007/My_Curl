/*Copyright (C) 2023 Timur Timak

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public
License along with this program. If not, see
<https://www.gnu.org/licenses/>. */

#include "../../headers/my_lib/my_printf.h"

int base_change(int nmbr, int base)
{
    if (nmbr == 0)
    {
        write(1, "0", 1);
        return 1;
    }
    char hex[] = "0123456789ABCDEF";
    char* str = (char*)malloc(sizeof(char) * 50);
    bool negative_flag = 0;
    int i = 0, j = 0;
    if (nmbr < 0)
    {
        nmbr = -nmbr;
        negative_flag = 1;
        write(1, "-", 1);
    }
    while (nmbr != 0)
    {
        i++;
        str[i] = hex[nmbr % base];
        nmbr /= base;
    }
    for (j = i; j != 0; j--)
    {
        write(1, &str[j], 1);
    }
    free(str);
    if (negative_flag == 1)
    {
        return i + 1;
    }
    else
    {
        return i;
    }
}

int print_pointer(long nmbr, int base)
{
    if (nmbr == 0)
    {
        write(1, "0", 1);
        return 1;
    }
    char hex[] = "0123456789abcdef";
    char* str = (char*)malloc(sizeof(char) * 50);
    bool negative_flag = 0;
    int i = 0, j = 0;
    if (nmbr < 0)
    {
        nmbr = -nmbr;
        negative_flag = 1;
        write(1, "-", 1);
    }
    while (nmbr != 0)
    {
        i++;
        str[i] = hex[nmbr % base];
        nmbr /= base;
    }
    for (j = i; j != 0; j--)
    {
        write(1, &str[j], 1);
    }
    free(str);
    if (negative_flag == 1)
    {
        return i + 1;
    }
    else
    {
        return i;
    }
}

int c(va_list arg)
{
    u_char member = (u_char)va_arg(arg, int);
    write(1, &member, 1);
    return 1;
}

int s(va_list arg)
{
    char* str = va_arg(arg, char*);
    if (str == NULL)
    {
        str = "(null)";
    }
    int i = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        write(1, &str[i], 1);
    }
    return i;
}

int d(va_list arg)
{
    int member = va_arg(arg, int);
    int i = base_change(member, 10);
    return i;
}

int o(va_list arg)
{
    unsigned int member = (unsigned int)va_arg(arg, int);
    int i = base_change(member, 8);
    return i;
}

int u(va_list arg)
{
    unsigned int member = (unsigned int)va_arg(arg, int);
    int i = base_change(member, 10);
    return i;
}

int x(va_list arg)
{
    unsigned int member = (unsigned int)va_arg(arg, int);
    int i = base_change(member, 16);
    return i;
}

int p(va_list arg)
{
    long member = (long)va_arg(arg, void*);
    write(1, "0", 1);
    write(1, "x", 1);
    int i = print_pointer(member, 16);
    return i + 2;
}

int roll(char* format_p, va_list arg)
{
    char* roll_format;
    int ret_val = 0;
    for (roll_format = format_p; *roll_format != '\0'; roll_format++)
    {
        if (*roll_format == '%')
        {
            switch (*(roll_format + 1))
            {
                case 'c':
                    ret_val += c(arg);
                    break;
                case 's':
                    ret_val += s(arg);
                    break;
                case 'd':
                    ret_val += d(arg);
                    break;
                case 'o':
                    ret_val += o(arg);
                    break;
                case 'u':
                    ret_val += u(arg);
                    break;
                case 'x':
                    ret_val += x(arg);
                    break;
                case 'p':
                    ret_val += p(arg);
                    break;
            }
            roll_format++;
        }
        else if (*(roll_format - 1) != '%')
        {
            write(1, roll_format, 1);
            ret_val++;
        }
    }
    return ret_val;
}

int my_printf(char* restrict format, ...)
{
    va_list arg;
    va_start(arg, format);
    int ret_val = 0;
    ret_val = roll(format, arg);
    va_end(arg);
    return ret_val;
}
