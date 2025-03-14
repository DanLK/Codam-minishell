/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:29:17 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/29 16:26:55 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1[i] == '\0' && n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (i < n && s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	s1[] = "abcdef";
// 	const char	s2[] = "abc\375xx";
// 	int		n = 5;
// 	int		result;

// 	result = ft_strncmp(s1, s2, n);
// 	printf("s1: %s\n", s1);
// 	printf("s2: %s\n", s2);
// 	printf("n: %d\n", n);
// 	printf("Result: %d\n", result);
// 	return (0);
// }