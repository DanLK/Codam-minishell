/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:48:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/15 13:55:27 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	t_token_list	*tokens;
	t_parser		*parser;
	t_t_node		*pipe;

	tokens = scan("ls -all - -xY  filex|cmd2|cmd3"); // WEIRD CASE: A|B|C
	parser = malloc(sizeof(t_parser));
	if(!parser)
		return (0);
	parser->current = tokens->head;
	parser->previous = NULL;
	pipe = parse_pipe(parser);
	print_tree_node(pipe, "", 1);
	// clear_token_list(tokens);
	// free(parser);
	return (0);
}