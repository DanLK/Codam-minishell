/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/17 11:29:28 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/14 10:30:46 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;
	char			*input;

	// list = init_token_list();
	// append_token(list, ECHO, "echo");
	// append_token(list, DQ_STRING, "\"Hello, world\"");
	// append_token(list, PIPE, "|");
	// append_token(list, EOF, "");
	// print_token_list(list);
	// clear_token_list(list);

	input = "echo hello >";
	ft_printf("Scanning input: \"%s\" \n\n", input);
	list = scan(input);
	print_token_list(list);
	clear_token_list(list);

	return (0);
}
