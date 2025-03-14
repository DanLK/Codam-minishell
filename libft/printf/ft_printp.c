/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/22 14:06:39 by dloustal      #+#    #+#                 */
/*   Updated: 2024/12/05 14:46:08 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printp(void	*ptr)
{
	uintptr_t	address;
	char		buffer[20];
	char		*address_to_print;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", STDOUT_FILENO);
		return (5);
	}
	address = (uintptr_t)ptr;
	address_to_print = buffer + 20;
	*--address_to_print = '\0';
	while (address > 0)
	{
		*--address_to_print = "0123456789abcdef"[address % 16];
		address /= 16;
	}
	*--address_to_print = 'x';
	*--address_to_print = '0';
	ft_putstr_fd(address_to_print, STDOUT_FILENO);
	return (ft_strlen(address_to_print));
}

// #include <stdio.h>

// int	main(void)
// {
// 	// void	*str = "Ik heb het koud";
// 	printf("%p\n", (void *)-1);
// 	printf("\nBytes printed: %d\n", ft_printp((void *)-1));
// 	return(0);
// }
