/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:08 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/07 17:27:04 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../libft/libft.h"

typedef struct s_env_var
{
	char				*home_dir;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_vars
{
	char				*name;
	char				*value;
	int					exported;
	int					hidden;
	struct s_vars		*next;
}	t_vars;

//builtins
void	echo_builtin(char *string);
void	pwd_builtin(void);
void	cd_builtin(char *command, t_vars *vars);
void	export_builtin(t_vars *head, char *var_name, char *var_value);
void	unset_builtin(t_vars **head, char *var_name);

//variables
t_vars	*add_var(t_vars **head, char *var_name, char *var_value, int exp);
t_vars	*create_var(char *name, char *value, int exp);
t_vars	*find_vars(t_vars *head, char *var_name);
void	env_builtin(t_vars *vars);
void	copy_env(t_vars **head, char **envp);
void	edit_var(t_vars *vars, char *var_name, char *var_value);

//utils
int		ft_strcmp(char *s1, char *s2);
void	free_array(char **array);
void	show_pid(void);
char	**convert_env(t_vars *head);

//environment
void	copy_env(t_vars **head, char **envp);

//signals
void	signal_action(void);