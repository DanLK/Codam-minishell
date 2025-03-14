/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:00:58 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 16:58:18 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ((char)s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*word = "teste";
// 	int		ch = 'e';
// 	printf("%s\n", ft_strchr(word, ch));
// 	return (0);
// }