/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 16:58:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/18 15:33:30 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

enum e_Type
{
	// Single character tokens
	LEFT_PAREN,
	RIGHT_PAREN,
	// Builtins
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	// Options (for example -n)
	OPTION,
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
t_token			**scan(char *source);

// Memory clears
void	clear_token_list(t_token_list *list);

#endif
