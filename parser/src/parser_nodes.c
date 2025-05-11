/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_nodes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 16:24:19 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/11 21:54:08 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**************************************************************************** 
 * Creates a redirection tree node with the given left and right children;  
 * and the corresponding redirection token
****************************************************************************/
// t_t_node	*redir_node(t_t_node *left, t_t_node *right, t_token *redir_tkn)
// {
// 	t_t_node		*node;
// 	t_token_list	*redir;

// 	if (!left|| !right || !redir_tkn) //Not sure about this check yet
// 		return (NULL);
// 	redir = init_token_list();
// 	if (!redir)
// 		return (NULL);
// 	append_token(redir, redir_tkn->type, redir_tkn->lexeme);
// 	node = new_tree_node(PARSER_REDIR, redir);
// 	if (!node)
// 		return (NULL);
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }

/**************************************************************************** 
 * Creates a pipe tree node with the given left and right children
****************************************************************************/
t_t_node	*pipe_node(t_t_node *left, t_t_node *right)
{
	t_t_node		*node;
	t_token_list	*pipe;

	if (!left || !right)
		return (NULL);
	pipe = init_token_list();
	if (!pipe)
		return (NULL);
	append_token(pipe, TKN_PIPE, "|");
	node = new_tree_node(PARSER_PIPE, pipe);
	if (!node)
		return (NULL);
	node->redirs = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

t_t_node	*redir_node(t_parser *parser)
{
	t_t_node		*node;
	t_token_node	*tkn_node;
	t_token_list	*cmd;
	char			*lexeme;
	t_redir_node	*redir;

	if (!parser)
		return (NULL);
	tkn_node = parser->current;
	// ft_printf("[debug redir_node] parser->current: %s\n", tkn_node->token->lexeme);
	cmd = init_token_list();
	if (!cmd)
		return (NULL);
	while (!is_redirection(tkn_node->token->type) && tkn_node->token->type != TKN_PIPE)
	{
		lexeme = tkn_node->token->lexeme;
		append_token(cmd, tkn_node->token->type, lexeme);
		advance(parser);
		tkn_node = parser->current;
		// ft_printf("[debug redir_node] parser->current: %s\n", tkn_node->token->lexeme);
	}
	node = new_tree_node(PARSER_REDIR, cmd);
	redir = NULL;
	get_redirs(parser, &redir);
	node->redirs = &redir;
	ft_printf("-------------------------\n");
	print_redirs(node, "");
	ft_printf("-------------------------\n");
	return (node);
}


/***********************************************************
 * Builds the redirections list
 * Can assume that parser->current is of type TKN_SOME_REDIR
 **************************************************************/
void	get_redirs(t_parser *parser, t_redir_node **redir)
{
	t_token_node	*tkn_node;
	// t_redir_node	*redir;
	// t_redir_node	**redirs;
	// char			*file;

	if (!parser)
		return ;
	tkn_node = parser->current;
	while (tkn_node && tkn_node->token->type != TKN_END
		&& tkn_node->token->type != TKN_PIPE)
	{
		// ft_printf("[debug get_redirs] %s\n", tkn_node->token->lexeme);
		append_redir(redir, tkn_node->token->type, tkn_node->token->lexeme);
		// ft_printf("[debug get_redirs] -- after copy: %s\n", get_last_redir(redir)->file);
		advance(parser);
		tkn_node = parser->current;
	}
}
