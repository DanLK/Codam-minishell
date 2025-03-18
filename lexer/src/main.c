/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/17 11:29:28 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/18 16:00:05 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;
	
	list = init_token_list();
	append_token(list, ECHO, "echo");
	print_token_list(list);
	clear_token_list(list);
	return (0);
}
