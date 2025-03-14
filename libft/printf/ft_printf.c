/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:49:57 by dloustal      #+#    #+#                 */
/*   Updated: 2024/12/05 15:00:10 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X'
		|| c == '%');
}

static int	handle_arg(va_list args, const char *input)
{
	int		result;

	result = 0;
	if (*input == 'c')
		result = ft_printc(va_arg(args, int));
	else if (*input == 's')
		result = ft_prints(va_arg(args, char *));
	else if (*input == 'p')
		result = ft_printp((void *)va_arg(args, void *));
	else if (*input == 'd' || *input == 'i')
		result = ft_printd((int)va_arg(args, int));
	else if (*input == 'u')
		result = ft_printu((unsigned int)va_arg(args, unsigned int));
	else if (*input == 'x')
		result = ft_printx((unsigned int)va_arg(args, unsigned int), 'x');
	else if (*input == 'X')
		result = ft_printx((unsigned int)va_arg(args, unsigned int), 'X');
	else if (*input == '%')
		result = ft_print_percent();
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && !*(format + 1))
			return (-1);
		if (*format == '%' && is_specifier(*(format + 1)))
			count += handle_arg(args, ++format);
		else
		{
			ft_putchar_fd(*format, STDOUT_FILENO);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

// #include <stdio.h>
// #include <limits.h>

// int	main(void)
// {
// 	printf("\n# printed: %d\n", ft_printf("Hello %d %s\n", 5, "worlds"));
// 	return (0);
// }