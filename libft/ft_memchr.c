/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:01:19 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/28 10:58:22 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*p;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)p[i] == (unsigned char)c)
			return ((char *)p + i);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
//    const char str[] = "Search me.";
//    const char ch = 'c';
//    char *ret;
//    ret = ft_memchr(str, ch, 3);
//    printf("%s\n", ret);
//    return(0);
// }