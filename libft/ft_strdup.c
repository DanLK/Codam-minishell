/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:41:33 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 17:49:37 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		slen;
	char	*dup;
	int		i;

	i = 0;
	slen = ft_strlen(s);
	dup = (char *)malloc((slen + 1) * sizeof(char));
	if (!dup)
		return (dup);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *s = "Chocolate cake";

// 	char *dup;
// 	dup = ft_strdup(s);
// 	printf("%s: %s\n", s, dup);
// 	return (0);
// }