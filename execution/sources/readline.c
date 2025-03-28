/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/28 17:19:09 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*initialize_data(void)
{
    t_vars *vars;
	
    vars = malloc(sizeof(t_vars));
    if (!vars)
    {
        perror("malloc on vars initialization");
        exit(EXIT_FAILURE);
    }
	return (NULL);
}

static char	*get_home_dir(void)
{
	char	*current_directory = NULL;
	char	buff[PATH_MAX + 1];

	if (!getcwd(buff, PATH_MAX + 1))
        return (NULL);
	current_directory = ft_strdup(buff);
	ft_printf("assigned directory\n");
	ft_printf("exiting functions...\n");
	ft_printf("cd is %s\n", current_directory);
	return (current_directory);
}

/******************************************************************************
*
*	-Creates the file .shell_history which will store all 
*	commands typed by user
*	
*	-The file is created in the root directory
*	
******************************************************************************/
void	create_history_file(void)
{
	int	fd;

	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	printf("history file created\n");
	close(fd);
}

/******************************************************************************
*
*	-This function takes the input from the command line and appends it to the 
*	.shell_history file
*	
******************************************************************************/

void	write_history_file(char *read)
{
	int	fd;
	int	i;

	i = 0;
	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (read[i] != '\0')
		i++;
	write(fd, read, i);
	write(fd, "\n", 1);
}

void print_environment(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

/******************************************************************************
*	
*	-The main maintains a constant loop until terminated by user.
*	
*	-It simulates and actual shell, where you can keep inputing commands
*
******************************************************************************/
int	main(int argc, char **argv, char **envp)
{
	char	*home_dir;	
	char	*read;
	t_vars	*vars;
	
	ft_printf("initializing_data..\n");
	vars = initialize_data();
	ft_printf("copying environment..\n");
	copy_env(&vars, envp);
	ft_printf("environment_copied..\n");
	home_dir = get_home_dir();
	edit_var(vars, "HOME", home_dir);
	create_history_file();
	ft_printf("created history file\n");
	while (1)
	{
		read = readline("> ");
		add_history(read);
		if (ft_strncmp(read, "pwd", 3) == 0)
			pwd_builtin();
		if (ft_strncmp(read, "echo", 4) == 0)
			echo_builtin(read);
		if (ft_strncmp(read, "cd", 2) == 0)
			cd_builtin("execution", vars);
		if (ft_strncmp(read, "cd2", 3) == 0)
			cd_builtin(NULL, vars);
		if (ft_strncmp(read, "edit", 4) == 0)
			edit_var(vars, "HOME", "rojornod/personal/minishell/execution");
		if (ft_strncmp(read, "env", 3) == 0)
			print_vars(vars);
		if (ft_strncmp(read, "find", 4) == 0)
			find_vars(vars, "HOME");
		write_history_file(read);
	}
	return (0);
}

