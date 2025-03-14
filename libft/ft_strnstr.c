/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:02:02 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/05 15:41:56 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*b;
	char			*l;

	b = (char *)big;
	l = (char *)little;
	i = 0;
	if (l[0] == '\0')
		return (b);
	while (i < len && b[i])
	{
		if ((unsigned char)b[i] == (unsigned char)l[0])
		{
			j = 0;
			while (j < ft_strlen(l) && b[i + j] == l[j] && (i + j) < len)
			{
				if (j == ft_strlen(l) - 1)
					return (b + i);
				j++;
			}
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	big[] = "";
// 	const char	little[] = "xx";

// 	printf("%s\n", ft_strnstr(big, little, 4294967295));
// 	return (0);
// }