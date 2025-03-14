/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:57:06 by dloustal          #+#    #+#             */
/*   Updated: 2024/11/12 17:33:14 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static bool	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if ((char)set[i] == (char)c)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	len;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	while (is_in_set(s1[start], set))
		start++;
	len = ft_strlen(s1);
	end = len - 1;
	while (is_in_set(s1[end], set) && end >= start)
		end--;
	result = (char *)malloc((end - start + 2) * sizeof(char));
	if (!result)
		return (result);
	i = 0;
	while (i < end - start + 1)
	{
		result[i] = s1[i + start];
		i++;
	}
	result[end - start + 1] = '\0';
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("TEST 1:%s\n", ft_strtrim("", ""));
// 	printf("TEST 5:%s\n", ft_strtrim("ab cd  f    ", " "));
// 	printf("TEST N:%s\n", ft_strtrim("   xxx   xxx", " x"));
// 	printf("TEST X:%s\n", ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t"));
// 	// if (is_in_set('\0', "ab"))
// 	// 	printf("yes");
// 	// ft_strtrim("ababa", "ab");
// 	return (0);
// }