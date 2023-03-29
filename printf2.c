#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int _putchar(char c)
{
    return write(1, &c, 1);
}

void print_unsigned(unsigned int n, int base, int *char_printed, char *digits)
{
    if (n >= (unsigned int) base)
        print_unsigned(n / base, base, char_printed, digits);
    *char_printed += _putchar(digits[n % base]);
}

void print_int(int n, int base, int *char_printed, char *digits)
{
    if (n < 0) {
        *char_printed += _putchar('-');
        n = -n;
    }
    print_unsigned(n, base, char_printed, digits);
}

void print_hex(unsigned int n, int *char_printed, int upper_case)
{
    char digits[16] = "0123456789abcdef";
    if (upper_case) {
        digits[10] = 'A';
        digits[11] = 'B';
        digits[12] = 'C';
        digits[13] = 'D';
        digits[14] = 'E';
        digits[15] = 'F';
    }
    print_unsigned(n, 16, char_printed, digits);
}

char* to_binary(unsigned int n)
{
    int binary_length = 0;
    unsigned int temp = n;
    while(temp > 0)
    {
        binary_length++;
        temp = temp / 2;
    }
    char *binary_number = (char*)malloc(binary_length+1);
    binary_number[binary_length] = '\0';
    int i = binary_length - 1;
    while(n > 0)
    {
        binary_number[i] = (n % 2 == 0) ? '0' : '1';
        n = n / 2;
        i--;
    }
    return binary_number;
}

char* reverse_string(char* str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    char *reversed_str = (char*)malloc(len+1);
    reversed_str[len] = '\0';
    for(int i = 0; i < len; i++)
    {
        reversed_str[i] = str[len-i-1];
    }
    return reversed_str;
}

char* reverse_integer(int n)
{
    char *num_str = (char*)malloc(12);
    if(n == 0)
    {
        num_str[0] = '0';
        num_str[1] = '\0';
        return num_str;
    }
    int i = 0;
    int is_negative = n < 0;
    if(is_negative)
    {
        n = -n;
    }
    while(n > 0)
    {
        num_str[i] = n % 10 + '0';
        n /= 10;
        i++;
    }
    if(is_negative)
    {
        num_str[i] = '-';
        i++;
    }
    num_str[i] = '\0';
    char *reversed_num_str = reverse_string(num_str);
    free(num_str);
    return reversed_num_str;
}

int _printf(const char *format, ...)
{
    int n = 0;
    int char_printed = 0;
    int len = 0;
    int number;
    unsigned int unsigned_number;
    char *int_to_word;
    char word;
    char *words;
    va_list(args);
    va_start(args, format);
    while(format[n] != '\0')
    {
        if(format[n] == '%')
        {
            n++; // move past the format specifier
            if(format[n] == 'c')
            {
                word = (char)va_arg(args, int);
                _putchar(word);
                char_printed++;
            }
            else if(format[n] == 's')
            {
                words = (char*)va_arg(args, char*);
                len = 0;
                while(words[len] != '\0')
                {
                    len++;
                }
                write(1, words, len);
                char_printed += len;
            }
            else if(format[n] == 'd' || format[n] == 'i')
        {
            number = va_arg(args, int);
            int_to_word = reverse_integer(number);
            len = 0;
            while(int_to_word[len] != '\0')
            {
                len++;
            }
            write(1, int_to_word, len);
            char_printed += len;
            free(int_to_word);
        }
        else if(format[n] == 'b')
        {
            number = va_arg(args, unsigned int);
            words = to_binary(number);
            int_to_word = reverse_integer(words);
            len = 0;
            while(int_to_word[len] != '\0')
            {
                len++;
            }
            write(1, int_to_word, len);
            char_printed += len;
            free(int_to_word);
             
        }
        else if(format[n] == 'u')
        {
            unsigned_number = va_arg(args, unsigned int);
            print_unsigned(unsigned_number, 10, &char_printed, "0123456789");
        }
        else if(format[n] == 'x')
        {
            unsigned_number = va_arg(args, unsigned int);
            print_hex(unsigned_number, &char_printed, 0);
        }
        else if(format[n] == 'X')
        {
            unsigned_number = va_arg(args, unsigned int);
            print_hex(unsigned_number, &char_printed, 1);
        }
        else if(format[n] == '%')
        {
            _putchar('%');
            char_printed++;
        }
    }
    else
    {
        _putchar(format[n]);
        char_printed++;
    }
    n++;
}
va_end(args);
return char_printed;
}





