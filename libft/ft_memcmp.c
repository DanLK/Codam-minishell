/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:29:37 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/29 16:22:52 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char			*p1;
	char			*p2;
	unsigned int	i;

	p1 = (char *)s1;
	p2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)p1[i] != (unsigned char)p2[i])
			return ((unsigned char)p1[i] - (unsigned char)p2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char s1[] = "abcdef";
// 	const char s2[] = "abc\375xx";

// 	printf("%d\n", ft_memcmp(s1, s2, 5));
// 	return (0);
// }