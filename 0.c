#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/**
 * int_to_string - converts an int to a string
 * @number: int to convert
 *
 * Return: string
 */

char *int_to_string(int number)
{
	char *s;
	int i = 0, negative = 0;
	int start, end;
	char temp;

	s = malloc(12);
	if (!s)
		return (NULL);

	if (number == 0)
	{
		*s = '0';
		*(s + 1) = '\0';
		return (s);
	}

	if (number < 0)
	{
		negative = 1;
		number = -number;
	}

	while (number != 0)
	{
		s[i++] = '0' + number % 10;
		number /= 10;
	}

	if (negative)
		s[i++] = '-';

	s[i] = '\0';

	for (start = 0, end = i - 1; start < end; start++, end--)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
	}

	return (s);
}

/**
 * write_int - writes a digit to fd 1 or returns -1
 * @args: variadic list to pick digit from
 *
 * Return: Number length or -1
 */

int write_int(va_list *args)
{
	int number;
	char *buffer;

	number = va_arg(*args, int);
	if (!number)
		return (-1);
	buffer = int_to_string(number);
	if (!buffer)
		return (-1);
	return (write(1, buffer, strlen(buffer)));
}
/**
 * write_string - writes a string to fd 1 or returns -1
 * @args: variadic list to pick the string from
 *
 * Return: strlen or -1
 */

int write_string(va_list *args)
{
	char *s;

	s = va_arg(*args, char *);

	if (!s)
		return (write(1, "(nil)", 5));
	return (write(1, s, strlen(s)));
}

/**
 * write_char - writes a char to fd 1
 * @args: variadic arguments to pick the char from
 *
 * Return: 1 on success or -1 on failure
 */

int write_char(va_list *args)
{
	char c;

	c = va_arg(*args, int);
	return (write(1, &c, 1));
}
/**
 * _printf - handles char and string printing using %
 * @format: format specifying string
 *
 * Return: number of chars printed or -1 on failure
 */

int _printf(const char *format, ...)
{
	int a, b, s, c, d;
	int sum = 0;
	va_list args;

	if (!format)
		return (-1);

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%' && *(format + 1) == 'c')
		{
			c = write_char(&args);
			if (c == -1)
				return (c);
			else
				sum += c;
			format += 2;
		}
		else if (*format == '%' && *(format + 1) == 's')
		{
			s = write_string(&args);
			if (s == -1)
				return (s);
			sum += s;
			format += 2;
		}
		else if (*format == '%' && *(format + 1) == '%')
		{
			b = write(1, "%", 1);
			if (b == -1)
				return (b);
			sum++;
			format += 2;
		}
		else if ((*format == '%' && *(format + 1) == 'i') || (*format == '%' && *(format + 1) == 'd'))
		{
			d = write_int(&args);
			if (d == -1)
				return (d);
			sum += d;
			format += 2;
		}
		else
		{
			a = write(1, format, 1);
			if (a == -1)
				return (a);
			sum++;
			format++;
		}
	}
	va_end(args);
	return (sum);
}
