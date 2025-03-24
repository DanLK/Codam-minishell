/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/17 11:29:28 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/24 15:55:04 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;
	// char			*substr;
	// int	cur;

	
	// list = init_token_list();
	// append_token(list, ECHO, "echo");
	// append_token(list, DQ_STRING, "\"Hello, world\"");
	// append_token(list, PIPE, "|");
	// append_token(list, EOF, "");
	// print_token_list(list);
	// clear_token_list(list);

	list = scan("M YVAR=hola | echo \"    Im a double quoted string with spaces \"  Hello   <file.txt word anotherword ");
	print_token_list(list);
	clear_token_list(list);

	// cur = 6;
	// substr = read_until(&cur, cur, "echo \"    Hoi  \"", '\"');
	// ft_printf("Substr: %s\n", substr);
	return (0);
}
