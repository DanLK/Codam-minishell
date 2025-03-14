/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:52:15 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 13:26:53 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_length(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len += 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*result;
	int		lim;

	num = n;
	len = find_length(n);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (result);
	lim = 0;
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
		lim += 1;
	}
	result[len] = '\0';
	while (len > lim)
	{
		result[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("num: %d  str: %s\n", (int)-2147483648, ft_itoa(-2147483648));
// 	return (0);
// }
