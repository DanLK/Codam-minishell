/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 12:02:07 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/19 11:59:20 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "parser.h"
# include "execution.h"

// Helper struct to keep the heredoc parsing short
typedef struct s_hd
{
	char	*input;
	char	*file_name;
	char	*eof;
	bool	quoted_eof;
	int		*fd;
}		t_hd;

// Helper struct to keep the variable expansion short
typedef struct s_exp
{
	int		i;
	int		res_i;
	bool	in_single;
	bool	in_double;
	char	*s;
}		t_exp;

// Cmd string ultilities
bool			is_cmd(char *str, char *cmd);

// Executioner
int				execute_src(t_t_node **root, t_vars *vars, t_info *info);
int				execute_redirection(t_t_node **root, t_vars *vars,
					t_info *info);
int				call_redir(t_redir_node *cur, t_info *info);
int				execute_command(t_t_node **root, t_vars *vars, t_info *info);
int				execute_builtin(t_t_node **root, t_vars *vars, t_info *info);

//Exec Builtins
int				execute_echo(t_token_list *tokens);
int				execute_cd(t_token_list *tokens, t_vars *vars);
int				execute_exit(t_t_node *root, t_token_list *tokens,
					t_vars *vars, t_info *info);

//Exec Builtins 2
int				execute_unset(t_token_list *tokens, t_vars **head);
int				execute_export(t_token_list *tokens, t_vars *head);
int				execute_ext_command(t_t_node **root, t_vars *vars,
					t_info *info);

//Exec Aux
void			exec_redirection_aux(t_redir_node *cur, t_info *info,
					int *exit_code);
t_token_node	*skip_empty_nodes(t_t_node **root);

//Execute var assignment
int				execute_assignment(t_token_list *tokens, t_vars *vars);

// Pipes
int				execute_pipe(t_t_node **root, t_vars *head, t_info *info);

// Variable expansion
void			expand_var_tree(t_t_node **root, t_vars *vars, t_info *info);
void			expand_var_list(t_token_list *tokens, t_vars *vars,
					t_info *info);
void			expand_redir_files(t_redir_node **red_head, t_vars *v,
					t_info *info);

// String expansion length calculation
int				qstr_exp_len(char *s, t_vars *vars, t_info *info);

//Expand one string
t_exp			*init_var_exp(char *s);
char			*expand_qstring(char *s, t_vars *vars, t_info *info);

// Variable expansion utilities
void			put_exitstatus(char **result, t_info *info, int *res_i);
void			put_var(char **result, char *var, int *res_i);
char			*get_var_name(char *string, int pos);

// Var expansion for heredoc
int				get_position(char *string, char c);
char			*remove_quotes(char *string);

// Redirections
int				exec_redir_out(char *file);
int				exec_redir_append(char *file);
int				exec_redir_in(char *file);

// Heredoc parse tree
void			parse_hd_tree(t_t_node **root, t_vars *vars, t_info *info);
void			parse_hd_node(t_t_node **root, t_vars *vars, t_info *info);
void			sigint_clean(int fd, char *file_name);

// Heredoc parse
void			parse_hd(t_redir_node *cur, t_vars *vars, t_info *info);

//Heredoc parse aux
char			*get_file_name(t_info *info);
t_hd			*init_heredoc(t_info *info);
void			clear_hd_struct(t_hd *hd);
void			set_quoted_eof(t_hd *hd, t_redir_node *cur);

//Heredoc
void			heredoc_cleanup(int fd);
int				sim_press_hook(void);
void			init_sig_heredoc(void);

//Exec heredoc
int				exec_heredoc(char *file);

//Error message 
char			*error_mssg(char *file, char *type);

#endif
