/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 19:11:27 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/11 10:46:03 by dloustal      ########   odam.nl         */
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
		case LEFT_PAREN: return "LEFT_PAREN";
		case RIGHT_PAREN: return "RIGHT_PAREN";
		case EQUAL: return "EQUAL";
		case ECHO: return "ECHO";
		case CD: return "CD";
		case PWD: return "PWD";
		case EXPORT: return "EXPORT";
		case UNSET: return "UNSET";
		case ENV: return "ENV";
		case EXIT: return "EXIT";
		case OPTION_N: return "OPTION_N";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_OUT: return "REDIR_OUT";
		case HEREDOC: return "HEREDOC";
		case REDIR_OUT_APPEND: return "REDIR_OUT_APPEND";
		case PIPE: return "PIPE";
		case EXIT_STATUS: return "EXIT_STATUS";
		case ENV_VAR: return "ENV_VAR";
		case FILE_PATH: return "FILE_PATH";
		case SQ_STRING: return "SQ_STRING";
		case DQ_STRING: return "DQ_STRING";
		case IDENTIFIER: return "IDENTIFIER";
		case END: return "END";
		default: return "UNKNOWN";
	}
}

void print_t_token_list(t_token_list *list, const char *prefix, int is_last)
{
	t_token_node *curr = list ? list->head : NULL;

	is_last = 3;
	while (curr)
	{
		printf("%sToken: %s -> \"%s\"\n",
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
