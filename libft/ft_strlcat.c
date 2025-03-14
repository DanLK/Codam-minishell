/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:42:35 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/29 10:35:37 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	index_src;

	len_dest = 0;
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dst);
	if (size == 0)
		return (len_src);
	if (len_dest >= size)
		return (size + len_src);
	index_src = 0;
	while (src[index_src] && (index_src + len_dest + 1) < size)
	{
		dst[len_dest + index_src] = src[index_src];
		index_src++;
	}
	dst[len_dest + index_src] = '\0';
	return (len_dest + len_src);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	src[] = "";
// 	char	dest[12] = "hello";
// 	int		len = ft_strlcat(dest, src, 5);
// 	printf("dest AFTER: %s\nlen: %d\n", dest, len);
// 	return (0);
// }
