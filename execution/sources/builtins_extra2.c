/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_extra2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 12:34:43 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/12 16:41:53 by dloustal      ########   odam.nl         */
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

int	exit_builtin(t_vars *vars, t_info *info)
{
	free_vars(vars);
	if (info->home_dir)
		free(info->home_dir);
	close(info->fdin);
	close(info->fdout);
	free(info);
	ft_printf("exit\n");
	exit(255);
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
			return (ft_printf("error: no HOME variable found"), 1);
		else
			return (chdir(vars->value), edit_var(vars, "PWD", vars->value), 0);
	}
	if (ft_strlen(path) == 0)
		return (0);
	else
	{
		if (chdir(path) < 0)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
			return (1);
		}
		else
			return (edit_var(vars, "PWD", getcwd(buff, PATH_MAX + 1)), 0);
	}
	return (1);
}
