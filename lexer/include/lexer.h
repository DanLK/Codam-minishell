/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 16:58:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/20 17:08:11 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

enum e_Type
{
	// Single character tokens
	LEFT_PAREN,
	RIGHT_PAREN,
	EQUAL,
	// Builtins
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	// Options (for example -n)
	OPTION_N,
	// Redirections
	RED_INPUT,
	RED_OUTPUT,
	HEREDOC,
	RED_OUT_APP,
	// Operators
	PIPE,
	// Exit status ($?)
	EXIT_STATUS,
	// Parameter Expansion ($)
	ENV_VAR,
	// Path
	FILE_PATH,
	// Literals
	SQ_STRING,
	DQ_STRING,
	IDENTIFIER,
	//Whitespace
	WHITESPACE,
	//EOF to indicate end of input
	EOF
};

typedef struct token
{
	enum e_Type	type;
	char		*lexeme;
}		t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}		t_token_node;

typedef struct s_token_list
{
	struct s_token_node	*head;
}		t_token_list;

// List utilities
t_token_list	*init_token_list(void);
t_token_node	*new_node(enum e_Type type, char *lex);
t_token_node	*get_last(t_token_list *list);
void			append_token(t_token_list *list, enum e_Type type, char *lex);
void			print_token_list(t_token_list *list);

// Lexer
t_token_list	*scan(char *src);
t_token_list	*populate_tokens(t_token_list *tokens, char *src);
void			get_cur_token(t_token_list *tokens, char *src, int s, int *cur);
char			get_current_char(int *cur, char *src);
bool			is_next(int *cur, char *src, char expected);

// Lexer utilities
void			consume_space(int *cur, int *start, char *src);
char			*read_quoted(int *cur, int start, char *src, char quotes);
char			*read_filepath(int *cur, int start, char *src);

// Memory clears
void			clear_token_list(t_token_list *list);

#endif
