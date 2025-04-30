/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:27:48 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/30 16:03:50 by rojornod         ###   ########.fr       */
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

void	exit_builtin(char *exit_cmd)
{
	ft_printf("exit\n");
	if (exit_cmd)
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
		if (tokens[i][j] == ' ' || tokens[i][j] == '\'' || tokens[i][j] == '\\')
	 		j++;
	 	else if (tokens[i][j] == ' ' && tokens[i][j + 1] == ' ')
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
void	echo_builtin(char **tokens)
{
	int	i;


	i = 0;
	if (!tokens[1])
		return (ft_putchar_fd('\n', 1));
	if (ft_strcmp(tokens[1], "-n") == 0)
	{
		i = 2;
		if (!tokens[i])
			return ;
		echo_printing(tokens, i);
	}
	else
	{
		i = 1;
		echo_printing(tokens, i);
		ft_putchar_fd('\n', 1);
	}
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
void	pwd_builtin(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = getcwd(buff, PATH_MAX + 1);
	if (current_directory != NULL)
		ft_printf("%s\n", current_directory);
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
void	cd_builtin(char *path, t_vars *vars)
{
	char	buff[PATH_MAX + 1];

	edit_var(vars, "OLDPWD", getcwd(buff, PATH_MAX + 1));
	if (!path)
	{
		vars = find_vars(vars, "HOME");
		if (!vars)
			ft_printf("error: no HOME variable found");
		else
			chdir(vars->value);
	}
	else
	{
		if (chdir(path) < 0)
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
	}
}
/******************************************************************************
*
*		This function will print out all the exported variables
*
******************************************************************************/
void	export_builtin(t_vars *head, char *var_name, char *var_value)
{
	if (!var_name)
	{
		while (head)
		{
			if (head->value == NULL)
				ft_printf("declare -x %s, value=[%s] export [%d]\n", head->name, head->value, head->exported);
			else
				ft_printf("declare -x %s=%s export [%d]\n", head->name, head->value, head->exported);
			head = head->next;
		}
	}
	else if (var_name)
	{
		head = find_vars(head, var_name);
		if (head)
		{
			head->exported = 1;
		}	
	}
	else if (var_name && var_value)
		add_var(&head, var_name, var_value, 1);
	else if (var_name && !var_value)
		add_var(&head, var_name, NULL, 1);
}

/******************************************************************************
*
*	-This function will delete the node where the var_name is found
*
******************************************************************************/
void	unset_builtin(t_vars **head, char *var_name)
{
	t_vars	*temp;

	while (*head)
	{
		if (ft_strcmp((*head)->name, var_name) == 0)
		{
			ft_printf("var found\nname [%s], value [%s]", (*head)->name, (*head)->value);
			temp = *head;
			*head = (*head)->next;
			free(temp);
			ft_printf("freed temp\n");
			return ;
		}
		head = &(*head)->next;
	}
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
void	env_builtin(t_vars *head)
{
	while (head)
	{
		if (head->name && head->hidden == 0)
			printf("%s=%s, export:[%d], hidden[%d] \n", head->name, head->value, head->exported, head->hidden);
		head = head->next;
	}
}


