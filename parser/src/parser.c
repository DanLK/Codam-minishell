/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/08 18:09:40 by dloustal      ########   odam.nl         */
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
	read_echo(ast, tokens, parser);
	read_builtin(ast, tokens, parser);
	read_unset(ast, tokens, parser);
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

void	read_echo(t_tree *ast, t_token_list *tokens, t_parser *parser)
{
	t_t_node	*new;
	enum e_Type	type;
	char		*lexeme;

	if (!ast || !tokens || !parser)
		return ;
	if (parser->current->token->type == ECHO)
	{
		lexeme = ft_strdup(parser->current->token->lexeme);
		new = new_tree_node(create_token(ECHO, lexeme));
		if (!new)
			return ;
		ast->root = new;
		advance(parser);
		free(lexeme);
		if (parser->current->token->type == OPTION_N)
		{
			insert_left(ast->root, create_token(OPTION_N, "-n"));
			advance(parser);
		}
		// Keep reading lexemes that are words and append them together in
		// a string to add it as the lexeme of token type word(?) 
		// or something appropriate for the input of the echo command
		type = parser->current->token->type;
		if (type == IDENTIFIER || type == SQ_STRING || type == DQ_STRING)
		{
			lexeme = ft_strdup(parser->current->token->lexeme);
			insert_right(ast->root, create_token(IDENTIFIER, lexeme));
			advance(parser);
		}
		free(lexeme);
	}
}

void	read_builtin(t_tree *ast, t_token_list *tokens, t_parser *parser)
{
	t_t_node	*new;
	enum e_Type	type;
	char		*lexeme;

	if (!ast || !tokens || !parser)
		return ;
	type = parser->current->token->type;
	if (type == PWD || type == ENV || type == EXIT)
	{
		lexeme = ft_strdup(parser->current->token->lexeme);
		new = new_tree_node(create_token(type, lexeme));
		if (!new)
			return ;
		ast->root = new;
		advance(parser);
		free(lexeme);
	} // else read_echo; read_cd; read_export;
}

void	read_unset(t_tree *ast, t_token_list *tokens, t_parser *parser)
{
	t_t_node	*new;
	enum e_Type	type;
	char		*lexeme;
	t_token		*token;

	if (!ast || !tokens || !parser)
		return ;
	if (parser->current->token->type == UNSET)
	{
		new = new_tree_node(create_token(UNSET, "unset"));
		if (!new)
			return ;
		ast->root = new;
		advance(parser);
	}
	type = parser->current->token->type;
	if (type == IDENTIFIER)
	{
		lexeme = ft_strdup(parser->current->token->lexeme);
		token = create_token(IDENTIFIER, lexeme);
		if (!token)
			return ;
		insert_left(ast->root, token);
		advance(parser);
		free(lexeme);
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
