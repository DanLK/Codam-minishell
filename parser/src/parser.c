/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/14 14:37:49 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/15 18:13:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**************************************************************************** 
 * Parses a pipe expression, returning the corresponding ast node
****************************************************************************/
t_t_node	*parse_pipe(t_parser *parser)
{
	t_t_node		*right;
	t_t_node		*node;
	enum e_Type	token_type;

	if (!parser)
		return (NULL);
	node = parse_redir(parser);
	token_type = parser->current->token->type;
	while (token_type == TKN_PIPE)
	{
		advance(parser);
		right = parse_redir(parser);
		node = pipe_node(node, right);
		token_type = parser->current->token->type;
	}
	return (node);
}

/**************************************************************************** 
 * Parses a redirection expression, returning the corresponding ast node
****************************************************************************/
t_t_node	*parse_redir(t_parser *parser)
{
	t_t_node	*node;
	t_t_node	*right;
	t_token		*redir_tkn;
	enum e_Type	token_type;

	if (!parser)
		return (NULL);
	node = parse_command(parser);
	redir_tkn = parser->current->token;
	token_type = redir_tkn->type;
	if (is_redirection(token_type))
	{
		advance(parser);
		right = parse_redir(parser); //Filepath? // 
		node = redir_node(node, right, redir_tkn);
	}
	return(node);
}

/**************************************************************************** 
 * Parses a command, the most atomic entity -- has highest precedence
****************************************************************************/
t_t_node	*parse_command(t_parser *parser)
{
	t_token_list	*command;
	enum e_Type		token_type;
	char			*lexeme;
	t_t_node		*node;

	if (!parser)
		return (NULL);
	command = init_token_list();
	if (!command)
		return (NULL);
	token_type = parser->current->token->type;
	while (!is_operator(token_type) && token_type != TKN_END)
	{
		lexeme = parser->current->token->lexeme;
		append_token(command, token_type, lexeme);
		advance(parser);
		token_type = parser->current->token->type;
	}
	node = new_tree_node(PARSER_COMMAND, command);
	if (!node)
		return (NULL);
	return (node);
}
