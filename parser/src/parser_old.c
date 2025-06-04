/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_old.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:04 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/04 14:44:56 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// t_tree	*parse(t_token_list *tokens)
// {
// 	t_tree		*ast;
// 	t_parser	*parser;

// 	ast = init_tree();
// 	if (!ast)
// 		return (NULL);
// 	parser = malloc(sizeof(t_parser));
// 	if (!parser)
// 		return (NULL);
// 	parser->current = tokens->head;
// 	parser->previous = NULL;
// 	parse_pipe(&(ast->root), tokens, parser);
// 	free(parser);
// 	return (ast);
// }

/****************************************************************************
 * 
 * This function reads the tokens one by one and starts building a new list
 * of tokens; when it finds an operator (>, <, >>, << or |) it stops and 
 * puts the list into a node that will be the left child of the operator. 
 * Then puts the operator at the root and builds the right side in a similar
 * way.
 * 
 ****************************************************************************/
// void	parse_tokens(t_t_node **root, t_token_list *tokens, t_parser *parser)
// {
// 	t_token_list	*command;
// 	t_token_list	*operator;
// 	enum e_Type		token_type;
// 	char			*lexeme;

// 	if (!tokens || !parser)
// 		return ;
// 	ft_printf("Debug parse_tokens: entering function...\n");
// 	command = init_token_list();
// 	token_type = parser->current->token->type;
// 	ft_printf("Token type of the current token: %d...\n", token_type);
// 	while (!is_operator(parser->current)
// 		&& token_type != TKN_END)
// 	{
// 		lexeme = parser->current->token->lexeme;
// 		ft_printf("Debug parse_tokens [while loop] Current token: %s...\n", lexeme);
// 		append_token(command, token_type, lexeme);
// 		advance(parser);
// 		token_type = parser->current->token->type;
// 	}
// 	// print_token_list(command);
// 	if (token_type != TKN_END)
// 	{
// 		operator = init_token_list();
// 		append_token(operator, token_type, parser->current->token->lexeme);
// 		advance(parser);
// 		*root = new_tree_node(PARSER_OPERATOR, operator);
// 		insert_left(*root, PARSER_COMMAND, command);
// 		if (parser->current->token->type == TKN_END)
// 			perror("Missing right side operand"); // Not sure if this is really a syntax error
// 		else
// 		{
// 			// In some cases the right node mucht not have a pointer to its corresponding right or left nodes initialized.
// 			parse_tokens(&((*root)->right), tokens, parser);
// 		}
// 	}
// 	else
// 		*root = new_tree_node(PARSER_COMMAND, command);
// }

// void	parse_pipe(t_t_node **root, t_token_list *tokens, t_parser *parser)
// {
// 	t_token_list	*command;
// 	t_token_list	*operator;
// 	enum e_Type		token_type;
// 	char			*lexeme;
// 	t_parser		*np;

// 	if (!tokens || !parser)
// 		return ;
// 	ft_printf("Debug parse_pipe: entering function...\n");
// 	command = init_token_list();
// 	token_type = parser->current->token->type;
// 	ft_printf("Token type of the current token: %d...\n", token_type);
// 	while (token_type != TKN_PIPE
// 		&& token_type != TKN_END)
// 	{
// 		lexeme = parser->current->token->lexeme;
// 		append_token(command, token_type, lexeme);
// 		advance(parser);
// 		token_type = parser->current->token->type;
// 	}
// 	print_token_list(command);
// 	ft_printf("Debug parse_pipe: command->head token: %s\n\n", command->head->token->lexeme);
// 	if (token_type != TKN_END)
// 	{
// 		ft_printf("Debug parse_pipe: entering if condition...\n");
// 		operator = init_token_list();
// 		append_token(operator, token_type, parser->current->token->lexeme);
// 		advance(parser);
// 		*root = new_tree_node(PARSER_OPERATOR, operator);
// 		np = malloc(sizeof(t_parser));
// 		if (!np)
// 			return ;
// 		np->current = command->head;
// 		np->previous = NULL;
// 		ft_printf("Debug parse_pipe: created a new parser...\n");
// 		ft_printf("Debug parse_pipe: parser->current: %s\n\n", np->current->token->lexeme);
// 		parse_tokens(&((*root)->left), command, np);
// 		free(np);
// 		if (parser->current->token->type == TKN_END)
// 			perror("Syntax error: Missing right side of the pipe"); // Not sure if this is really a syntax error
// 		else
// 		{
// 			parse_pipe(&((*root)->right), tokens, parser);
// 		}
// 	}
// 	else
// 		*root = new_tree_node(PARSER_COMMAND, command);
// }
