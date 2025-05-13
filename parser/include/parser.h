/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 16:41:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/13 10:09:25 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

enum e_Ptype
{
	PARSER_COMMAND,
	PARSER_PIPE,
	PARSER_REDIR,
	// PARSER_FILEPATH
};

typedef struct s_redir_node
{
	enum e_Type			type;
	char				*file;
	struct s_redir_node	*next;	
}		t_redir_node;

typedef struct s_t_node
{
	t_token_list		*tokens;
	struct s_t_node		*left;
	struct s_t_node		*right;
	int					level;
	enum e_Ptype		p_type;
	t_redir_node		**redirs;
}		t_t_node;	

// typedef struct s_tree
// {
// 	t_t_node	*root;
// }		t_tree;

typedef struct s_parser
{
	t_token_node	*current;
	t_token_node	*previous;
}		t_parser;

// Redirection nodes utilities
t_redir_node	*new_r_node(enum e_Type type, char *file);
t_redir_node	*get_last_redir(t_redir_node **head);
void			append_redir(t_redir_node **head, enum e_Type type, char *file);
//Tree utilities
// t_tree		*init_tree(void);
t_t_node	*new_tree_node(enum e_Ptype p_type, t_token_list *tokens);
void		insert_left(t_t_node *root, enum e_Ptype p_type, t_token_list *tokens);
void		insert_right(t_t_node *root, enum e_Ptype p_type, t_token_list *tokens);

//Memory clears
void		clear_subtree(t_t_node *root);
// void		clear_tree(t_tree *tree);
void		clear_tree_node(t_t_node *node);
void		clear_array(char **words);

/********************************************************************************
 * Functions from the old parser i.e. the first attempt at parsing 
********************************************************************************/
// t_tree		*parse(t_token_list *tokens);
// void		parse_pipe(t_t_node **root, t_token_list *tokens, t_parser *parser);
// void		parse_tokens(t_t_node **root, t_token_list *tokens, t_parser *parser);
// void		advance(t_parser *parser);
/********************************************************************************
********************************************************************************/
//Parsing
t_t_node		*parse_command(t_parser *parser);
t_t_node		*parse_pipe(t_parser *parser);
// t_t_node		*parse_redir(t_parser *parser);

//Parsing node creation
t_t_node		*pipe_node(t_t_node *left, t_t_node *right);
// t_t_node	*redir_out_node(t_t_node *cmd, t_t_node *filepath);
// t_t_node	*redir_node(t_t_node *left, t_t_node *right, t_token *redir_tkn);
t_t_node	*redir_node(t_parser *parser);
// void	get_redirs(t_parser *parser, t_redir_node **redir);
t_redir_node	**get_redirs_list(t_parser *parser);

//Parser utilities
bool			is_operator(enum e_Type type);
bool 			is_redirection(enum e_Type type);
bool			is_redir_twochar(enum e_Type type);
void			advance(t_parser *parser);
bool			is_redir(t_parser *parser);

//Debug
// void		pretty_print_tree(t_t_node *root, int depth);
void 			print_t_token_list(t_token_list *list, const char *prefix, int is_last);
void 			print_tree_node(t_t_node *node, const char *prefix, int is_last);
void			print_redirs(t_t_node *node, const char *prefix);
// void 		print_parse_tree(t_tree *tree);

#endif