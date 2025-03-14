/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_prints.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:44:30 by dloustal      #+#    #+#                 */
/*   Updated: 2024/12/05 14:46:21 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prints(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", STDOUT_FILENO);
		return (6);
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	return (ft_strlen(str));
}

// #include <stdio.h>

// int	main(void)
// {
// 	// char	s[] = "";

// 	printf("%s\n", (char *)NULL);
// 	printf("\n");
// 	printf("\nBytes printed: %d\n", ft_prints(NULL));
// 	return (0);
// }