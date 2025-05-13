/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:48:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/13 17:39:17 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	t_token_list	*tokens;
	t_parser		*parser;
	t_t_node		*pipe;
	char			*exp;

	exp = "echo> >hello ";
	tokens = scan(exp);
	parser = malloc(sizeof(t_parser));
	if(!parser)
		return (0);
	parser->current = tokens->head;
	parser->previous = NULL;
	pipe = parse_pipe(parser);
	// advance(parser);
	// advance(parser);
	// advance(parser);
	// ft_printf("exp: %s\n", parser->current->token->lexeme);
	// ft_printf("----------------------------------------\n");
	if (pipe == NULL)
	{
		clear_token_list(tokens);
		free(parser);
		exit(EXIT_FAILURE);
	}
	ft_printf("Finished parsing... expression: \"%s\"\n", exp);
	print_tree_node(pipe, "", 1);
	clear_token_list(tokens);
	clear_subtree(pipe);
	free(parser);
	return (0);
}