/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/24 16:16:05 by rojornod         ###   ########.fr       */
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
	return (vars);
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
	printf("file created\n");
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

/******************************************************************************
*	
*	-The main maintains a constant loop until terminated by user.
*	
*	-It simulates and actual shell, where you can keep inputing commands
*
******************************************************************************/
int	main(void)
{
	char	*home_dir;	
	char	*read;
	t_vars	*vars;
	
	vars = initialize_data();
	home_dir = get_home_dir();
	add_var(&vars,"HOME", home_dir, 1);
	print_vars(vars);
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
			cd_builtin("libft/printf", vars);
		write_history_file(read);
	}
	return (0);
}

