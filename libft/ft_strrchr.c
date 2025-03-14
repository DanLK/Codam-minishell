/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:15:06 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 17:21:56 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		i;

	p = (char *)s;
	i = ft_strlen(p);
	while (i >= 0)
	{
		if ((unsigned char)p[i] == (unsigned char)c)
			return ((char *)p + i);
		i--;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*s = "";
// 	printf("%s\n", ft_strrchr(s, 'c'));
// 	return (0);
// }