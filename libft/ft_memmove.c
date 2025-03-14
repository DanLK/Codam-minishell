/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:51:24 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/07 10:44:55 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (0);
	d = (char *)dest;
	s = (char *)src;
	if (d < s)
	{
		i = 0;
		while (i++ < n)
			d[i - 1] = s[i - 1];
	}
	else
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s1[] = "Hello, world!";
// 	char	s2[] = "abcdefgh";
// 	char	dest[20];

// 	// Copy Hello, world! to destination
// 	ft_memmove(dest, s1, 13);
// 	printf("Result 0: %s\n", dest); // Expect Hello, world!

// 	// Move world! to the beginning of the string
// 	ft_memmove(s1, s1 + 7, 6);
// 	printf("Result 1: %s\n", s1); // Expect world! world!

// 	// Move the first 4 characters to the end of the string
// 	ft_memmove(s2 + 4, s2, 4);
// 	printf("Result 2: %s\n", s2); // Expect abcdabcd
// 	return (0);
// }
