/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:48:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/11 10:59:25 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	t_token_list	*list;
	t_tree			*ast;

	list = scan("unset EXACT < echo Hello World how are you | cat pipe");
	ast = parse(list);
	print_parse_tree(ast);
	//Clear memory
	clear_tree(ast);
	clear_token_list(list);
	return (0);
}