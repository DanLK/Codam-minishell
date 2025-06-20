/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:34:43 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/20 18:34:32 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/******************************************************************************
*	
*	Built ins to do:
*		echo with option -n
*		cd with only relative path or absolute path
*		pwd with no options
*		export with no options
*		unset with no options
*		env with no options or arguments
*		exit with no options
*
*******************************************************************************/

int	exit_builtin(t_vars *vars, t_info *info, int exit_code)
{
	int	exit_code_cpy;

	exit_code_cpy = exit_code;
	free_vars(vars);
	free(info);
	ft_printf("exit\n");
	rl_clear_history();
	exit(exit_code_cpy);
}

/******************************************************************************
*
*	Function that will be called when user types cd.
*
*	-If path is NULL, cd will default to the home directory. The home directory
*	 is set when the program first runs and is the root folder of the program
*	-If there is a valid path, the chdir will change directory to that path
*	-If the path is invalid an error message will be output and the directory 
*	 won't change
*
******************************************************************************/
int	cd_builtin(char *path, t_vars *vars)
{
	char	buff[PATH_MAX + 1];

	edit_var(vars, "OLDPWD", getcwd(buff, PATH_MAX + 1));
	if (!path)
	{
		vars = find_vars(vars, "HOME");
		if (!vars)
			return (ft_putendl_fd("Minishell: cd: No HOME variable found"
					, 2), 1);
		else
			return (chdir(vars->value), edit_var(vars, "PWD", vars->value), 0);
	}
	if (ft_strlen(path) == 0)
		return (0);
	else
	{
		if (chdir(path) < 0)
		{
			ft_putendl_fd("Minishell: cd: No such file or directory", 2);
			return (1);
		}
		else
			return (edit_var(vars, "PWD", getcwd(buff, PATH_MAX + 1)), 0);
	}
	return (1);
}
