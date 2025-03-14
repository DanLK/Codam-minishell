/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:29:41 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/05 15:06:46 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char				*d;
	char				*s;
	unsigned int		i;

	i = 0;
	if (!dest && !src)
		return (0);
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	dest[16];
// 	const char 	src[16] = "I am the source.";

// 	ft_memcpy(dest, src, 16);
// 	printf("Dest is %s\n", dest);
// 	return (0);
// }