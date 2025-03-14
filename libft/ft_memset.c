/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:49:17 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/21 09:15:43 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int				i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		p[i] = c;
		n--;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[50] = "This is an example.";
// 	printf("Original string: %s\n", str);
// 	ft_memset(str + 5, 'x', 2*sizeof(char));
// 	printf("String after memset: %s\n", str);
// 	return (0);
// }