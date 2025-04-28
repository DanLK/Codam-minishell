/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traversal.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 12:02:07 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/28 12:21:12 by dloustal      ########   odam.nl         */
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

// Variable expansion
void	expand_var(t_token_node *node, t_vars *vars);
void	expand_var_list(t_token_list *tokens, t_vars *vars);
void	expand_var_tree(t_t_node **root, t_vars *vars);

#endif
