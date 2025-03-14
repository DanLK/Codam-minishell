/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:03:41 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/10 12:04:43 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%c\n", ft_tolower('X'));
// 	printf("%c\n", ft_tolower('@'));
// 	return (0);
// }