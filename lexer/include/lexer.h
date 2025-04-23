/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 16:58:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/22 14:29:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"

enum e_Type
{
	// Single character tokens
	TKN_L_PAREN, //0
	TKN_R_PAREN, //1
	TKN_EQUAL, //2
	// Builtins
	TKN_ECHO, //3
	TKN_CD,
	TKN_PWD, //5
	TKN_EXPORT,
	TKN_UNSET,
	TKN_ENV,
	TKN_EXIT, //9
	// Options
	TKN_OPTION,
	// Redirections
	TKN_REDIR_IN, //11
	TKN_REDIR_OUT,
	TKN_HEREDOC,
	TKN_REDIR_OUT_APP,
	// Operators
	TKN_PIPE, //15
	// Exit status ($?)
	TKN_EXIT_STATUS,
	// Parameter Expansion ($)
	TKN_ENV_VAR,
	// Path
	TKN_FILE_PATH, //18
	// Literals
	TKN_SQ_STRING,
	TKN_DQ_STRING,
	TKN_WORD, //21
	//EOF to indicate end of input
	TKN_END //22
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
	t_token_node	*head;
}		t_token_list;

typedef struct s_scanner
{
	int	start;
	int	cur;
}		t_scanner;

typedef struct s_map
{
	char		*words[7];
	enum e_Type	types[7];
}		t_map;

// List utilities
t_token_list	*init_token_list(void);
t_token			*create_token(enum e_Type type, char *lex);
t_token_node	*new_node(enum e_Type type, char *lex);
t_token_node	*get_last(t_token_list *list);
void			append_token(t_token_list *list, enum e_Type type, char *lex);
t_scanner		*init_scanner(int cur, int start);
void			print_token_list(t_token_list *list);

// Lexer
t_token_list	*scan(char *src);
t_token_list	*populate_tkns(t_token_list *tokens, char *src, t_scanner *s);

//Token type identifier (token_identifier.c)
void			get_cur_token(t_token_list *tokens, char *src, t_scanner *s);
void			redir_tkn(t_token_list *tkns, char *src, t_scanner *s, char c);
void			tkn_quote(t_token_list *tkns, char *src, t_scanner *s, char c);
void			tkn_opt_word(t_token_list *tkns, char *src, t_scanner *s, char c);
char			*read_options(t_scanner *scanner, char *src);


// Lexer utilities
void			consume_space(t_scanner *scanner, char *src);
char			*read_quoted(t_scanner *scanner, char *src, char quotes);
char			*read_filepath(t_scanner *scanner, char *src);
bool			is_special_char(char c);
bool			is_builtin_type(enum e_Type type);
char			*read_identifier(t_scanner *scanner, char *src);
const t_map		*get_map(void);

// Lexer utilities 2
int				is_keyword(char *lexeme);
bool			kw_compare(const t_map *keywords, char *lexeme, int i);
bool			issymbol(char c);
char			get_current_char(int *cur, char *src);
bool			is_next(int *cur, char *src, char expected);

// Memory clears
void			clear_token_list(t_token_list *list);

#endif
