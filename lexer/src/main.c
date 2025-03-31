/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/17 11:29:28 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/31 16:44:41 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;

	// list = init_token_list();
	// append_token(list, ECHO, "echo");
	// append_token(list, DQ_STRING, "\"Hello, world\"");
	// append_token(list, PIPE, "|");
	// append_token(list, EOF, "");
	// print_token_list(list);
	// clear_token_list(list);

	list = scan("echo <> EOF | \'I am a single quoted sequence\' | exit");
	print_token_list(list);
	clear_token_list(list);

	return (0);
}
