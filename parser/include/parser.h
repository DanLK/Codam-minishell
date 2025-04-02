/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:41:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/02 13:40:37 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../lexer/include/lexer.h"

typedef struct s_t_node
{
	t_token	*token;
	struct s_t_node	*left;
	struct s_t_node	*right;
	int				level;
}		t_t_node;	

typedef struct s_tree
{
	struct t_t_node	*root;
}		t_tree;


//Tree utilities
t_tree		*init_tree(void);
t_t_node	*new_tree_node(t_token *token);
void		insert_left(t_t_node *root, t_token *token);
void		insert_right(t_t_node *root, t_token *token);
void		pretty_print_tree(t_t_node *root, int depth);

#endif