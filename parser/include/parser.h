/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:41:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/03 19:12:24 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../lexer/include/lexer.h"

typedef struct s_t_node
{
	t_token			*token;
	struct s_t_node	*left;
	struct s_t_node	*right;
	int				level;
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
t_t_node	*new_tree_node(t_token *token);
void		insert_left(t_t_node *root, t_token *token);
void		insert_right(t_t_node *root, t_token *token);

//Memory clears
void		clear_subtree(t_t_node *root);
void		clear_tree(t_tree *tree);
void		clear_tree_node(t_t_node *node);

//Parsing
t_tree		*parse(t_token_list *tokens);
void		parse_tokens(t_tree *ast, t_token_list *tokens, t_parser *parser);
void		read_command(t_tree *ast, t_token_list *tokens, t_parser *parser);
void		advance(t_parser *parser);

//Debug
void		pretty_print_tree(t_t_node *root, int depth);

#endif