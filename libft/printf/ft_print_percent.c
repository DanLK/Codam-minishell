/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_percent.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 13:33:32 by dloustal      #+#    #+#                 */
/*   Updated: 2024/12/05 14:45:21 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_percent(void)
{
	ft_putchar_fd('%', STDOUT_FILENO);
	return (1);
}
