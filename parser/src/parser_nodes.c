/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_nodes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 16:24:19 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/15 16:29:05 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**************************************************************************** 
 * Creates a redirection tree node with the given left and right children;  
 * and the corresponding redirection token
****************************************************************************/
t_t_node	*redir_node(t_t_node *left, t_t_node *right, t_token *redir_tkn)
{
	t_t_node		*node;
	t_token_list	*redir;

	if (!left|| !right || !redir_tkn) //Not sure about this check yet
		return (NULL);
	redir = init_token_list();
	if (!redir)
		return (NULL);
	append_token(redir, redir_tkn->type, redir_tkn->lexeme);
	node = new_tree_node(PARSER_REDIR, redir);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

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
	node->left = left;
	node->right = right;
	return (node);
}
