/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traversal.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 12:02:07 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/14 17:03:18 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAVERSAL_H
# define TRAVERSAL_H
# include "parser.h"
# include "minishell.h"

// Cmd string ultilities
bool	is_cmd(char *str, char *cmd);

// Executioner
int		execute_src(t_t_node **root, t_vars *vars, t_shell_info *info);
int		execute_command(t_t_node **root, t_vars *vars, t_shell_info *info);
int		execute_builtin(t_t_node **root, t_vars *vars, t_shell_info *info);
int		execute_echo(t_token_list *tokens);
int		execute_cd(t_token_list *tokens, t_vars *vars);
int		execute_unset(t_token_list *tokens, t_vars **head);
int		execute_export(t_token_list *tokens, t_vars *head);
int		execute_assignment(t_token_list *tokens, t_vars *vars);
int		execute_ext_command(t_t_node **root, t_vars *vars, t_shell_info *info);
int		execute_redirection(t_t_node **root, t_vars *vars, t_shell_info *info);
void	call_redir(t_redir_node *cur);

// Pipes
int		execute_pipe(t_t_node **root, t_vars *head, t_shell_info *info);

// Variable expansion
void	expand_var_tree(t_t_node **root, t_vars *vars, t_shell_info *info);
void	expand_var_list(t_token_list *tokens, t_vars *vars, t_shell_info *info);
void	expand_envvar(t_token_node *node, t_vars *vars);
void	expand_exitstatus(t_token_node *node, t_shell_info *info);
char	*expand_one_dqstring(char *string, t_vars *vars);
char	*expand_dqstring(char *string, t_vars *vars);

// Variable expansion utilities
char	*get_var_name(char *string, int pos);
int		get_position(char *string, char c);

// Redirections
int		execute_redir_out(t_t_node **root, t_vars *head, t_shell_info *info);

// Redirection Experiments
void	exp_redir_out(t_t_node **root, t_vars *vars, t_shell_info *info);
void	tmp_redir_out(char *file);
void	tmp_redir_append(char *file);
void	tmp_redir_in(char *file);

#endif
