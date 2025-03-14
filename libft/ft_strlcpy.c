/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:05:31 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/28 12:40:12 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			len_src;

	len_src = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (len_src < size - 1 && src[len_src])
	{
		dst[len_src] = src[len_src];
		len_src++;
	}
	dst[len_src] = '\0';
	while (src[len_src])
		len_src++;
	return (len_src);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	src[] = "I am the Source.";
// 	char	dest[17];
// 	unsigned int	len;

// 	printf("src: %s\n", src);
// 	len = ft_strlcpy(dest, src, 11);
// 	printf("dest: %s\n", dest);
// 	printf("len: %d\n", len);
// 	return (0);
// }