/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/03 19:16:40 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*parse(t_token_list *tokens)
{
	t_tree	*ast;
	t_parser	*parser;

	ast = init_tree();
	if (!ast)
		return (NULL);
	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->current = tokens->head;
	parser->previous = NULL;
	parse_tokens(ast, tokens, parser);
	free(parser);
	return (ast);
}

void	parse_tokens(t_tree *ast, t_token_list *tokens, t_parser *parser)
{
	if (!ast || !tokens || !parser)
		return ;
	read_command(ast, tokens, parser);
}

// void	read_pipe(t_tree *ast, t_token_list *tokens, t_parser *parser)
// {
// 	t_t_node	*new;

// 	if (!ast || !tokens || !parser)
// 		return ;
// 	read_command(ast, tokens, parser);
// 	while (parser->current->token->type == PIPE)
// 	{
// 		new = new_tree_node(create_token(PIPE, "|"));
// 		if (!new)
// 			return ;
// 		ast->root = new;
// 		advance(parser);
// 		read_command(ast, tokens, parser);
// 	}
// 	clear_tree_node(new);
// }

void	read_command(t_tree *ast, t_token_list *tokens, t_parser *parser)
{
	t_t_node	*new;
	enum e_Type	type;
	char		*lexeme;

	if (!ast || !tokens || !parser)
		return ;
	if (parser->current->token->type == ECHO)
	{
		type = parser->current->token->type;
		lexeme = parser->current->token->lexeme;
		new = new_tree_node(create_token(type, lexeme));
		if (!new)
			return ;
		ast->root = new;
		advance(parser);
		if (parser->current->token->type == OPTION_N)
		{
			insert_left(ast->root, create_token(OPTION_N, "-n"));
		}
		// Keep reading lexemes that are words and append them together in
		// a string to add it as the lexeme of token type word(?) 
		// or something appropriate for the input of the echo command
	}
}

void	advance(t_parser *parser)
{
	t_token_node *tmp;

	if (!parser)
		return ;
	tmp = parser->current;
	parser->current = parser->current->next;
	parser->previous = tmp;
}
