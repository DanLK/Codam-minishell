/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_atoi_base.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: dloustal <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/08/29 11:57:18 by dloustal       #+#    #+#                */
/*   Updated: 2024/08/29 11:57:22 by dloustal       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	index_digit(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	valid_base_len(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-' || base[i] <= ' ' || base[i] > '~')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (i);
}

int	calculate_int(char *str, char *base, int b)
{
	int	nb;
	int	index;

	nb = 0;
	index = index_digit(*str, base);
	while (index != -1)
	{
		nb = nb * b + index;
		str++;
		index = index_digit(*str, base);
	}
	return (nb);
}

int	ft_atoi_base(char *str, char *base)
{
	int	base_len;
	int	nb;
	int	sign;

	base_len = valid_base_len(base);
	if (base_len == 0)
		return (0);
	nb = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	nb = calculate_int(str, base, base_len);
	return (nb * sign);
}

// #include<stdio.h>

// int	main(void)
// {
// 	char str[] = "    \t  +-----10000000000000000000000000000000 8563";
// 	char base[] = "01";

// 	printf("%d\n", ft_atoi_base(str, base));
// 	return (0);
// }