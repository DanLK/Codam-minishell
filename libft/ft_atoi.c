/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:43:14 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/13 10:51:18 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

static bool	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	ft_atoi(const char *nptr)
{
	int		nb;
	int		sign;
	char	*str;

	str = (char *)nptr;
	nb = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (is_sign(*str))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_digit(*str))
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb * sign);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	const char str[] = "    -2147483648 05968543";

// 	printf("ft_atoi: %d\n", ft_atoi(str));
// 	printf("atoi: %d\n", atoi(str));
// 	return (0);
// }