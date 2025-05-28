/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:27:48 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/27 17:13:02 by rojornod         ###   ########.fr       */
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

int	exit_builtin(t_vars *vars,  t_shell_info *info)
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
*	Very barebones echo. so far it prints the text after echo with either a new 
*	line or not based on the -n flag.
*
*	32 = SPACE
*	34 = "
*	39 = '
*	92 = \
*
*	SOME TO DO
*
*	-handle single and double quotes (they are ignored but affect expansion) ⍻
*	-ignore backslashes ✔
*	-multiple spaces are collapsed into one if not between quotes ✔
*	-multiple spaces are not ignored if between quotes
*	-ignore empty variables
*	-double dash (--) makes echo ignore potential flags (ex: -n)
*	
******************************************************************************/
static void	echo_printing(char **tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i])
	{
		// if (tokens[i][j] == ' ' || tokens[i][j] == '\'' || tokens[i][j] == '\\')
		// 	j++;
		if (tokens[i][j] == ' ' && tokens[i][j + 1] == ' ')
		{
			ft_putstr_fd(tokens[i], 1);
			while (tokens[i][j] == ' ')
				j++;
		}
		else
		{
			ft_putstr_fd(tokens[i], 1);
			ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

/******************************************************************************
*
*		-This function first checks if echo was passed with no extra arguments
*		 and if thats true it prints a new line.
*		-If echo ws passed with the flag -n it then checks if there is nothing
*		 after that and if its true it gives the prompt
*		 back
*		-If echo is passed with text, it calls the echo_printing function
*		
******************************************************************************/
int	echo_builtin(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens[0])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (ft_strcmp(tokens[0], "-n") == 0)
	{
		i = 1;
		while (ft_strcmp(tokens[i], "-n") == 0)
			i++;
		if (!tokens[i])
			return (0);
		echo_printing(tokens, i);
	}
	else
	{
		i = 0;
		echo_printing(tokens, i);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

/******************************************************************************
*	
*	-Currently this function simply displays the current working directory if 
*	it detects that the user typed pwd
*	
*	-getcwd gives you the current working directory when given a buffer and 
*	size
*	
******************************************************************************/
int	pwd_builtin(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = getcwd(buff, PATH_MAX + 1);
	if (!current_directory)
		return (1);
	ft_printf("%s\n", current_directory);
	return (0);
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
	if (ft_strlen(path) == 0)
		return (0);
	if (!path)
	{
		vars = find_vars(vars, "HOME");
		if (!vars)
		{
			ft_printf("error: no HOME variable found");
			return (1);
		}
		else
		{
			chdir(vars->value);
			return (0);
		}
	}
	else
	{
		if (chdir(path) < 0)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
			return (1);
		}
		else 
			return (0);
	}
	return (1);
}

/******************************************************************************
*
*		This function will print out all the exported variables
		If the value is null and it is exported 
*
******************************************************************************/
int	export_builtin(t_vars **head, char *var_name, char *var_value)
{
    t_vars	*temp;

    if (!var_name)
    {
        temp = *head;
        while (temp)
        {
            if (!temp->value && temp->exported == 1)
                ft_printf("declare -x %s\n", temp->name);
            else if (temp->value && temp->exported == 1)
                ft_printf("declare -x %s=%s\n", temp->name, temp->value);
            temp = temp->next;
        }
        return (0);
    }
    else
    {
        temp = find_vars(*head, var_name);
        if (temp)
        {
            temp->exported = 1;
            if (var_value)
            {
                if (temp->value)
                    free(temp->value);
                temp->value = ft_strdup(var_value);
            }
            return (0);
        }
        else
        {
            add_var(head, var_name, var_value, 1);
            return (0);
        }
    }
}

/******************************************************************************
*
*	-This function will delete the node where the var_name is found
*
******************************************************************************/
int	unset_builtin(t_vars *head, char *var_name)
{
	t_vars	*current;
	t_vars	*previous;
	
	current = head;
	previous = NULL;
	while (current)
	{
		if (current->name && ft_strcmp((current)->name, var_name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else 
				head = current->next;
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return (0);
		}

		previous = current;
		current = current->next;
	}
	return (0);
}

/******************************************************************************
* 
*	-This function prints all the environment variables stored in t_vars list.
*	-Will be called by the env command.
*	-Can be used to see what is currently stored in all the variables.
*
*	EDGE CASES DONE :
*	-env won't print variables with no value attached to them
*
******************************************************************************/
int	env_builtin(t_vars *head)
{
	while (head)
	{
		if (head->value && head->name && head->hidden == 0 && head->exported == 1)
			ft_printf("%s=%s, [export:[%d], hidden[%d]] \n", head->name, head->value, head->exported, head->hidden);
		head = head->next;
	}
	return (0);
}
