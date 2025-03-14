/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:58:48 by dloustal      #+#    #+#                 */
/*   Updated: 2024/12/05 14:45:29 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printc(char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (1);
}
