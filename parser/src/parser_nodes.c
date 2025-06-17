/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:24:19 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/17 10:37:43 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/****************************************************************************** 
 * Creates a pipe tree node with the given left and right children
******************************************************************************/
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

/****************************************************************************** 
 * Sets the error message
******************************************************************************/
static void	redir_error(t_parser *p)
{
	char	*error;
	char	*err_comp;
	char	*lex;

	if (p->current->token->type == TKN_END)
		lex = ft_strdup("newline");
	else
		lex = ft_strdup(p->current->token->lexeme);
	error = ft_strjoin("Minishell: syntax error near unexpected token `", lex);
	err_comp = ft_strjoin(error, "'");
	if (!err_comp)
		perror("Error");
	else
		ft_putendl_fd(err_comp, STDERR_FILENO);
	free(error);
	free(lex);
	free(err_comp);
}

/****************************************************************************** 
 * Auxiliary function to fill up the redirections list
******************************************************************************/
static bool	set_redirs(t_parser *p,
	t_token_node *n, t_token_list *cmd, t_redir_node **redirs)
{
	while (n->token->type != TKN_PIPE
		&& n->token->type != TKN_END)
	{
		if (is_redirection(n->token->type))
		{
			append_redir(redirs, n->token->type, n->token->lexeme);
			advance(p);
			n = p->current;
			if (n->token->type == TKN_END || n->token->type == TKN_PIPE
				|| is_redirection(p->current->token->type))
			{
				redir_error(p);
				return (clear_redirs(redirs), false);
			}
			append_redir(redirs, n->token->type, n->token->lexeme);
		}
		else
			append_token(cmd, n->token->type, n->token->lexeme);
		advance(p);
		n = p->current;
	}
	return (true);
}

t_t_node	*redir_node(t_parser *parser)
{
	t_t_node		*node;
	t_token_node	*tkn_node;
	t_token_list	*cmd;
	t_redir_node	**redirs;

	if (!parser)
		return (NULL);
	tkn_node = parser->current;
	cmd = init_token_list();
	if (!cmd)
		return (NULL);
	redirs = malloc(sizeof(t_redir_node *));
	if (!redirs)
		return (clear_token_list(cmd), NULL);
	*redirs = NULL;
	if (!set_redirs(parser, tkn_node, cmd, redirs))
		return (clear_token_list(cmd), free(redirs), NULL);
	node = new_tree_node(PARSER_REDIR, cmd);
	if (!node)
		return (clear_token_list(cmd), free(redirs), NULL);
	node->redirs = redirs;
	return (node);
}

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

// t_t_node	*old_redir_node(t_parser *parser)
// {
// 	t_t_node		*node;
// 	t_token_node	*tkn_node;
// 	t_token_list	*cmd;
// 	char			*lexeme;
// 	t_redir_node	**redirs;

// 	if (!parser)
// 		return (NULL);
// 	tkn_node = parser->current;
// 	// ft_printf("[debug redir_node] parser->current: %s\n",
// 		tkn_node->token->lexeme);
// 	cmd = init_token_list();
// 	if (!cmd)
// 		return (NULL);
// 	while (!is_redirection(tkn_node->token->type) 
//		&& tkn_node->token->type != TKN_PIPE)
// 	{
// 		lexeme = tkn_node->token->lexeme;
// 		append_token(cmd, tkn_node->token->type, lexeme);
// 		advance(parser);
// 		tkn_node = parser->current;
// 		// ft_printf("[debug redir_node] parser->current: %s\n",
//				 tkn_node->token->lexeme);
// 	}
// 	node = new_tree_node(PARSER_REDIR, cmd);
// 	redirs = get_redirs_list(parser);
// 	node->redirs = redirs;
// 	return (node);
// }

/***********************************************************
 * Builds the redirections list
 * Can assume that parser->current is of type TKN_SOME_REDIR
 **************************************************************/
// void	get_redirs(t_parser *parser, t_redir_node **redir)
// {
// 	t_token_node	*tkn_node;
// 	// t_redir_node	*redir;
// 	// t_redir_node	**redirs;
// 	// char			*file;

// 	if (!parser)
// 		return ;
// 	tkn_node = parser->current;
// 	while (tkn_node && tkn_node->token->type != TKN_END
// 		&& tkn_node->token->type != TKN_PIPE)
// 	{
// 		// ft_printf("[debug get_redirs] %s\n", tkn_node->token->lexeme);
// 		append_redir(redir, tkn_node->token->type, tkn_node->token->lexeme);
// 		// ft_printf("[debug get_redirs] -- after copy: %s\n",
//				get_last_redir(redir)->file);
// 		advance(parser);
// 		tkn_node = parser->current;
// 	}
// }
/***********************************************************
 * Builds the redirections list
 * Can assume that parser->current is of type TKN_SOME_REDIR
 * 
 * For now not using ... merged with redir_node
 **************************************************************/
// t_redir_node	**get_redirs_list(t_parser *parser)
// {
// 	t_redir_node	**head;
// 	t_token_node	*tkn_node;

// 	if (!parser)
// 		return (NULL);
// 	tkn_node = parser->current;
// 	head = malloc(sizeof(t_redir_node *));
// 	*head = NULL;
// 	if (!head)
// 		return (NULL);
// 	while (tkn_node && tkn_node->token->type != TKN_END
// 		&& tkn_node->token->type != TKN_PIPE)
// 	{
// 		append_redir(head, tkn_node->token->type, tkn_node->token->lexeme);
// 		advance(parser);
// 		tkn_node = parser->current;
// 	}
// 	return (head);
// }