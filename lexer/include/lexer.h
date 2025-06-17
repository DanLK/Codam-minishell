/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 16:58:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 15:19:33 by dloustal      ########   odam.nl         */
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
	TKN_EQUAL,
	TKN_ECHO,
	TKN_CD,
	TKN_PWD,
	TKN_EXPORT,
	TKN_UNSET,
	TKN_ENV,
	TKN_EXIT,
	TKN_OPTION,
	TKN_VAR_NAME,
	TKN_VAR_VALUE,
	TKN_REDIR_IN,
	TKN_REDIR_OUT,
	TKN_HEREDOC,
	TKN_REDIR_OUT_APP,
	TKN_PIPE,
	TKN_FILE_PATH,
	TKN_WORD,
	TKN_END
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

// Context struct for reducing quote reading length (s_quoted_state)
typedef struct s_qt_st
{
	bool	in_single;
	bool	in_double;
	int		*i;
}		t_qt_st;

// Token list
t_token_list	*init_token_list(void);
t_token			*create_token(enum e_Type type, char *lex);
t_token_node	*new_node(enum e_Type type, char *lex);
t_token_node	*get_last(t_token_list *list);
void			append_token(t_token_list *list, enum e_Type type, char *lex);

// Token list utilities
void			print_token_list(t_token_list *list);
int				len_token_list(t_token_list *list);
char			**tkn_list_to_array(t_token_list *tokens);

// Lexer
t_token_list	*scan(char *src);
t_token_list	*populate_tkns(t_token_list *tokens, char *src, t_scanner *s);
void			get_cur_token(t_token_list *tokens, char *src, t_scanner *s);

//Token type identifier (token_identifier.c)
void			redir_tkn(t_token_list *tkns, char *src, t_scanner *s, char c);
// void			tkn_quote(t_token_list *tkns, char *src, t_scanner *s, char c);
// char			*tkn_env_var(char *src, t_scanner *scanner);
void			tkn_opt_word(t_token_list *t, char *src, t_scanner *s, char c);
void			tkn_assignment(t_token_list *tokens, t_scanner *s, char *src);

// Lexer utilities
void			consume_space(t_scanner *scanner, char *src);
bool			is_builtin_type(enum e_Type type);
const t_map		*get_map(void);
bool			is_variable_tkn(char *src, t_scanner *scanner);

// Lexer utilities 2
int				is_keyword(char *lexeme);
bool			kw_compare(const t_map *keywords, char *lexeme, int i);
char			get_cur_char(int *cur, char *src);
bool			is_next(int *cur, char *src, char expected);
bool			is_assignment(t_scanner *s, char *src);

//Lexer utilities symbol identifiers
bool			issymbol(char c);
bool			is_special_char(char c);
bool			is_token_breaker(char c);

// Reader quotes
char			*read_quoted(t_scanner *sc, char *src);

// Readers
char			*read_filepath(t_scanner *scanner, char *src);
char			*read_options(t_scanner *scanner, char *src);
char			*get_variable(t_scanner *s, char *src);

// Initial checks
bool			closed_quotes(char *src, bool in_single, bool in_double);
t_scanner		*init_scanner(int cur, int start);

// Memory clears
void			clear_token_list(t_token_list *list);

#endif
