/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloustal <dloustal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:26:30 by dloustal          #+#    #+#             */
/*   Updated: 2024/10/10 12:05:50 by dloustal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*test = malloc(50);
// 	ft_bzero(test, 50);
// 	printf("%s\n", test);
// 	return(0);
// }
