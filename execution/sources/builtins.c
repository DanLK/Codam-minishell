/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:27:48 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/10 16:51:13 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	exit_builtin(t_vars *vars, t_shell_info *info)
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

static void	print_export(t_vars	*temp)
{
	while (temp)
	{
		if ((!temp->value || ft_strlen(temp->value) == 0) && temp->exported == 1)
			ft_printf("declare -x %s\n", temp->name);
		else if (temp->value && temp->exported == 1)
			ft_printf("declare -x %s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

static int validate_var_name(char *var_name)
{
	if (ft_isalpha(var_name[0]) == 1 || var_name[0] == '_')
		return (0);
	else
		return (1);
}

/******************************************************************************
*
*		This function will print out all the exported variables
*		If the value is null and it is exported 
*
******************************************************************************/
int	export_builtin(t_vars **head, char *var_name, char *var_value)
{
	t_vars	*temp;

	if (!var_name)
	{
		temp = *head;
		return (print_export(temp), 0);
	}
	else
	{
		if (validate_var_name(var_name) == 0)
		{
			temp = find_vars(*head, var_name);
			if (temp)
			{
				temp->exported = 1;
				temp->hidden = 0;
				if (var_value)
				{
					if (temp->value)
						free(temp->value);
					temp->value = ft_strdup(var_value);
				}
				return (0);
			}
			else
				return (add_var(head, var_name, var_value, 1), 0);
		}
		else 
			return (ft_printf("`%s': not a valid identifier\n", var_name), 1);
	}
}
