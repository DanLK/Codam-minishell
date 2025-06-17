/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/14 14:37:49 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 15:38:32 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**************************************************************************** 
 * Creates the parser and calls the parsing functions
****************************************************************************/
t_t_node	*parse(t_token_list *tokens)
{
	t_parser	*parser;
	t_t_node	*root;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	if (tokens->head->token->type == TKN_END)
		return (free(parser), NULL);
	parser->current = tokens->head;
	parser->previous = NULL;
	root = parse_pipe(parser);
	free(parser);
	return (root);
}

// divided from parse_pipe
static void	right_tokens_null(t_token *token, t_t_node *node, t_t_node *right)
{
	char	*error;
	char	*error_comp;
	char	*tk;

	tk = ft_strdup(token->lexeme);
	error = ft_strjoin("Minishell: syntax error near unexpected token `", tk);
	error_comp = ft_strjoin(error, "'");
	if (!error_comp)
		perror("Error: ");
	else
		ft_putendl_fd(error_comp, STDERR_FILENO);
	free(tk);
	free(error);
	free(error_comp);
	clear_subtree(node);
	clear_subtree(right);
}

// divided from parse_pipe
static void	node_tokens_null(t_t_node *node, t_parser *parser)
{
	char	*error;
	char	*error_comp;
	char	*tk;

	tk = ft_strdup(parser->current->token->lexeme);
	error = ft_strjoin("Minishell: syntax error near unexpected token `", tk);
	error_comp = ft_strjoin(error, "'");
	if (!error_comp)
		perror("Error: ");
	else
		ft_putendl_fd(error_comp, STDERR_FILENO);
	free(tk);
	free(error);
	free(error_comp);
	clear_subtree(node);
}

/**************************************************************************** 
 * Parses a pipe expression, returning the corresponding ast node
****************************************************************************/
t_t_node	*parse_pipe(t_parser *parser)
{
	t_t_node		*right;
	t_t_node		*node;
	t_token			*token;

	if (parser->current->token->type == TKN_END)
		return (NULL);
	node = parse_command(parser);
	if (!node)
		return (NULL);
	if (!node->tokens->head && !*(node->redirs))
		return (node_tokens_null(node, parser), NULL);
	token = parser->current->token;
	while (token->type == TKN_PIPE)
	{
		advance(parser);
		right = parse_command(parser);
		if (!right)
			return (NULL); //CLEAR!!
		if (!right->tokens->head)
			return (right_tokens_null(token, node, right), NULL);
		node = pipe_node(node, right);
		token = parser->current->token;
	}
	return (node);
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
	if (is_redir(parser))
		return (redir_node(parser));
	command = init_token_list();
	if (!command)
		return (NULL);
	token_type = parser->current->token->type;
	while (token_type != TKN_PIPE && token_type != TKN_END)
	{
		lexeme = parser->current->token->lexeme;
		append_token(command, token_type, lexeme);
		advance(parser);//return current
		token_type = parser->current->token->type;
	}
	node = new_tree_node(PARSER_COMMAND, command);
	if (!node)
		return (free(command), NULL);
	node->redirs = NULL;
	return (node);
}
/**************************************************************************** 
 * Parses a redirection expression, returning the corresponding ast node
****************************************************************************/
// t_t_node	*parse_redir(t_parser *parser)
// {
// 	t_t_node		*node;
// 	// t_redir_node	**redirs;
// 	// t_redir_node	*fake_redir;
// 	// t_t_node	*right;
// 	// t_token		*redir_tkn;
// 	// enum e_Type	token_type;

// 	if (!parser)
// 		return (NULL);
// 	// redirs = NULL;
// 	node = parse_command(parser);
// 	node->p_type = PARSER_REDIR;
// 	node->redirs = NULL;
// 	// if (is_redir(parser))
// 	// {
// 	// 	fake_redir = new_r_node(TKN_REDIR_OUT, ">");
// 	// 	redirs = &fake_redir;
// 	// 	node->redirs = redirs;
// 	// }
// 	return (node);
// 	// redir_tkn = parser->current->token;
// 	// token_type = redir_tkn->type;
// 	// if (is_redirection(token_type))
// 	// {
// 	// 	advance(parser);
// 	// 	right = parse_redir(parser); //Filepath? // 
// 	// 	node = redir_node(node, right, redir_tkn);
// 	// }
// 	// return(node);
// }
