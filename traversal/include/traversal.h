/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traversal.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 12:02:07 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/05 12:25:48 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAVERSAL_H
# define TRAVERSAL_H
# include "parser.h"
# include "minishell.h"

// Executioner
int		execute_src(t_t_node **root, t_vars *vars);
int		execute_command(t_t_node **root, t_vars *vars);
int		execute_builtin(t_t_node **root, t_vars *vars);
int		execute_echo(t_token_list *tokens);
int		execute_unset(t_token_list *tokens, t_vars **head);
int		execute_export(t_token_list *tokens, t_vars *head);
int		execute_assignment(t_token_list *tokens, t_vars *vars);

// Variable expansion
void	expand_var_tree(t_t_node **root, t_vars *vars);
void	expand_var_list(t_token_list *tokens, t_vars *vars);
void	expand_envvar(t_token_node *node, t_vars *vars);
char	*expand_one_dqstring(char *string, t_vars *vars);
char	*expand_dqstring(char *string, t_vars *vars);

// Variable expansion utilities
char	*get_var_name(char *string, int pos);
int		get_position(char *string, char c);



#endif
