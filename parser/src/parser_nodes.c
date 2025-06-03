/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:24:19 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/03 11:37:04 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	t_redir_node	**redirs;

	if (!parser)
		return (NULL);
	tkn_node = parser->current;
	cmd = init_token_list();
	redirs = malloc(sizeof(t_redir_node *));
	if (!redirs)
		return (NULL); //And clear cmd
	if (!cmd)
		return (NULL);// And clear redirs
	*redirs = NULL;
	while (tkn_node->token->type != TKN_PIPE && tkn_node->token->type != TKN_END)
	{
		if (is_redirection(tkn_node->token->type))
		{
			append_redir(redirs, tkn_node->token->type, tkn_node->token->lexeme);
			advance(parser);
			tkn_node = parser->current;
			if (tkn_node->token->type == TKN_END || is_redirection(parser->current->token->type))
			{
				ft_printf("Syntax error near unexpected token \'%s\'\n",
					parser->previous->token->lexeme);
				return (clear_redirs(redirs), NULL);
				// exit(EXIT_FAILURE); // Just clear everything
				//Must clear everything and exit correctly
			}
			append_redir(redirs, tkn_node->token->type, tkn_node->token->lexeme);
		}
		else
			append_token(cmd, tkn_node->token->type, tkn_node->token->lexeme);
		advance(parser);
		tkn_node = parser->current;
	}
	node = new_tree_node(PARSER_REDIR, cmd);
	if (!node)
		return (NULL);
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
// 	// ft_printf("[debug redir_node] parser->current: %s\n", tkn_node->token->lexeme);
// 	cmd = init_token_list();
// 	if (!cmd)
// 		return (NULL);
// 	while (!is_redirection(tkn_node->token->type) && tkn_node->token->type != TKN_PIPE)
// 	{
// 		lexeme = tkn_node->token->lexeme;
// 		append_token(cmd, tkn_node->token->type, lexeme);
// 		advance(parser);
// 		tkn_node = parser->current;
// 		// ft_printf("[debug redir_node] parser->current: %s\n", tkn_node->token->lexeme);
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
// 		// ft_printf("[debug get_redirs] -- after copy: %s\n", get_last_redir(redir)->file);
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