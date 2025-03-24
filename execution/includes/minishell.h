/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:08 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/24 16:08:21 by rojornod         ###   ########.fr       */
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
#include "../../libft/libft.h"

typedef struct s_env_var
{
	char	*home_dir;
	struct	s_env_var *next;
}	t_env_var;

typedef struct s_vars
{
	char				*name;
	char				*value;
	int					exported;
	struct	s_vars		*next;
}	t_vars;

void	echo_builtin(char *string);
void	pwd_builtin(void);
void	cd_builtin(char *command, t_vars *vars);

//variables
t_vars	*add_var(t_vars **head, char *name, char *value, int exported);
t_vars	*create_var(char *name, char *value, int exported);
void print_vars(t_vars *vars);