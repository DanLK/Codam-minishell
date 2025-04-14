/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 19:11:27 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/11 13:29:01 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_token(t_token *token)
{
	if (!token)
	{
		ft_printf("Token is NULL. Nothing to print\n");
		return ;
	}
	ft_printf("[%d]: %s\n", token->type, token->lexeme);
}

static const char *get_parser_type(enum e_Ptype type)
{
	switch (type)
	{
		case PARSER_COMMAND: return "COMMAND";
		case PARSER_OPERATOR: return "OPERATOR";
		case PARSER_FILEPATH: return "FILEPATH";
		default: return "UNKNOWN";
	}
}

static const char *get_token_type(enum e_Type type)
{
	switch (type)
	{
		case TKN_L_PAREN: return "LEFT_PAREN";
		case TKN_R_PAREN: return "RIGHT_PAREN";
		case TKN_EQUAL: return "EQUAL";
		case TKN_ECHO: return "ECHO";
		case TKN_CD: return "CD";
		case TKN_PWD: return "PWD";
		case TKN_EXPORT: return "EXPORT";
		case TKN_UNSET: return "UNSET";
		case TKN_ENV: return "ENV";
		case TKN_EXIT: return "EXIT";
		case TKN_OPTION_N: return "OPTION_N";
		case TKN_REDIR_IN: return "REDIR_IN";
		case TKN_REDIR_OUT: return "REDIR_OUT";
		case TKN_HEREDOC: return "HEREDOC";
		case TKN_REDIR_OUT_APP: return "REDIR_OUT_APPEND";
		case TKN_PIPE: return "PIPE";
		case TKN_EXIT_STATUS: return "EXIT_STATUS";
		case TKN_ENV_VAR: return "ENV_VAR";
		case TKN_FILE_PATH: return "FILE_PATH";
		case TKN_SQ_STRING: return "SQ_STRING";
		case TKN_DQ_STRING: return "DQ_STRING";
		case TKN_WORD: return "WORD";
		case TKN_END: return "END";
		default: return "UNKNOWN";
	}
}

void print_t_token_list(t_token_list *list, const char *prefix, int is_last)
{
	t_token_node *curr = list ? list->head : NULL;

	is_last = 3;
	while (curr)
	{
		printf("%sType: %s -> \"%s\"\n",
			   prefix,
			   //is_last && curr->next == NULL ? "└── " : "├── ",
			   get_token_type(curr->token->type),
			   curr->token->lexeme);
		curr = curr->next;
	}
}

void print_tree_node(t_t_node *node, const char *prefix, int is_last)
{
	if (!node)
		return;

	printf("%s%s%s\n", prefix, is_last ? "└── " : "├── ", get_parser_type(node->p_type));

	// New prefix for children
	char new_prefix[256];
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

	// Print tokens
	if (node->tokens && node->tokens->head)
		print_t_token_list(node->tokens, new_prefix, node->left == NULL && node->right == NULL);

	// Handle children
	if (node->left && node->right)
	{
		print_tree_node(node->left, new_prefix, 0);
		print_tree_node(node->right, new_prefix, 1);
	}
	else if (node->left)
	{
		print_tree_node(node->left, new_prefix, 1);
	}
	else if (node->right)
	{
		print_tree_node(node->right, new_prefix, 1);
	}
}

void print_parse_tree(t_tree *tree)
{
	if (!tree || !tree->root)
	{
		printf("Tree is empty.\n");
		return;
	}
	printf("=== ABSTRACT SYNTAX TREE ===\n\n");
	print_tree_node(tree->root, "", 1);
	printf("==================\n");
}
