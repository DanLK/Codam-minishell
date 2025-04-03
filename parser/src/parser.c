/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/03 16:30:34 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*parse(t_token_list *tokens)
{
	t_tree	*ast;

	ast = init_tree();
	if (!ast)
		return (NULL);
	parse_tokens(ast, tokens);
}

void	parse_tokens(t_tree *ast, t_token_list *tokens)
{
	t_parser	*parser;

	if (!ast || !tokens)
		return ;
	parser = malloc(sizeof(t_parser));
	if (!parser)
		return ;
	parser->current = tokens->head;
	parser->previous = NULL;
	read_pipe(ast, tokens, parser);
}