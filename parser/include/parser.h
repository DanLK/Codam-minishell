/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:41:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/10 16:34:51 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../lexer/include/lexer.h"

enum e_Ptype
{
	PARSER_COMMAND,
	PARSER_OPERATOR,
	PARSER_FILEPATH
};

typedef struct s_t_node
{
	t_token_list		*tokens;
	struct s_t_node		*left;
	struct s_t_node		*right;
	int					level;
	enum e_Ptype		p_type;
}		t_t_node;	

typedef struct s_tree
{
	t_t_node	*root;
}		t_tree;

typedef struct s_parser
{
	t_token_node	*current;
	t_token_node	*previous;
}		t_parser;

//Tree utilities
t_tree		*init_tree(void);
t_t_node	*new_tree_node(enum e_Ptype p_type, t_token_list *tokens);
void		insert_left(t_t_node *root, enum e_Ptype p_type, t_token_list *tokens);
void		insert_right(t_t_node *root, enum e_Ptype p_type, t_token_list *tokens);

//Memory clears
void		clear_subtree(t_t_node *root);
void		clear_tree(t_tree *tree);
void		clear_tree_node(t_t_node *node);

//Parsing
t_tree		*parse(t_token_list *tokens);
void		parse_tokens(t_t_node **root, t_token_list *tokens, t_parser *parser);
void		advance(t_parser *parser);

// Reading commands
void		read_echo(t_tree *ast, t_token_list *tokens, t_parser *parser);
void		read_builtin(t_tree *ast, t_token_list *tokens, t_parser *parser);
void		read_unset(t_tree *ast, t_token_list *tokens, t_parser *parser);

//Parser utilities
bool		is_operator(t_token_node *node);

//Debug
// void		pretty_print_tree(t_t_node *root, int depth);
void 		print_t_token_list(t_token_list *list, const char *prefix, int is_last);
void 		print_tree_node(t_t_node *node, const char *prefix, int is_last);
void 		print_parse_tree(t_tree *tree);

#endif